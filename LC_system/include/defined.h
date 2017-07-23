#ifndef DEFINED_H_INCLUDED
#define DEFINED_H_INCLUDED
///mathematical defined:
#define PI 3.1415926535897
#define K_B 1.38066e-23

/// model defined:
#define MODEL_NAME "simple_debug1" ///the model name, this will be the folder name in the run directory

#define DIMENSIONS 2
#define MOLECULES_IN_EACH_DIRECTION {10,10} /// #moleuclues will be the product of all elements.
#define SYSTEM_SIZES {1000,1000} /// the location of the molecules cant exceed the size of the system.

/// colloid molecules - define all the molecules in the system
#define COLLOID_MOLS {\
    {0,2},\
    {1,0} }

#define INIT_SPACING 1.0///the expected value of the inital location of the molecules
#define INIT_SPIN {1/sqrt(2), 1/sqrt(2)} ///the expected value of the inital orientation of the molecules

#define INIT_SPACING_STD 1.0 ///the standart deviation of the inital location of the location
#define INIT_SPIN_STD 1.0 ///the standart deviation of the inital location of the spin

#define TEMPERATURE_RANGE {3.1, 2.1, 1.0}  ///temperature range of the monte carlo

#define NUMBER_OF_STEPS 5000 ///number of steps in each temperature

#define STD_LOCATION 0.001 ///the standart deviation of the location in the monte carlo
#define STD_SPIN 0.05 ///the standart deviation of the orientation in the monte carlo

//L > D
#define D_0 0.6 /// the small size of the liquid crystal molecule.
#define L_0 1.8 /// the long size of the liquid crystal molecule

#define D_1 4.5 /// the radius of the colloid molecule
#define L_1 4.5001 ///D_1 + very small number, just to allow the expression (L_1 - D_1) / (L_1 - D_1)

#define EPSILON0_0 K_B ///the epsilon0 of the LC
#define EPSILON0_1 K_B ///the epsilon0 of the col


#define EE_DIV_ES_0 1.0 ///the ratio of the corresponding to the end-to-end arrengment vs the corosponding to the side-by-side arrangement, for the LC.
#define EE_DIV_ES_1	1.0 ///same for the colloide.

//miu and ni are adjustable parameters
#define MIU 1.0 ///parameter taken into account the location between the molecules as well as the spin.
#define NI 1.0 ///parameter taken into account only the orientation between the molecules.

#define DIF_ANGLES_COL_REPRESENTATION 30 ///the colloide is represented by a lot of LC like molecules locating in the same place
				///this parameter influence what is the difference between each 2 lines (LC like molecules), this is in degrees.
//the number should be divide in 180
///programming  and debug defined:
#define DEBUG 100
#define SHOW_TEMP_TIMMING
//#define PRINT_STEP_NUM

enum Mol_Type {lc, col};


#endif // DEFINED_H_INCLUDED
