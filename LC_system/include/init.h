#ifndef INIT_H
#define INIT_H

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <random>

#include "./defined.h"
#include "molecule.h"

#define SIZE_OF_ARRAY(A) (sizeof(A) / sizeof(A[0]))

using namespace std;
/// this is a static class (constructor in private) contating all the function to initialize the system.

class Init
{
    public:
		static vector<int> Init::get_mols_each_dir();

		static vector<double> Init::get_sys_sizes();

		static vector< vector<int> > Init::get_col_indices();

		static vector<double> Init::get_temp_range();

		static vector<double> Init::get_init_spin();

		static vector<Molecule> get_molecules(const vector<int> & molecules_in_each_directions, const vector<double> & initial_spin);

		static void add_randomization(vector<Molecule> & molecules, const vector< vector<int> > & colloid_molecules,
			const vector<int> & molecules_in_each_directions, const vector<double> & sys_sizes);

    protected:

    private:
		//static class, private constuctor.
		Init();
		virtual ~Init();
};

#endif // INIT_H
