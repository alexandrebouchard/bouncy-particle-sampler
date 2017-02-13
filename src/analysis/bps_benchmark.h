#pragma once

#include "analysis/output_analysis.h"
#include "analysis/parallel_mcmc_runner.h"
#include "analysis/plotting_utils.h"
#include "core/mcmc.h"

#include <string>
#include <vector>

namespace bps {
namespace analysis {

/**
 * A class for performing standard analysis on the BPS algorithm.
 */
template<typename FloatingPointType, int Dimensionality>
class BpsBenchmark {

 public:

  typedef std::vector<typename ParallelMcmcRunner<
            FloatingPointType, Dimensionality>::BpsFactory>
          BpsFactoriesVector;

  typedef typename Mcmc<FloatingPointType, Dimensionality>::SampleOutput
          SampleRun;

  typedef std::shared_ptr<std::vector<SampleRun>> SampleOutputsVector;

  typedef typename OutputAnalysis<FloatingPointType, Dimensionality>
            ::ExpecatationEstimator
          ExpectationEstimator;

  typedef typename Mcmc<FloatingPointType, Dimensionality>
            ::RealFunctionOnSamples
          RealFunctionOnSamples;

  /**
   * The given name vectors and bpsFactories vector must all be of the same
   * size.
   *
   * @param bpsFactories
   *   A vector of bps factory functions (functions which create new instances
   *   of bps algorithm class).
   * @param algorithmNames
   *   Detailed names of the algorithms (given in the bpsFactory) which will
   *   appear in the plots.
   * @param shortAlgorithmDescriptions
   *   Short descriptions for each algorithms (a couple of symbols). Will be
   *   used, for example, when plotting box plots to compare different
   *   algorithms on the same plot.
   * @param benchmarkName
   *   All results will be output to a directory with this name.
   */
  BpsBenchmark(
    const BpsFactoriesVector& bpsFactories,
    const std::vector<std::string>& algorithmNames,
    const std::vector<std::string>& shortAlgorithmNames,
    const std::string& benchmarkName);


  /**
   * A helper for the main constructor, which does not take algorithm names.
   * This constructor will fill in { "Algorithm1", "Algorithm2", ... } for
   * algorithm names and { "Alg1", "Alg2", ... } for short algorithm names.
   *
   * To see full description of parameters, read see the other constructor.
   */
  BpsBenchmark(
    const BpsFactoriesVector& bpsFactories,
    const std::string& benchmarkName);

  /**
   * Runs the algorithms given in the constructor to generate samples.
   * It will erase all data generated by the previous sample runs.
   *
   * @requiredTrajectoryLengths
   *   The required trajectory lengths to generate for each instance of the
   *   BPS algorithm.
   * @numberOfRunsForEachAlgorithm
   *   The required number of times that we should run each given algorithm.
   * @numberOfCores
   *   The number of CPU cores to use for running the BPS algorithms.
   */
  void generateSamples(
    const FloatingPointType& requiredTrajectoryLengths,
    const int& numberOfRunsForEachAlgorithm,
    const int& numberOfCores = 8);

  /**
   * Runs benchmark analysis on the samples generated by generateSamples()
   * method.
   *
   * @param expectationEstimators
   *   An expecation estimators, one for each algorithm.
   * @param realFunctionOnSamples
   *   Function which will be applied for all the generated sample points
   *   from the BPS algorithm.
   * @param benchmarkName
   *   Name of this benchmark. All the plots will appear in a directory with
   *   this name.
   */
  void runBenchmark(
    const std::vector<ExpectationEstimator>& expectationEstimators,
    const RealFunctionOnSamples& realFunctionOnSamples,
    const std::string& benchmarkName,
    const int& numberOfBatchesForBatchMeans = 100,
    const int& acfLagUpperbound = 100,
    const int& lagStepSize = 1);

  /**
   * Runs a custom function on the samples of each algorithm given by the user.
   * The given functions must have a numeric return type.
   * A box plot will be generated for each of the algorithm by running the
   * given function on each of its sample runs.
   * The functions vector must be of the same size as the number of algorithms.
   * @param functions
   *   The functions vector which should be run on each sample run of each
   *  algorithm.
   * @param name
   *   Name for outputting the results.
   */
  void runCustomFunctionOnSamplesWithNumericalOutputs(
    const std::vector<std::function<FloatingPointType(SampleRun)>>& functions,
    const std::string& name);

 private:

  // Gets errors for all runs of one particular algorithm.
  void outputErrorsForSampleRuns(
    const int& algorithmId,
    const std::string& outputDir,
    const ExpectationEstimator& expectationEstimator,
    const RealFunctionOnSamples& realFunctionOnSamples);

  // Outputs average interevent times.
  void outputAverageIntereventTimes(
    const std::string &outputDir);

  // For each run (numberOfAlgorithms * numberOfRuns) returns the IACT.
  std::vector<std::vector<FloatingPointType>> outputIactBoxPlot(
    const std::string& outputDir,
    const std::vector<ExpectationEstimator>& expectationEstimators,
    const RealFunctionOnSamples& realFunctionOnSamples,
    const int& numberOfBatches);

  // For each run, outputs the ESS/s.
  void outputEffectiveSampleSizesPerSecond(
    const std::string& outputDir,
    const std::vector<std::vector<FloatingPointType>>& iacts);

  // Gets autocorrelation functions for each run of one particular algorithm.
  void outputAutocorrelationFunctions(
    const int& algorithmId,
    const std::string& outputDir,
    const ExpectationEstimator& expectationEstimator,
    const RealFunctionOnSamples& realFunctionOnSamples,
    const int& acfLagUpperbound,
    const int& lagStepSize);

  // If Dimensionality == 2, plots two dimensional sample paths.
  void plotTwoDimensionalSamplePaths(
    const int& algorithmId,
    const std::string& outputDir);

  const BpsFactoriesVector bpsFactories_;
  const std::vector<std::string> algorithmNames_;
  const std::vector<std::string> shortAlgorithmNames_;
  const std::string outputDirectory_;
  PlottingUtils<FloatingPointType> plottingUtils_;
  std::unique_ptr<std::vector<SampleOutputsVector>> sampleOutputs_;
  std::unique_ptr<std::vector<std::vector<double>>> runningTimes_;

};

}
}

#include "analysis/bps_benchmark.tcc"
