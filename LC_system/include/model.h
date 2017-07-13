#ifndef MODEL_H
#define MODEL_H

#include <math.h>
#include "./defined.h"

/// this is a container to hold all the variables of the system.
/// this should be hold by the system in order to calculate the potential.
/// the length of the molecules also hold here for performance.
/// another approach would be that every molecule with hold their structure.

class Model
{
    public:
        Model(double d_0, double l_0, double d_1, double l_1, double epsilon_0_0, double epsilon_0_1,
               double miu, double ni, double ee_div_es_0, double ee_div_es_1 );
        virtual ~Model();

        double m_d_0;
        double m_l_0;

        double m_d_1;
        double m_l_1;

        double m_epsilon_0_0;
        double m_epsilon_0_1;

        double m_miu;
        double m_ni;

        double m_ee_div_es_0;
        double m_ee_div_es_1;

        double m_sigma_00;
        double m_sigma_11;
        double m_sigma_01;

        double m_chi_00;
        double m_chi_11;
        double m_chi_01;

        double m_alpha_00;
        double m_alpha_11;
        double m_alpha_01;


        double m_chi_tag_00;
        double m_chi_tag_11;
        double m_chi_tag_01;

        double m_alpha_tag_00;
        double m_alpha_tag_11;
        double m_alpha_tag_01;


    protected:

    private:
};

#endif // MODEL_H
