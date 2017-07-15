#ifndef DEFINED_H_INCLUDED
#define DEFINED_H_INCLUDED

#define K_B 1.38066e-23

/// model defined:
#define MODEL_NAME "simple_debug1"

#define DIMENSIONS 3
#define MOLECULES_IN_EACH_DIRECTION {2,3} /// #moleuclues will be the product of all elements.
#define SYSTEM_SIZES {3,3}

/// colloid molecules
#define COLLOID_MOLS {\
    {0,0},\
    {1,1} }

#define TEMPERATURE_RANGE {3.1, 2.1, 1.0}  //temperature range of the monte carlo

#define NUMBER_OF_STEPS 50///number of steps in each temperature

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

/// debug defined:
#define DEBUG 1
#define PRINT_DEBUG_INFO 1
#define PRINT_DEBUG_POTENTIAL 1
#define PRINT_EACH_POTENTIAL 1
#define PRINT_LOCATION 1
#define PRINT_INITIAL 1
#define PRINT_SPIN 1

///physical defined:

enum Mol_Type {lc, col};

#endif // DEFINED_H_INCLUDED
