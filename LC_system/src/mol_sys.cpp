#include "./../include/mol_sys.h"

Mol_Sys::Mol_Sys(vector<double> & sys_sizes, vector<Molecule> & mols, vector<double> temperature_range, Model* model)
	:m_sys_sizes(sys_sizes), m_molecules(mols), m_temperature_range(temperature_range), m_model(model)
{
	for (unsigned int i = 0; i < m_molecules.size(); i++)
	{
		vector<double> pot(m_molecules.size());
		m_pair_potentials.push_back(pot);
	}

	for (unsigned int i = 0; i < m_molecules.size(); i++)
		for (unsigned int j = i + 1; j < m_molecules.size(); j++)
			m_pair_potentials[i][j] = m_molecules[i].potential(&m_molecules[j], m_model);

	update_sys_potential();
}


Mol_Sys::~Mol_Sys()
{
	//dtor
}

void Mol_Sys::update_sys_potential()
{
	///update the system potential based on the pair potential of all the molecules.

	/// this function is less performance sensitive so we dont mind doing things twice:
	double potential = 0.0;
	for (unsigned int i = 0; i < m_molecules.size(); i++)
	{
		potential += get_all_pair_potential_of_index(i);
	}
	///since we calculated the pair potential i,j for each pair twice, once for i and once for j we need to divide by two
	m_potential = potential / 2;
}

void Mol_Sys::start_cooling()
{
#ifdef SHOW_TEMP_TIMMING
	clock_t prev, curr;
	double duration;
	curr = clock();
#endif // SHOW_TEMP_TIMMING

	/// in future will use some module how to cool the system.
	/// currently will just perform x monte carlos for each temperature from the array.
	for (m_current_index_temp = 0; m_current_index_temp < m_temperature_range.size(); m_current_index_temp++)
	{

		/// need to add print of the system here to xyz.
		/// first implement just a simple print
		monte_carlo();
#ifdef SHOW_TEMP_TIMMING
		prev = curr;
		curr = clock();
		duration = (curr - prev) / (double)CLOCKS_PER_SEC;
		cout << "temperature index " << m_current_index_temp << " took " << duration << " secs" << endl;

#endif // SHOW_TEMP_TIMMING
	}
}

double Mol_Sys::get_all_pair_potential_of_index(unsigned int index)
{
	///get the column potential:
	double potential = 0.0;
	for (unsigned int i = 0; i < index; i++)
		potential += m_pair_potentials[i][index];

	///get the row potential:
	for (unsigned int i = index + 1; i < m_molecules.size(); i++)
		potential += m_pair_potentials[index][i];

	return potential;
}

void Mol_Sys::update_sys(Molecule &mol_chosen, unsigned int index, double* potential, double tot_pot_update)
{
	///inputs:
	/// Molecule mol_chosen: molecule to update.
	/// int index: the index of the molecule to update.
	/// double* potential: an array of all the new pair potential (size of m_molecules_size)
	///         potential[index] is undefined and should not use!!
	///
	/// the function update the system with the new vars.


	///update the molecule
	m_molecules[index] = mol_chosen;

	///update the pair potential:

	///update the column:
	for (unsigned int i = 0; i < index; i++)
		m_pair_potentials[i][index] = potential[i];

	///update the rows:
	for (unsigned int i = index + 1; i < m_molecules.size(); i++)
		m_pair_potentials[index][i] = potential[i];

	m_potential += tot_pot_update;




}

void Mol_Sys::monte_carlo()
{
	/** for each step:
		choose molecule randomly
		change location and spin with gauss distribution
		calculate dE
		if dE<0 take the step
		if not take the step with probability of e^-dE/Kb*T */

	int num_mol_chosen;
	double prob, dE, current_total_pot, suggested_location, suggested_spin, spin_norm = 0, temp_total_pot = 0;
	double * potential;
	Molecule mol_chosen;

	///initiate the random generators:
	srand((unsigned int)time(0));
	std::default_random_engine loc_gen((unsigned int)time(0));
	std::normal_distribution<double> loc_dist(0.0, STD_LOCATION);

	std::default_random_engine spin_gen((unsigned int)time(0));
	std::normal_distribution<double> spin_dist(0.0, STD_SPIN);

	/*std::random_device;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0, 1); */

	for (int i = 0; i < NUMBER_OF_STEPS; i++)
	{
#ifdef PRINT_STEP_NUM
		cout << "doing step " << i << endl;
#endif //DEBUG

		///choose molecule:
		num_mol_chosen = rand() % m_molecules.size();

		///change location around gauss dist:
		mol_chosen = m_molecules[num_mol_chosen];
		for (unsigned int j = 0; j < mol_chosen.m_location.size(); j++)
		{
#if DEBUG >= 3
			unsigned int counter = 0;
#endif //DEBUG
			///it's actually multivariate normal distribution where E=loc, std=std given, and no correlation between the axis.
			do
			{
#if DEBUG >= 3
				counter++;
				if (counter > 500)
				{
					cout << "you probably gave location for molecule such that it excceed dimension " << j << "\n";
					exit(EXIT_FAILURE);
				}
#endif //DEBUG
				suggested_location = mol_chosen.m_location[j] + loc_dist(loc_gen);
			} while ((suggested_location > m_sys_sizes[j]) || (suggested_location < 0) );
			mol_chosen.m_location[j] = suggested_location;
		}

		for (unsigned int j = 0; j < mol_chosen.m_spin.size(); j++)
		{
			///it's actually multivariate normal distribution where E=loc, std=std given, and no correlation between the axis.
			suggested_spin = mol_chosen.m_spin[j] + spin_dist(spin_gen);
			mol_chosen.m_spin[j] = suggested_spin;
			spin_norm += suggested_spin;
		}
		for (unsigned int j = 0; j < mol_chosen.m_spin.size(); j++)
			mol_chosen.m_spin[j] /= spin_norm;


		/// we now have the location vector and the spin vector suggested, now we have to calculate dE for them
		///since all changed is this 1 molecule we will:
		/// calculate row of for the potential done by this molecule
		potential = new double[m_molecules.size()];
		for (unsigned int j = 0; j < m_molecules.size(); j++)
		{
			if (j == num_mol_chosen) continue;
			potential[j] = mol_chosen.potential(&m_molecules[j], m_model);
			temp_total_pot += potential[j];
		}
		current_total_pot = get_all_pair_potential_of_index(num_mol_chosen);
		if (temp_total_pot <= current_total_pot)
		{
			update_sys(mol_chosen, num_mol_chosen, potential, temp_total_pot - current_total_pot);
		}
		else
		{
			prob = ((double)rand() / (RAND_MAX));
			dE = get_all_pair_potential_of_index(num_mol_chosen) - temp_total_pot;
			if (prob < exp(dE / (m_temperature_range[m_current_index_temp] * K_B)))
			{
				update_sys(mol_chosen, num_mol_chosen, potential, temp_total_pot - current_total_pot);
			}
		}
		delete[] potential;
		//no need to delete mol_chosen since it wan't created by new it limited to this scope.
	}
}

