#ifndef DEFINED_H_INCLUDED
#define DEFINED_H_INCLUDED

#define K_B 1.38066e-23

/// model defined:
#define MODEL_NAME "simple_debug1"

#define DIMENSIONS 2
#define MOLECULES_IN_EACH_DIRECTION {10,10} /// #moleuclues will be the product of all elements.
#define SYSTEM_SIZES {1000,1000}

/// colloid molecules
#define COLLOID_MOLS {\
    {0,2},\
    {1,0} }

#define INIT_SPACING 1.0
#define INIT_SPIN {1/sqrt(2), 1/sqrt(2)}

#define INIT_SPACING_STD 1.0
#define INIT_SPIN_STD 1.0

#define TEMPERATURE_RANGE {3.1, 2.1, 1.0}  ///temperature range of the monte carlo

#define NUMBER_OF_STEPS 5000 ///number of steps in each temperature

#define STD_LOCATION 0.1
#define STD_SPIN 0.5

//L > D
#define D_0 0.6
#define L_0 1.8

#define D_1 4.5
#define L_1 4.5001

#define EPSILON0_0 K_B
#define EPSILON0_1 K_B

#define MIU 1.0
#define NI 1.0

#define EE_DIV_ES_0 1.0
#define EE_DIV_ES_1	1.0

///programming  and debug defined:
#define DEBUG 100
#define SHOW_TEMP_TIMMING
//#define PRINT_STEP_NUM

enum Mol_Type {lc, col};

#endif // DEFINED_H_INCLUDED
