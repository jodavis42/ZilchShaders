################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
# commented out since we have to ignore some files in this folder at the moment
#include(${CMAKE_CURRENT_LIST_DIR}/Generated.cmake)

target_sources(ZilchShaders
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/AttributeResolvers/IAttributeResolver.hpp
    ${CMAKE_CURRENT_LIST_DIR}/AttributeResolvers/AttributeResolverSortData.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Enums/ImageEnums.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SpirVUtils/SpirVDefinitions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SpirVUtils/SpirVDefinitions.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ArithmeticInstructions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BitInstructions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CommonInstructions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ConversionInstructions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CycleDetection.cpp
    ${CMAKE_CURRENT_LIST_DIR}/EntryPointGeneration.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ExtensionLibrary.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FixedArray.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Glsl450Extensions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LibraryTranslationHelpers.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LogicalInstructions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OperatorKeys.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderAttributes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderByteStream.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderCodeBuilder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderErrors.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderImageIntrinsics.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderIntrinsics.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderIntrinsicTypes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderIRLibraryTranslation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleZilchParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleZilchShaderIRGenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SpirVSpecializationConstantPass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StageRequirementsGatherer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TypeDependencyCollector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderGlslBackend.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderIntrinsicsStaticZilchLibrary.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRCompositor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRCore.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRExtendedTypes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRLibrary.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRMeta.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRPasses.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRProject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRReflection.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRShared.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderSpirVBinaryBackend.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShadersStandard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRTranslationPass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchSpirVDisassemblerBackend.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchSpirVFrontEnd.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchSpirVFrontEndValidation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchSpirVSettings.cpp
#  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/BaseShaderIRTranslator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CommonInstructions.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CycleDetection.hpp
    ${CMAKE_CURRENT_LIST_DIR}/EntryPointGeneration.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ExtensionLibrary.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ForwardDeclarations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/GLSL.std.450.h
    ${CMAKE_CURRENT_LIST_DIR}/LibraryTranslationHelpers.hpp
    ${CMAKE_CURRENT_LIST_DIR}/OperatorKeys.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderAttributes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderByteStream.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderCodeBuilder.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderErrors.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderImageIntrinsics.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderIntrinsicTypes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderIRLibraryTranslation.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleZilchParser.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleZilchShaderIRGenerator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SpirVHelpers.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SpirVSpecializationConstantPass.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StageRequirementsGatherer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/TypeDependencyCollector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderGlslBackend.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderIntrinsicsStaticZilchLibrary.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRCompositor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRCore.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRExtendedTypes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRLibrary.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRMeta.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRPasses.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRProject.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRReflection.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRShared.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderIRTranslationPass.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShaderSpirVBinaryBackend.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchShadersStandard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchSpirVDisassemblerBackend.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchSpirVFrontEnd.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchSpirVFrontEndValidation.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ZilchSpirVSettings.hpp
)
