#ifndef COOLING_CLASS
#define COOLING_CLASS

#include "../athena.hpp"
#include "../athena_arrays.hpp"

#include "code_units.hpp"

static bool DEBUG_FLAG = false;
// static bool DEBUG_FLAG = true;

class Cooling {
public:
  Cooling();
  ~Cooling();

  Real tfloor;

  Real townsend(Real temp, Real rho, Real const dt, Real Lambda_fac = 1.0);
  Real Lambda(Real temp);
  Real tcool(Real temp, Real rho);

private:
  Real const mh  = 1.6605e-24;   // atomic mass unit (g)
  Real const kb  = 1.380648e-16; // boltzmann constant (erg/K)

  int nbins;
  Real const_factor;

  AthenaArray<Real> cool_t;
  AthenaArray<Real> cool_tef;
  AthenaArray<Real> cool_coef;
  AthenaArray<Real> cool_index;
};

// Initialize all values in the cooling table
Cooling::Cooling() {

  if (DEBUG_FLAG){
    printf("Start of Cooling::Cooling!\n");
  }

  // Compute the constant factor needed to compute new TEFs
  // Real g  = 5.0/3.0; // adiabatic index
  // Real X = 0.7; auto Z = 0.02; // Fully ionized, solar abundances
  // Real mu   = 1.0/(2.0*X + 0.75*(1.0-X-Z) + Z/2.0);
  // Real mu_e = 2.0/(1.0+X);
  // Real mu_h = 1.0/X;
  const_factor = (1.0e-23)*(g-1.0)*mu/(kb*mue*muH*mh);

  // Initialize the cooling table
  nbins = 80;

  cool_t.NewAthenaArray(nbins);
  cool_tef.NewAthenaArray(nbins);
  cool_coef.NewAthenaArray(nbins);
  cool_index.NewAthenaArray(nbins);
  // Temperatures in [K]

  cool_t(0) = 100.0;
  cool_t(1) = 119.0;
  cool_t(2) = 142.0;
  cool_t(3) = 169.0;
  cool_t(4) = 202.0;
  cool_t(5) = 241.0;
  cool_t(6) = 287.0;
  cool_t(7) = 342.0;
  cool_t(8) = 407.0;
  cool_t(9) = 486.0;
  cool_t(10) = 579.0;
  cool_t(11) = 690.0;
  cool_t(12) = 822.0;
  cool_t(13) = 980.0;
  cool_t(14) = 1168.0;
  cool_t(15) = 1392.0;
  cool_t(16) = 1660.0;
  cool_t(17) = 1978.0;
  cool_t(18) = 2358.0;
  cool_t(19) = 2810.0;
  cool_t(20) = 3350.0;
  cool_t(21) = 3993.0;
  cool_t(22) = 4759.0;
  cool_t(23) = 5672.0;
  cool_t(24) = 6761.0;
  cool_t(25) = 8058.0;
  cool_t(26) = 9605.0;
  cool_t(27) = 11449.0;
  cool_t(28) = 13646.0;
  cool_t(29) = 16265.0;
  cool_t(30) = 19387.0;
  cool_t(31) = 23107.0;
  cool_t(32) = 27542.0;
  cool_t(33) = 32828.0;
  cool_t(34) = 39129.0;
  cool_t(35) = 46639.0;
  cool_t(36) = 55590.0;
  cool_t(37) = 66260.0;
  cool_t(38) = 78977.0;
  cool_t(39) = 94135.0;
  cool_t(40) = 112202.0;
  cool_t(41) = 133737.0;
  cool_t(42) = 159404.0;
  cool_t(43) = 189998.0;
  cool_t(44) = 226464.0;
  cool_t(45) = 269929.0;
  cool_t(46) = 321736.0;
  cool_t(47) = 383486.0;
  cool_t(48) = 457088.0;
  cool_t(49) = 544816.0;
  cool_t(50) = 649382.0;
  cool_t(51) = 774016.0;
  cool_t(52) = 922571.0;
  cool_t(53) = 1099639.0;
  cool_t(54) = 1310690.0;
  cool_t(55) = 1562248.0;
  cool_t(56) = 1862087.0;
  cool_t(57) = 2219474.0;
  cool_t(58) = 2645453.0;
  cool_t(59) = 3153189.0;
  cool_t(60) = 3758374.0;
  cool_t(61) = 4479711.0;
  cool_t(62) = 5339493.0;
  cool_t(63) = 6364291.0;
  cool_t(64) = 7585776.0;
  cool_t(65) = 9041698.0;
  cool_t(66) = 10777053.0;
  cool_t(67) = 12845470.0;
  cool_t(68) = 15310875.0;
  cool_t(69) = 18249459.0;
  cool_t(70) = 21752040.0;
  cool_t(71) = 25926865.0;
  cool_t(72) = 30902954.0;
  cool_t(73) = 36834095.0;
  cool_t(74) = 43903587.0;
  cool_t(75) = 52329911.0;
  cool_t(76) = 62373484.0;
  cool_t(77) = 74344698.0;
  cool_t(78) = 88613522.0;
  cool_t(79) = 105620933.0;


  // cool_t(0)  = 10000.0;
  // cool_t(1)  = 12600.0;
  // cool_t(2)  = 15890.0;
  // cool_t(3)  = 20020.0;
  // cool_t(4)  = 25240.0;
  // cool_t(5)  = 31810.0;
  // cool_t(6)  = 40090.0;
  // cool_t(7)  = 50530.0;
  // cool_t(8)  = 63680.0;
  // cool_t(9)  = 80260.0;
  // cool_t(10) = 101200.0;
  // cool_t(11) = 127500.0;
  // cool_t(12) = 160700.0;
  // cool_t(13) = 202600.0;
  // cool_t(14) = 255300.0;
  // cool_t(15) = 321800.0;
  // cool_t(16) = 405600.0;
  // cool_t(17) = 511100.0;
  // cool_t(18) = 644200.0;
  // cool_t(19) = 812000.0;
  // cool_t(20) = 1000000.0;
  // cool_t(21) = 1259000.0;
  // cool_t(22) = 1585000.0;
  // cool_t(23) = 1995000.0;
  // cool_t(24) = 2512000.0;
  // cool_t(25) = 3162000.0;
  // cool_t(26) = 3981000.0;
  // cool_t(27) = 5012000.0;
  // cool_t(28) = 6310000.0;
  // cool_t(29) = 7943000.0;
  // cool_t(30) = 10000000.0;
  // cool_t(31) = 12590000.0;
  // cool_t(32) = 15850000.0;
  // cool_t(33) = 19950000.0;
  // cool_t(34) = 25120000.0;
  // cool_t(35) = 31620000.0;
  // cool_t(36) = 39810000.0;
  // cool_t(37) = 50120000.0;
  // cool_t(38) = 63100000.0;
  // cool_t(39) = 79430000.0;

  // Cooling Coefficient [1e-23 ergs*cm3/s]

  cool_coef(0) = 0.000124667684;
  cool_coef(1) = 0.00014593765885687732;
  cool_coef(2) = 0.0001715959828372093;
  cool_coef(3) = 0.00020397635462371136;
  cool_coef(4) = 0.0002466095905714286;
  cool_coef(5) = 0.0002966292262343471;
  cool_coef(6) = 0.00035146525112574403;
  cool_coef(7) = 0.000412892923070039;
  cool_coef(8) = 0.0004797314999474621;
  cool_coef(9) = 0.0005539902296304718;
  cool_coef(10) = 0.0006333264208942366;
  cool_coef(11) = 0.0007187620482269327;
  cool_coef(12) = 0.0008101481672828035;
  cool_coef(13) = 0.0009081792531775214;
  cool_coef(14) = 0.0010130434637853109;
  cool_coef(15) = 0.0011255698499059563;
  cool_coef(16) = 0.0012475156926631853;
  cool_coef(17) = 0.0013793436427391307;
  cool_coef(18) = 0.0015253688396651582;
  cool_coef(19) = 0.0016881318432176654;
  cool_coef(20) = 0.0018669900756401838;
  cool_coef(21) = 0.0020686742846827135;
  cool_coef(22) = 0.0022990780405097865;
  cool_coef(23) = 0.002548326727217589;
  cool_coef(24) = 0.0027969074196591984;
  cool_coef(25) = 0.0031934686079779914;
  cool_coef(26) = 0.004396787565834668;
  cool_coef(27) = 0.04430091428571428;
  cool_coef(28) = 1.586213;
  cool_coef(29) = 11.23877331571995;
  cool_coef(30) = 14.8976;
  cool_coef(31) = 12.127940978886757;
  cool_coef(32) = 10.902579233226838;
  cool_coef(33) = 11.440342752659577;
  cool_coef(34) = 13.19197646733112;
  cool_coef(35) = 16.695811065006918;
  cool_coef(36) = 22.755533507432705;
  cool_coef(37) = 32.837041083974576;
  cool_coef(38) = 44.84870334261839;
  cool_coef(39) = 51.635627968460106;
  cool_coef(40) = 52.668985714285704;
  cool_coef(41) = 49.912263794212215;
  cool_coef(42) = 51.196952521008406;
  cool_coef(43) = 52.87662967365968;
  cool_coef(44) = 53.92870857142857;
  cool_coef(45) = 47.968170032362465;
  cool_coef(46) = 30.55581943434343;
  cool_coef(47) = 21.766112730941707;
  cool_coef(48) = 19.928391112414467;
  cool_coef(49) = 18.94198287993488;
  cool_coef(50) = 16.803802654471543;
  cool_coef(51) = 16.02167005303244;
  cool_coef(52) = 16.387104387036167;
  cool_coef(53) = 16.011635615459884;
  cool_coef(54) = 14.751485754684838;
  cool_coef(55) = 12.775967581818183;
  cool_coef(56) = 9.827491367966903;
  cool_coef(57) = 7.0434459610619475;
  cool_coef(58) = 5.278841242997543;
  cool_coef(59) = 4.099287205521472;
  cool_coef(60) = 3.352993418538324;
  cool_coef(61) = 2.9968111506679866;
  cool_coef(62) = 2.887220077297075;
  cool_coef(63) = 2.918314246262003;
  cool_coef(64) = 3.024328703341902;
  cool_coef(65) = 3.109309256504162;
  cool_coef(66) = 3.091097092871287;
  cool_coef(67) = 2.9245103626943005;
  cool_coef(68) = 2.6431605064655175;
  cool_coef(69) = 2.3816492931818183;
  cool_coef(70) = 2.2342942462151396;
  cool_coef(71) = 2.189288367620232;
  cool_coef(72) = 2.212009637787419;
  cool_coef(73) = 2.3035336311672685;
  cool_coef(74) = 2.432885989368421;
  cool_coef(75) = 2.588963904430538;
  cool_coef(76) = 2.7672399065230984;
  cool_coef(77) = 2.9645383030653565;
  cool_coef(78) = 3.177493148706832;
  cool_coef(79) = 3.4177251276911766;

  // cool_coef(0) = 1.6408984689285624;
  // cool_coef(1) = 5.789646575948292;
  // cool_coef(2) = 18.797203755396648;
  // cool_coef(3) = 16.7384754689852;
  // cool_coef(4) = 11.274384717759935;
  // cool_coef(5) = 9.95038422958871;
  // cool_coef(6) = 11.302144847043829;
  // cool_coef(7) = 15.819149070534786;
  // cool_coef(8) = 25.224636283348048;
  // cool_coef(9) = 38.02107089248533;
  // cool_coef(10) = 43.98219098299675;
  // cool_coef(11) = 41.277704007796586;
  // cool_coef(12) = 41.95311185975414;
  // cool_coef(13) = 45.260670345801;
  // cool_coef(14) = 47.275626188961176;
  // cool_coef(15) = 32.21420131907784;
  // cool_coef(16) = 24.350976818250636;
  // cool_coef(17) = 23.383616480583676;
  // cool_coef(18) = 18.333394532081098;
  // cool_coef(19) = 14.89691888284402;
  // cool_coef(20) = 14.392505898454834;
  // cool_coef(21) = 13.027915287005817;
  // cool_coef(22) = 11.671262753284271;
  // cool_coef(23) = 9.070904785425046;
  // cool_coef(24) = 6.489695397654223;
  // cool_coef(25) = 4.766239129792971;
  // cool_coef(26) = 3.7811870710765074;
  // cool_coef(27) = 3.313622783657129;
  // cool_coef(28) = 3.0600313080475674;
  // cool_coef(29) = 2.9993768457216112;
  // cool_coef(30) = 2.9491332141250552;
  // cool_coef(31) = 2.744653611808266;
  // cool_coef(32) = 2.3449511265716;
  // cool_coef(33) = 2.0169621177549892;
  // cool_coef(34) = 1.8907205849384978;
  // cool_coef(35) = 1.91584885606706;
  // cool_coef(36) = 2.056870288868004;
  // cool_coef(37) = 2.233680315878366;
  // cool_coef(38) = 2.4097186710383474;
  // cool_coef(39) = 2.5502102007949023;

  // Cooling power index
  cool_index(0) = 0.9055755814788305;
  cool_index(1) = 0.9165816253824087;
  cool_index(2) = 0.9930467965795304;
  cool_index(3) = 1.0640998234342836;
  cool_index(4) = 1.046152384161304;
  cool_index(5) = 0.9710485219709948;
  cool_index(6) = 0.9187178699038683;
  cool_index(7) = 0.8622768271897759;
  cool_index(8) = 0.8112975142592808;
  cool_index(9) = 0.764383835848322;
  cool_index(10) = 0.7215065145376907;
  cool_index(11) = 0.6837339103228488;
  cool_index(12) = 0.6496968708602496;
  cool_index(13) = 0.6226517358704278;
  cool_index(14) = 0.6003482716728716;
  cool_index(15) = 0.5842060448744487;
  cool_index(16) = 0.5731409921530503;
  cool_index(17) = 0.57263910660426;
  cool_index(18) = 0.5781254636915297;
  cool_index(19) = 0.5729173969098684;
  cool_index(20) = 0.5842291881279158;
  cool_index(21) = 0.6017287713092797;
  cool_index(22) = 0.586474579373514;
  cool_index(23) = 0.5299656970874005;
  cool_index(24) = 0.7555410042219408;
  cool_index(25) = 1.8208029135454589;
  cool_index(26) = 13.15425144225546;
  cool_index(27) = 20.382914769958912;
  cool_index(28) = 11.152418326696527;
  cool_index(29) = 1.6050740479547532;
  cool_index(30) = -1.1717929030386005;
  cool_index(31) = -0.6066447840717054;
  cool_index(32) = 0.2742304563406291;
  cool_index(33) = 0.8113747307038128;
  cool_index(34) = 1.3416001078051365;
  cool_index(35) = 1.7637247035403647;
  cool_index(36) = 2.0887482888056486;
  cool_index(37) = 1.7755710606227835;
  cool_index(38) = 0.8026121322474284;
  cool_index(39) = 0.11285969173522381;
  cool_index(40) = -0.30619524373176354;
  cool_index(41) = 0.14474995991173714;
  cool_index(42) = 0.18386477764991632;
  cool_index(43) = 0.1122129637727278;
  cool_index(44) = -0.6671032354905164;
  cool_index(45) = -2.5686416665316867;
  cool_index(46) = -1.9319782274900217;
  cool_index(47) = -0.5024063252777698;
  cool_index(48) = -0.28913821103849996;
  cool_index(49) = -0.6821980210592937;
  cool_index(50) = -0.27147373677328274;
  cool_index(51) = 0.1284518607601927;
  cool_index(52) = -0.1320193815842161;
  cool_index(53) = -0.4668852864926393;
  cool_index(54) = -0.8189110836568699;
  cool_index(55) = -1.4944412314760238;
  cool_index(56) = -1.8971450002398187;
  cool_index(57) = -1.6425784274365576;
  cool_index(58) = -1.4403976677693775;
  cool_index(59) = -1.1445987542675535;
  cool_index(60) = -0.6396501455748754;
  cool_index(61) = -0.21218992452978713;
  cool_index(62) = 0.06101200902624875;
  cool_index(63) = 0.20323854503199934;
  cool_index(64) = 0.15783516300870554;
  cool_index(65) = -0.03345930970184931;
  cool_index(66) = -0.3155342720331987;
  cool_index(67) = -0.5761261809749756;
  cool_index(68) = -0.5933867008520205;
  cool_index(69) = -0.3637697533048537;
  cool_index(70) = -0.11590027637233989;
  cool_index(71) = 0.05880716047606841;
  cool_index(72) = 0.2309185630982361;
  cool_index(73) = 0.3111763931415481;
  cool_index(74) = 0.35415398081936483;
  cool_index(75) = 0.37928936217708137;
  cool_index(76) = 0.3922656333556603;
  cool_index(77) = 0.3951155169931811;
  cool_index(78) = 0.41511486020673116;
  cool_index(79) = 0.4651736861681356;

  // cool_index(0) = 5.455488390256632;
  // cool_index(1) = 5.076170519863754;
  // cool_index(2) = -0.5020655826640291;
  // cool_index(3) = -1.7055659800651979;
  // cool_index(4) = -0.5399688186820728;
  // cool_index(5) = 0.550609170202909;
  // cool_index(6) = 1.4527662908446985;
  // cool_index(7) = 2.0172644735605223;
  // cool_index(8) = 1.773197476674277;
  // cool_index(9) = 0.6282445620956022;
  // cool_index(10) = -0.2747076405016009;
  // cool_index(11) = 0.07013182420220869;
  // cool_index(12) = 0.32752568568776125;
  // cool_index(13) = 0.1883881016798681;
  // cool_index(14) = -1.6570303755459093;
  // cool_index(15) = -1.209120245966656;
  // cool_index(16) = -0.17533183860418153;
  // cool_index(17) = -1.0512755674245657;
  // cool_index(18) = -0.896664392554265;
  // cool_index(19) = -0.16540667885641686;
  // cool_index(20) = -0.43250361812273735;
  // cool_index(21) = -0.4775539072045259;
  // cool_index(22) = -1.0956186284443203;
  // cool_index(23) = -1.453147878451421;
  // cool_index(24) = -1.3412596915753237;
  // cool_index(25) = -1.0051719479026813;
  // cool_index(26) = -0.573142729390977;
  // cool_index(27) = -0.3457087236213044;
  // cool_index(28) = -0.08698732111048613;
  // cool_index(29) = -0.07335511773234596;
  // cool_index(30) = -0.3119882060952377;
  // cool_index(31) = -0.6835132944311395;
  // cool_index(32) = -0.6549261784681947;
  // cool_index(33) = -0.2804886559029823;
  // cool_index(34) = 0.05737205818565948;
  // cool_index(35) = 0.30836313806582183;
  // cool_index(36) = 0.3580735000106496;
  // cool_index(37) = 0.3293929876114671;
  // cool_index(38) = 0.24620665148692336;
  // cool_index(39) = 0.10953503955831644;

  // Calculate All TEFs Y_k recursively (Eq. A6)
  cool_tef(nbins-1) = 0.0; // Last Y_N = 0
  for (int i=nbins-2; i>=0; i--) {
    Real t_n    = cool_t(nbins-1);
    Real coef_n = cool_coef(nbins-1);

    Real t_i   = cool_t(i);
    Real tef_i = cool_tef(i);
    Real coef  = cool_coef(i);
    Real slope = cool_index(i);

    Real sm1  = slope - 1.0;
    Real step = (coef_n/coef)*(t_i/t_n)*(std::pow(t_i/cool_t(i+1),sm1)-1)/sm1;
    cool_tef(i) = cool_tef(i+1) - step;
  }

  // Set temperature floor
  tfloor = cool_t(0);


  if (DEBUG_FLAG){
    printf("End of Cooling::Cooling!\n");
  }

}

Cooling::~Cooling() {
  cool_t.DeleteAthenaArray();
  cool_tef.DeleteAthenaArray();
  cool_coef.DeleteAthenaArray();
  cool_index.DeleteAthenaArray();
}

// Exact Integration Scheme for Radiative Cooling from Townsend (2009)
// Returns: Temperature(K) at the next timestep after cooling
// Requires: - Input temperature, density, and timestep in cgs units
//           - T < t_ceil and T > t_floor
//           - All cooling slopes are not equal to 1
//           - `Lambda_fac` can be used to increase (>1) or decrease (<1) cooling.
Real Cooling::townsend(Real temp, Real rho, Real const dt, Real Lambda_fac)
{

  if (DEBUG_FLAG){
    printf("Start of Cooling::townsend!\n");
  }

  if (DEBUG_FLAG){
    printf("Check that temperature is above the cooling floor\n");
  }
  // Check that temperature is above the cooling floor
  // if (temp < tfloor) return tfloor;


  if (DEBUG_FLAG){
    printf("Get Reference values from the last bin\n");
  }
  // Get Reference values from the last bin
  Real t_n    = cool_t(nbins-1);
  Real coef_n = cool_coef(nbins-1) * Lambda_fac;


  if (DEBUG_FLAG){
    printf("Get the index of the right temperature bin\n");
  }

  // TODO: Change to binary search or direct calculation
  // Get the index of the right temperature bin
  int idx = 0;
  while ((idx < nbins-2) && (cool_t(idx+1) < temp)) { idx += 1; }

  // t_n    = cool_t(idx+2);
  // coef_n = cool_coef(idx+2) * Lambda_fac;

  if (DEBUG_FLAG){
    printf("Look up the corresponding slope and coefficient\n");
  }
  // Look up the corresponding slope and coefficient
  Real t_i   = cool_t(idx);
  Real tef_i = cool_tef(idx);
  Real coef  = cool_coef(idx) * Lambda_fac;
  Real slope = cool_index(idx);

  if (DEBUG_FLAG){
    printf("Compute the Temporal Evolution Function Y(T) (Eq. A5)\n");
  }
  // Compute the Temporal Evolution Function Y(T) (Eq. A5)
  Real sm1 = slope - 1.0;
  Real tef = tef_i + (coef_n/coef)*(t_i/t_n)*(std::pow(t_i/temp,sm1)-1)/sm1;

  if (DEBUG_FLAG){
    printf("Compute the adjusted TEF for new timestep (Eqn. 26)\n");
  }
  // Compute the adjusted TEF for new timestep (Eqn. 26)
  Real tef_adj = tef + rho*coef_n*const_factor*dt/t_n;

  if (DEBUG_FLAG){
    printf("TEF is a strictly decreasing function and new_tef > tef\n");
  }
  // TEF is a strictly decreasing function and new_tef > tef
  // Check if the new TEF falls into a lower bin
  // If so, update slopes and coefficients
  while ((idx > 0) && (tef_adj > cool_tef(idx))) {
    idx -= 1;
    t_i   = cool_t(idx);
    tef_i = cool_tef(idx);
    coef  = cool_coef(idx) * Lambda_fac;  //* Later correction
    slope = cool_index(idx);
  }

  if (DEBUG_FLAG){
    printf("Compute the Inverse Temporal Evolution Function Y^{-1}(Y) (Eq. A7)\n");
  }
  // Compute the Inverse Temporal Evolution Function Y^{-1}(Y) (Eq. A7)
  Real oms  = 1.0 - slope;
  // Real tnew = temp;

  Real tnew = t_i*std::pow(1-oms*(coef/coef_n)*(t_n/t_i)*(tef_adj-tef_i),1/oms);
  
  if (idx == 0) {
    tnew = t_i*std::exp(-1.0*(coef/coef_n)*(t_n/t_i)*(tef_adj-tef_i));
    printf("Got idx==0 \n");
  }


  if (DEBUG_FLAG){

    printf("\n\ntnew = %lf \n\n t_n = %lf\n t_i = %lf \n", tnew, t_n, t_i);
    printf("coef = %lf \n coef_n = %lf \n", coef, coef_n);
    printf("tef_adj = %lf \n tef_i = %lf \n", tef_adj, tef_i);
    printf("idx = %d \n slope = %lf \n oms = %lf \n", idx, slope, oms);

    printf("End of Cooling::townsend!\n");
  }
  // Return the new temperature if it is still above the temperature floor
  //return std::max(tnew,tfloor);
  return tnew;
}


// Lambda(T)
// Returns: Lambda(T) in [1e-2e ergs*cm3/s], nan if T oob
// Requires: - Input temperature in K
Real Cooling::Lambda(Real temp)
{

  if (DEBUG_FLAG){
    printf("Start of Cooling::Lambda!\n");
  }

  // Check that temperature is not oob
  if((temp < cool_t(0)) || (temp > cool_t(nbins - 1)))
     return NAN;
     
  // Get the index of the right temperature bin
  int idx = 0;
  while ((idx < nbins-2) && (cool_t(idx+1) < temp)) { idx += 1; }

  // Look up the corresponding slope and coefficient
  Real t_i   = cool_t(idx);
  Real coef  = cool_coef(idx);
  Real slope = cool_index(idx);

  if (DEBUG_FLAG){
    printf("End of Cooling::Lambda!\n");
  }

  return coef * pow(temp / t_i, slope);
}


// tcool(T,rho)
// Returns: tcool [s], nan if T oob
// Requires: - Input temperature in K
//           - Input density in g
Real Cooling::tcool(Real temp, Real rho)
{
  if (DEBUG_FLAG){
    printf("Start of Cooling::tcool!\n");
  }
  // Check that temperature is not oob
  if((temp < cool_t(0)) || (temp > cool_t(nbins - 1)))
     return NAN;

  Real L = Cooling::Lambda(temp);

  if (DEBUG_FLAG){
    printf("End of Cooling::tcool!\n");
  }

  return temp / (const_factor * rho * L);
}

#endif
