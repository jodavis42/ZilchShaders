///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Math
{

//-------------------------------------------------------------------BoolVector4
/// An empty callback for when an Lcp solver fails to converge.
/// Used when no callback is provided to an lcp solver.
struct EmptyErrorCallback
{
  template<typename MatrixType, typename VectorType>
  void operator()(MatrixType& A, VectorType& b,VectorType& x0, real convergence)
  {

  }
};

//-------------------------------------------------------------------BoolVector4
struct SimpleErrorCallback
{
  bool mSuccessfullySolved;
  real mConvergence;

  SimpleErrorCallback()
  {
    mSuccessfullySolved = true;
    mConvergence = 0;
  }

  template<typename MatrixType, typename VectorType>
  void operator()(MatrixType& A, VectorType& b, VectorType& x0, real convergence)
  {
    mSuccessfullySolved = false;
    mConvergence = convergence;
  }
};

}//namespace Math
