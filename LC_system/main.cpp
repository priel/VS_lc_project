#include <iostream>
#include <stdlib.h>
#include "./include/mol_sys.h"
#include "./include/molecule.h"
#include "./include/defined.h"

#define SIZE_OF_ARRAY(A) (sizeof(A) / sizeof(A[0]))

using namespace std;

int main(int argc, char* argv[])
{
	/// here we just want to do some basic configuration for debug.
	/// lets try with simple 3x3 2d.

	/* Mol_Sys(double* sys_sizes, int dimensions, Molecule *mols, int max_mol,
			double std_loc, double std_spin, double *temp_range, int temp_size, int steps); */

	double std_loc = 1, std_spin = 1;

	//TODO put it in a function
	double sys_size[] = SYSTEM_SIZES;
	int max_sys_size = SIZE_OF_ARRAY(sys_size);
	if (max_sys_size != DIMENSIONS)
	{
		cout << "dimensions of SYSTEM_SIZE is " << max_sys_size << " and it doesn't match with DIMENSIONS which is " << DIMENSIONS << "\n";
		exit(EXIT_FAILURE);
	}
	std::vector<double> sys_sizes(sys_size, sys_size + max_sys_size);

	//TODO: put it in a function
	int max_mol = 1;
	int mols_in_directions[] = MOLECULES_IN_EACH_DIRECTION;
	int max_mols_each_direction_size = SIZE_OF_ARRAY(mols_in_directions);
	if (max_mols_each_direction_size != DIMENSIONS)
	{
		cout << "dimensions of MOLECULES_IN_EACH_DIRECTION is " << max_mols_each_direction_size << " and it doesn't match with DIMENSIONS which is " << DIMENSIONS << "\n";
		exit(EXIT_FAILURE);
	}
	std::vector<int> molecules_in_each_directions(mols_in_directions, mols_in_directions + max_mols_each_direction_size);

	for (unsigned int i = 0; i < DIMENSIONS; i++)
		max_mol *= molecules_in_each_directions[i];

	//TODO: put it in a fucntion
	int coll_mols[][DIMENSIONS] = COLLOID_MOLS;
	int max_coll_mols = SIZE_OF_ARRAY(coll_mols);
	vector< vector<int> > colloid_molecules;
	for (int i = 0; i < max_coll_mols; i++)
	{
		vector<int> coll_indices(coll_mols[i], coll_mols[i] + DIMENSIONS);
		colloid_molecules.push_back(coll_indices);
	}
	

	//TODO: put it in a function
	double temp_range[] = TEMPERATURE_RANGE;
	int temp_size = SIZE_OF_ARRAY(temp_range);
	std::vector<double> temperature_range(temp_range, temp_range + SIZE_OF_ARRAY(temp_range));

	//TODO: put it in a function
	std::vector<Molecule> molecules(max_mol); //default initialize the vectors --with lc-mols

	//TODO: here should be some kind of randomness for the locations and the orientation.

#if DIMENSIONS == 2
	for (int i = 0; i < molecules_in_each_directions[0]; i++)
	{
		for (int j = 0; j < molecules_in_each_directions[1]; j++)
		{
			int molecule_to_manipulate = molecules_in_each_directions[1] * i + j;
			molecules[molecule_to_manipulate].m_location[0] = i;
			molecules[molecule_to_manipulate].m_location[1] = j;
			molecules[molecule_to_manipulate].m_spin[0] = 1;
		}
	}
#elif DIMENSIONS == 3
	for (int i = 0; i < molecules_in_each_directions[0]; i++)
	{
		for (int j = 0; j < molecules_in_each_directions[1]; j++)
		{
			for (int k = 0; k < molecules_in_each_directions[2]; k++)
			{
				int molecule_to_manipulate = molecules_in_each_directions[2] * molecules_in_each_directions[1] * i + molecules_in_each_directions[2] * j + k;
				molecules[molecule_to_manipulate].m_location[0] = i;
				molecules[molecule_to_manipulate].m_location[1] = j;
				molecules[molecule_to_manipulate].m_location[2] = k;
				molecules[molecule_to_manipulate].m_spin[0] = 1;
			}
		}
	}
#endif //DIMENSIONS


#if DIMENSIONS == 2
	for (unsigned int i = 0; i < colloid_molecules.size(); i++)
	{
		int index_to_manipulate = molecules_in_each_directions[1] * colloid_molecules[i].at(0) + colloid_molecules[i].at(1);
		molecules[index_to_manipulate].m_mol_type = col;
	}
#elif DIMENSIONS == 3
	for (unsigned int i = 0; i < colloid_molecules.size(); i++)
	{
		int index_to_manipulate = molecules_in_each_directions[2] * molecules_in_each_directions[1] * colloid_molecules[i].at(0)
											+ molecules_in_each_directions[1] * colloid_molecules[i].at(1)
												+ colloid_molecules[i].at(2);
		molecules[index_to_manipulate].m_mol_type = col;
	}
#endif // DIMENSIONS


	Model * model = new Model();
	Mol_Sys * lc_system = new Mol_Sys(sys_sizes, molecules, temperature_range, model);
	lc_system->start_cooling();
	delete lc_system;
	delete model;

	cout << "finished successfully";
	scanf("finished");
}
/// after a bit of investigation, better use only vectors and not arrays.
/// should convert all arrays into vectors.
