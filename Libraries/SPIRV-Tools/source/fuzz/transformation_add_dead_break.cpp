// Copyright (c) 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "source/fuzz/transformation_add_dead_break.h"

#include "source/fuzz/fact_manager.h"
#include "source/fuzz/fuzzer_util.h"
#include "source/opt/basic_block.h"
#include "source/opt/ir_context.h"
#include "source/opt/struct_cfg_analysis.h"

namespace spvtools {
namespace fuzz {

TransformationAddDeadBreak::TransformationAddDeadBreak(
    const spvtools::fuzz::protobufs::TransformationAddDeadBreak& message)
    : message_(message) {}

TransformationAddDeadBreak::TransformationAddDeadBreak(
    uint32_t from_block, uint32_t to_block, bool break_condition_value,
    std::vector<uint32_t> phi_id) {
  message_.set_from_block(from_block);
  message_.set_to_block(to_block);
  message_.set_break_condition_value(break_condition_value);
  for (auto id : phi_id) {
    message_.add_phi_id(id);
  }
}

bool TransformationAddDeadBreak::AddingBreakRespectsStructuredControlFlow(
    opt::IRContext* context, opt::BasicBlock* bb_from) const {
  // Look at the structured control flow associated with |from_block| and
  // check whether it is contained in an appropriate construct with merge id
  // |to_block| such that a break from |from_block| to |to_block| is legal.

  // There are three legal cases to consider:
  // (1) |from_block| is a loop header and |to_block| is its merge
  // (2) |from_block| is a non-header node of a construct, and |to_block|
  //     is the merge for that construct
  // (3) |from_block| is a non-header node of a selection construct, and
  //     |to_block| is the merge for the innermost loop containing
  //     |from_block|
  //
  // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/2653) It may be
  //   possible to be more aggressive in breaking from switch constructs.
  //
  // The reason we need to distinguish between cases (1) and (2) is that the
  // structured CFG analysis does not deem a header to be part of the construct
  // that it heads.

  // Consider case (1)
  if (bb_from->IsLoopHeader()) {
    // Case (1) holds if |to_block| is the merge block for the loop;
    // otherwise no case holds
    return bb_from->MergeBlockId() == message_.to_block();
  }

  // Both cases (2) and (3) require that |from_block| is inside some
  // structured control flow construct.

  auto containing_construct =
      context->GetStructuredCFGAnalysis()->ContainingConstruct(
          message_.from_block());
  if (!containing_construct) {
    // |from_block| is not in a construct from which we can break.
    return false;
  }

  // Consider case (2)
  if (message_.to_block() ==
      context->cfg()->block(containing_construct)->MergeBlockId()) {
    // This looks like an instance of case (2).
    // However, the structured CFG analysis regards the continue construct of a
    // loop as part of the loop, but it is not legal to jump from a loop's
    // continue construct to the loop's merge (except from the back-edge block),
    // so we need to check for this case.
    //
    // TODO(https://github.com/KhronosGroup/SPIRV-Tools/issues/2577): We do not
    //  currently allow a dead break from a back edge block, but we could and
    //  ultimately should.
    return !fuzzerutil::BlockIsInLoopContinueConstruct(
        context, message_.from_block(), containing_construct);
  }

  // Case (3) holds if and only if |to_block| is the merge block for this
  // innermost loop that contains |from_block|
  auto containing_loop_header =
      context->GetStructuredCFGAnalysis()->ContainingLoop(
          message_.from_block());
  if (containing_loop_header &&
      message_.to_block() ==
          context->cfg()->block(containing_loop_header)->MergeBlockId()) {
    return !fuzzerutil::BlockIsInLoopContinueConstruct(
        context, message_.from_block(), containing_loop_header);
  }
  return false;
}

bool TransformationAddDeadBreak::IsApplicable(
    opt::IRContext* context, const FactManager& /*unused*/) const {
  // First, we check that a constant with the same value as
  // |message_.break_condition_value| is present.
  opt::analysis::Bool bool_type;
  auto registered_bool_type =
      context->get_type_mgr()->GetRegisteredType(&bool_type);
  if (!registered_bool_type) {
    return false;
  }
  opt::analysis::BoolConstant bool_constant(registered_bool_type->AsBool(),
                                            message_.break_condition_value());
  if (!context->get_constant_mgr()->FindConstant(&bool_constant)) {
    // The required constant is not present, so the transformation cannot be
    // applied.
    return false;
  }

  // Check that |message_.from_block| and |message_.to_block| really are block
  // ids
  opt::BasicBlock* bb_from =
      fuzzerutil::MaybeFindBlock(context, message_.from_block());
  if (bb_from == nullptr) {
    return false;
  }
  opt::BasicBlock* bb_to =
      fuzzerutil::MaybeFindBlock(context, message_.to_block());
  if (bb_to == nullptr) {
    return false;
  }

  // Check that |message_.from_block| ends with an unconditional branch.
  if (bb_from->terminator()->opcode() != SpvOpBranch) {
    // The block associated with the id does not end with an unconditional
    // branch.
    return false;
  }

  assert(bb_from != nullptr &&
         "We should have found a block if this line of code is reached.");
  assert(
      bb_from->id() == message_.from_block() &&
      "The id of the block we found should match the source id for the break.");
  assert(bb_to != nullptr &&
         "We should have found a block if this line of code is reached.");
  assert(
      bb_to->id() == message_.to_block() &&
      "The id of the block we found should match the target id for the break.");

  // Check whether the data passed to extend OpPhi instructions is appropriate.
  if (!fuzzerutil::PhiIdsOkForNewEdge(context, bb_from, bb_to,
                                      message_.phi_id())) {
    return false;
  }

  // Check that adding the break would respect the rules of structured
  // control flow.
  if (!AddingBreakRespectsStructuredControlFlow(context, bb_from)) {
    return false;
  }

  // Check that adding the break would not violate the property that a
  // definition must dominate all of its uses.
  return fuzzerutil::NewEdgeLeavingConstructBodyRespectsUseDefDominance(
      context, bb_from, bb_to);
}

void TransformationAddDeadBreak::Apply(opt::IRContext* context,
                                       FactManager* /*unused*/) const {
  fuzzerutil::AddUnreachableEdgeAndUpdateOpPhis(
      context, context->cfg()->block(message_.from_block()),
      context->cfg()->block(message_.to_block()),
      message_.break_condition_value(), message_.phi_id());

  // Invalidate all analyses
  context->InvalidateAnalysesExceptFor(opt::IRContext::Analysis::kAnalysisNone);
}

protobufs::Transformation TransformationAddDeadBreak::ToMessage() const {
  protobufs::Transformation result;
  *result.mutable_add_dead_break() = message_;
  return result;
}

}  // namespace fuzz
}  // namespace spvtools