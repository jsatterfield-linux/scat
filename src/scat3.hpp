#ifndef SCAT2_HPP
#define SCAT2_HPP

// SCAT version 3.0.3

#include <array>
#include <map>
#include <string>
#include <vector>

const double PI = 3.141592; 
const std::string VERSION="3.0.3";

const int FLAGINT = -1;
    
const int MAXSPECIES = 2;
// This line is 120 for microsats and 2 for SNPs
// const int MAXNALLELE = 120; 
const int MARGIN = 7;  // margin around grid

typedef std::vector<double> DoubleVec1d;
typedef std::vector<DoubleVec1d> DoubleVec2d;
typedef std::vector<DoubleVec2d> DoubleVec3d;
typedef std::vector<DoubleVec3d> DoubleVec4d;
typedef std::vector<int> IntVec1d;
typedef std::vector<IntVec1d> IntVec2d;
typedef std::vector<IntVec2d> IntVec3d;
typedef std::vector<IntVec3d> IntVec4d;
typedef std::vector<std::string> StringVec1d;
typedef std::vector<std::map<int,int>> MapVec1d;

const int ValidateAssumptions = 1;

const double EPSILON = 1e-100;

struct Config {
  // required parameters
  
  // '<arg1>'; input genotype file to read from
  std::string genotypeFile;
  // '<arg2>'; input regions/location file to read from
  std::string regionsFile;
  // '<arg3>'; directory to write files to
  std::string outputDir;

  // '<arg4>'; number of loci in the genotype file
  int numLoci;

  // optional parameters

  // '<arg5>' (default 100)
  // number of sampled iterations of the MCMC scheme to perform.
  int numIter = 100;
  // '<arg6>' (default 10)
  // number of steps taken through the Markov chain between samplings
  // also called the "thinning interval"
  int numThin = 10;
  // '<arg7>' (default 100); number of burn-in iterations
  int numBurn = 100;
  // '<arg8>' (default 1); number of species
  int numSpecies = 1;

  // number of individuals read from genotypeFile
  int numInd;
  // number of regions read from regionsFile
  int numRegion;
  // number of alleles
  IntVec1d numAllele;

  // '-S' (default false); whether the seed is set
  bool seedSet = false;
  // '-S' (default 0); seed of the random-number generator
  int seed = 0;
  // '-C' (default 0)
  // number of columns to skip in genotype file after location number
  int skipCol = 0;
  // '-p' (default 0);
  int pseudocount = 0;

  // '-H' (default 0); undocumented method of running the program
  int hybridCheck = 0;
  // '-A' (default false)
  // whether to try to estimate the position of a particular sample
  bool locate = false;
  // '-A <arg1>'; index of the first sample to locate
  int firstSampleToLocate = 0;
  // '-A <arg2>'; index of the last sample to locate
  int lastSampleToLocate = -1;
  // '-W' (default false); locate the whole region
  bool locateWholeRegion = false;
  // '-R' (default false)
  // whether to remove all samples from a region when doing location
  bool removeRegion = false;

  // '-N' (default false);
  bool includeNugget = false;
  // '-Z' (default false); whether location file includes subregion data
  bool useSubregion = false;
  // (default 8); number of subregions
  int numSubregion = 8;
  // '-D' (default false)
  // whether to use default map info for only forest elephants
  bool forestOnly = false;
  // '-d' (default false)
  // whether to use default map info for only savannah elephants
  bool savannahOnly = false;

  // '-I' (default true); whether to permute the regions (if specified on CLI)
  bool permute = true;
  // '-X' (default false)
  // whether to cheat by starting estimates at the true location
  bool cheat = false;
  // '-x' (default false); non-uniform prior weights sample as being more likely
  // to be near one of the sampling locations
  bool nonUniformPrior = false;
  // '-r' (default false); whether a non-random walk is used
  bool useLangevin = false;
  // '-w' (default true); whether spatial smoothing is used
  bool useSpatial = true;

  // '-f' (default true); whether the alpha parameters should be updated
  bool updateAlpha = true;
  // `-N`; will change to 4 if "nugget" effect
  int alphaLen = 3;
  // '-f <arg1> <arg2> <arg3>' or '-i <arg1> <arg2> <arg3>'
  // what to initially set the alpha parameters to
  std::array<double, 4> alphaInit = { 1, 1, 1, 0 };
  // [0]: (default 0.2); 1 / alpha[0]
  // [1]: (default 1); scale on which frequency correlations dropoff 
  // [2]: (default 0.1);
  // [3]: (default 0); the "nugget" effect
  std::array<double, 4> alphaMin = { 0.2, 1, 0.1, 0 };
  // [0]: (default 100); controls amount of variation of frequencies about mean
  // [1]: (default 100000);
  // [2]: (default 2);
  // [3]: (default 100); the "nugget" effect
  std::array<double, 4> alphaMax = { 100, 100000, 2, 100 };
  // '-a' (default 0.4);
  double alphaUpdateSD = 0.4;
  // (default 0.001); gamma prior on alpha
  double alphaN = 0.001;
  // (default 0.001);
  double alphaL = 0.001;
  // '-b' or '-f' or '-m' (default true)
  // whether beta parameters should be updated
  bool updateBeta = true;
  // '-f <arg4>' or '-i <arg4>' (default 1)
  // what to initially set the beta parameter to
  double betaInit = 1;
  // (default 0.001); parameters on gamma prior on beta
  double betaN = 0.001;
  // (default 0.001); beta is prior precision of mu
  double betaL = 0.001; 
  // '-e <arg1>' (default 0.05)
  // prob of genotyping error in this one sample (set to 0 for no error)
  double delta = 0.05;
  int deltaLen = 3;
  // [0]: (default 0.1);
  // [1]: (default 1);
  // [2]: (default 0.1);
  std::array<double, 3> deltaMin = { 0.1, 1, 0.1 };
  // [0]: (default 100);
  // [1]: (default 10000);
  // [2]: (default 2);
  std::array<double, 3> deltaMax = { 100, 10000, 2 };
  // (default 0.001); gamma prior on delta
  double deltaN = 0.001;
  // (default 0.001);
  double deltaL = 0.001;
  // (default 0.001); params of gamma prior on eta
  double etaN = 0.001;
  // (default 0.001); eta is prior precision of lambda
  double etaL = 0.001;
  // '-m' (default true); fix mu to be 0, mimic "indep frequencies" model
  bool updateMu = true;
  // '-n' (default true); whether Nu update should be disabled
  // currently always true due to undeveloped multi-species machinery
  bool updateNu = true;
  // (default true);
  bool updateX = true;
  // '-j' (default false); whether to update x parameter jointly
  bool updateJoint = false;

  // '-e <arg2>' (default 0.0); prob of null allele
  double nullAlleleProb = 0.0;
  // '-h' (default 0.5); proposal variance for x parameter update
  double xProposalFactor = 0.5;
  // (default 0.5); proposal variance for y parameter update
  double yProposalFactor = 0.5;
  // (default 1); 0.0001 
  double temperature = 1; 

  // '-E' (default false); whether inputs should be echo'ed to the terminal
  bool echoInputs = false;
  // '-v' (default false);
  bool verbose = false;
  // '-v' (default false);
  bool outputX = false;
  // (default 20); max characters from individual name to use when outputting 
  size_t maxOutCharsInName = 20;
  // (default 0.2); controls what percentage of progress will print a "."
  double screenProgressInterval = 0.2;

  // '-M <filename>'; filename of samples to be assigned
  std::string assignFile = "";
  // '-B <filename>'; filename of boundaries to read
  std::string boundaryFile = "";
  // '-g <filename>'; filename of grid file, replacement for a boundary file
  std::string gridFile = "";
  // '-v <arg1>'; filename to write the state of X to for debugging
  std::string xFile = "";
};

struct AcceptanceStat {
  int attempt = 0;
  int accept = 0;
};

struct State {
  std::array<AcceptanceStat, 4> alpha;
  std::array<AcceptanceStat, 3> delta;
  AcceptanceStat lambda;
  AcceptanceStat mu;
  AcceptanceStat nu;
  AcceptanceStat loc;
  AcceptanceStat x;
  AcceptanceStat y;

  int sampleToLocate = 0;
  // stores true region of the sample to be located
  int trueRegion;
};

#endif  // SCAT2_HPP
