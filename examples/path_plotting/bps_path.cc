#include <iostream>
#include <vector>

#include <Eigen/Core>

#include "mcmc/bps/bps_builder.h"
#include "mcmc/distributions/gaussian.h"

#include "run_and_plot.h"

const double kRefreshRate = 1.0;

using namespace pdmp::mcmc;

int main(int argc, char **argv) {
  // Create a standard normal 2-dimensional factor.
  RealMatrix covariances(2, 2);
  covariances << 1, 0,
                 0, 1;
  RealVector mean(2);
  mean << 0, 0;
  mcmc::GaussianDistribution gaussianDistribution(mean, covariances);

  // Create a BPS sampler from the factor created above.
  pdmp::mcmc::BpsBuilder bpsBuilder(2);
  bpsBuilder.addFactor(
    {0,1},
    gaussianDistribution,
    kRefreshRate);
  auto pdmp = bpsBuilder.build();

  // Finally, run the sampler and plot its path.
  runSamplerAndPlotPath(pdmp);
  return 0;
}
