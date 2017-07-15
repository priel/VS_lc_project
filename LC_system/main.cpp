#include <iostream>
#include <stdlib.h>
#include "./include/mol_sys.h"
#include "./include/molecule.h"
#include "./include/defined.h"

#define SIZE_OF_ARRAY(A) (sizeof(A)/sizeof(A[0]))

using namespace std;

int main(int argc, char* argv[])
{
	/// here we just want to do some basic configuration for debug.
	/// lets try with simple 3x3 2d.

	/* Mol_Sys(double* sys_sizes, int dimensions, Molecule *mols, int max_mol,
			double std_loc, double std_spin, double *temp_range, int temp_size, int steps); */


	int steps = 10;
	double std_loc = 1, std_spin = 1;

	//TODO put it in function
	double sys_size[] = SYSTEM_SIZES;
	int max_sys_size = SIZE_OF_ARRAY(sys_size);
	if (max_sys_size != DIMENSIONS)
	{
		printf("SYSTEM_SIZE is %d and it doesn't match with DIMENSIONS which is %d\n", max_sys_size, DIMENSIONS);
		exit(EXIT_FAILURE);
	}
	std::vector<double>  sys_sizes(sys_size, sys_size + sizeof(sys_size) / sizeof(sys_size[0]));

	//TODO: put it in function
	int max_mol = 1;
	int mols_in_directions[] = MOLECULES_IN_EACH_DIRECTION;
	int max_mols_each_direction_size = SIZE_OF_ARRAY(mols_in_directions);
	if (max_mols_each_direction_size != DIMENSIONS)
	{
		printf("MOLECULES_IN_EACH_DIRECTION is %d and it doesn't match with DIMENSIONS which is %d\n", max_mols_each_direction_size, DIMENSIONS);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < DIMENSIONS; i++)
		max_mol *= mols_in_directions[i];

	//TODO: put it in function
	double temp_range[] = TEMPERATURE_RANGE;
	int temp_size = SIZE_OF_ARRAY(temp_range);
	std::vector<double> temperature_range(temp_range, temp_range + sizeof(temp_range) / sizeof(temp_range[0]));

	std::vector<Molecule> molecules(max_mol); //default initialize the vectors --with lc-mols
	Molecule *mols = new Molecule[max_mol];


	//TODO: here should be some kind of STD for the locations and the orientation.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			molecules[3 * i + j].m_location[0] = i;
			molecules[3 * i + j].m_location[1] = i;
			molecules[3 * i + j].m_spin[0] = 1;
		}
	}

	Model * model = new Model(0.6, 1.8, 4.5, 4.5001, K_B, K_B, 1.0, 3.0, 1.0, 1.0);
	Mol_Sys * lc_system = new Mol_Sys(sys_size, mols, max_mol, std_loc, std_spin, temp_range, temp_size, steps, model);
	lc_system->start_cooling();
	delete lc_system;
	delete model;

	scanf("finished");
}
/// after a bit of investigation, better use only vectors and not arrays.
/// should convert all arrays into vectors.
