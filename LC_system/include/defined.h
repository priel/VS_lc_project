#ifndef DEFINED_H_INCLUDED
#define DEFINED_H_INCLUDED

/// model defined:
#define MODEL_NAME "simple_debug1"

#define DIMENSIONS 2
#define MOLECULES_IN_EACH_DIRECTION {2,3} /// #moleuclues will be the product of all elements.
#define SYSTEM_SIZES {3,3}

/// colloid molecules
#define COLLOIDE_MOLS {\
    {0,0},\
    {1,1} }

#define TEMPERATURE_RANGE {3.1, 2.1, 1.0}  //temperature range of the monte carlo

#define NUMBER_OF_STEPS ///number of steps in each temperature

#define STD_LOCATION
#define STD_SPIN

#define D_0
#define L_0

#define D_1
#define L_1

#define EPSILON0_0
#define EPSILON0_1

#define MIU
#define NI

#define EE_DIV_ES_0
#define EE_DIV_ES_1

/// debug defined:
#define DEBUG 1
#define PRINT_DEBUG_INFO 1
#define PRINT_DEBUG_POTENTIAL 1
#define PRINT_EACH_POTENTIAL 1
#define PRINT_LOCATION 1
#define PRINT_INITIAL 1
#define PRINT_SPIN 1

///physical defined:
#define K_B 1.38066e-23
enum Mol_Type {lc, col};

#endif // DEFINED_H_INCLUDED
