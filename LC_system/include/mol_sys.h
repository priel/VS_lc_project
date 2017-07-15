#ifndef MOL_SYS_H
#define MOL_SYS_H

#include <time.h>
#include <cstdlib>
#include <random>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "./mol_sys.h"
#include "./defined.h"
#include "./molecule.h"
#include "./model.h"

using namespace std;

class Mol_Sys
{
    public:

        /** the default constructor will do everything by itself.
        will create a Gaussian distribution where the STD and expected is given. **/

        /** this is some kind of custom constructor where all the parameters are pre-defined.**/
        Mol_Sys(vector<double> & sys_sizes, vector<Molecule> & mols, vector<double> temperature_range, Model* model);

        /** the destructor will delete all the data here and all the molecules. */
        ~Mol_Sys();

        vector<double> m_sys_sizes; ///array in the length of dimensions which determine the x,y,(z) of the system.

		vector<Molecule> m_molecules; /// ///pointer to the first molecule array.

        double m_potential; /// hold the current system total potential

		vector< vector<double> > m_pair_potentials; /// have all the pairs of potential for example pair_potential[0][1] has the potential between molecule 0 and 1.
												    ///the last column has the sum potential of this
        /** example of potentials as a matrix for m_molecules.size()=4:
            0   1   2   3
        0  N/A 2.0 1.0 2.1
        1  N/A N/A 2.1 1.2
        2  N/A N/A N/A 1.0
        3  N/A N/A N/A N/A   //this is not really needed and just here for simplicity.
        */

        // We could have saved more memory by defining only the triangle, however it left that way for simplicity of the code.
		// if memory will become an issue we can change this.

		vector<double> m_temperature_range; ///hold the range of temperature we want to check (Starting from 0 to max_temp -1;
		unsigned int m_current_index_temp;

        Model* m_model;

        /** the public functions: */

        /// update the system potential based on the pair potential
        void update_sys_potential();

        void start_cooling();
        /// in future will use some module how to cool the system.
        /// currently will just perform x monte carlos for each temperature from the array.

        double get_all_pair_potential_of_index(unsigned int index);
		///get the potential of all the pairs with the index

        void update_sys(Molecule &mol_chosen, unsigned int index, double* potential, double tot_pot_update);
        /// in charge of updating the system.

        void monte_carlo();
        ///doing NUMBER_OF_STEPS times monte carlo steps


    protected:

    private:
		Mol_Sys(); /// no default constructr should be in use, arguments must be provided.
};

#endif // MOL_SYS_H
