#include <iostream>
#include <stdlib.h>
#include "./include/mol_sys.h"
#include "./include/molecule.h"
#include "./include/defined.h"

#define SIZE_OF_ARRAY(A) (sizeof(A) / sizeof(A[0]))

using namespace std;

int main(int argc, char* argv[])
{

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

	std::vector<Molecule> molecules(max_mol); //default initialize the vectors --with lc-mols

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
	std::vector<double> temperature_range(temp_range, temp_range + temp_size);


	//TODO: put it in a funciton.
	double init_spin[] = INIT_SPIN;
	int init_spin_size = SIZE_OF_ARRAY(init_spin);
	std::vector<double> initial_spin(init_spin, init_spin + init_spin_size);
	//check dimensions:
	if (init_spin_size != DIMENSIONS)
	{
		cout << "dimensions of INIT_SPIN is " << init_spin_size << " and it doesn't match with DIMENSIONS which is " << DIMENSIONS << "\n";
		exit(EXIT_FAILURE);
	}


	//what happen if the distribution will ge us out of the system?



#if DIMENSIONS == 2
	for (int i = 0; i < molecules_in_each_directions[0]; i++)
	{
		for (int j = 0; j < molecules_in_each_directions[1]; j++)
		{
			int molecule_to_manipulate = molecules_in_each_directions[1] * i + j;
			molecules[molecule_to_manipulate].m_location[0] = i * INIT_SPACING;
			molecules[molecule_to_manipulate].m_location[1] = j * INIT_SPACING;
			molecules[molecule_to_manipulate].m_spin[0] = initial_spin[0];
			molecules[molecule_to_manipulate].m_spin[1] = initial_spin[1];
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
				molecules[molecule_to_manipulate].m_location[0] = i * INIT_SPACING;
				molecules[molecule_to_manipulate].m_location[1] = j * INIT_SPACING;
				molecules[molecule_to_manipulate].m_location[2] = k * INIT_SPACING;
				molecules[molecule_to_manipulate].m_spin[0] = initial_spin[0];
				molecules[molecule_to_manipulate].m_spin[1] = initial_spin[1];
				molecules[molecule_to_manipulate].m_spin[2] = initial_spin[2];
			}
		}
	}
#endif //DIMENSIONS

	///initiate the random generators:
	srand((unsigned int)time(0));
	std::default_random_engine loc_gen((unsigned int)time(0));
	std::normal_distribution<double> loc_dist(0.0, INIT_SPACING_STD);

	std::default_random_engine spin_gen((unsigned int)time(0));
	std::normal_distribution<double> spin_dist(0.0, INIT_SPIN_STD);

	for (unsigned int i = 0; i < molecules.size(); i++)
	{
		//change the location with std of location:
		for (int j = 0; j < DIMENSIONS; j++)
		{
			double suggested_init_loc;
			do
			{
				suggested_init_loc = molecules[i].m_location[j] + loc_dist(loc_gen);
			} while ((suggested_init_loc < 0) || (suggested_init_loc > sys_sizes[j]));
			molecules[i].m_location[j] = suggested_init_loc;
		}

		//change spin with the std of the spin and normalize it:
		double norm_spin = 0;
		for (int j = 0; j < DIMENSIONS; j++)
		{
			molecules[i].m_spin[j] = molecules[i].m_spin[j] + spin_dist(spin_gen);
			norm_spin += (molecules[i].m_spin[j] * molecules[i].m_spin[j]);
		}
		norm_spin = sqrt(norm_spin);
		for (int j = 0; j < DIMENSIONS; j++)
		{
			molecules[i].m_spin[j] = molecules[i].m_spin[j] / norm_spin;
		}
	}

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

//here we can call to some function that will modify the system if user want to.

	Model * model = new Model();
	Mol_Sys * lc_system = new Mol_Sys(sys_sizes, molecules, temperature_range, model);
	lc_system->start_cooling();
	delete lc_system;
	delete model;

	cout << "finished successfully";
	scanf("finished");
}

