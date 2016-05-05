#pragma once

#include "rosban_gp/tools.h"

#include <Eigen/Core>

#include <functional>
#include <memory>

namespace rosban_gp
{

class GaussianProcess
{
public:
  GaussianProcess();

  GaussianProcess(const Eigen::MatrixXd & inputs,
                  const Eigen::VectorXd & observations,
                  CovarianceFunction covar_func);

  /// Generate the outputs of a random function using the requested inputs
  /// While in the requested Inputs, each column is a different input,
  /// In the result, each row is a different output
  Eigen::VectorXd generateValues(const Eigen::MatrixXd & requested_inputs,
                                 std::default_random_engine & engine);

private:
  /// Update the inverse covariance matrix if required
  void updateInverse();

  ///
  std::shared_ptr<CovarianceFunction> covar_func;

  /// Known inputs of the gaussian process (row is dimension, col is sample no)
  Eigen::MatrixXd inputs;
  /// Measured outputs (row is sample no)
  Eigen::VectorXd observations;
  /// Inverse covariance matrix of the inputs
  Eigen::MatrixXd inv_cov;
  /// Is it necessary to update inverse of the covariance matrix
  bool dirty_inv;
};

}
