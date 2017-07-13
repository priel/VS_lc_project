#include "./../include/model.h"



Model::Model(double d_0, double l_0, double d_1, double l_1, double epsilon_0_0, double epsilon_0_1,
               double miu, double ni, double ee_div_es_0, double ee_div_es_1)
               :m_d_0(d_0), m_l_0(l_0), m_d_1(d_1), m_l_1(l_1), m_epsilon_0_0(epsilon_0_0), m_epsilon_0_1(epsilon_0_1),
               m_miu(miu), m_ni(ni), m_ee_div_es_0(ee_div_es_0), m_ee_div_es_1 (ee_div_es_1)
{
    m_sigma_00 = m_d_0;
    m_sigma_11 = m_d_1;
    m_sigma_01 = sqrt(pow(m_d_0, 2) + pow(m_d_1, 2) ) / 2.0;

    m_chi_00 = (pow(m_l_0/m_d_0, 2) - 1) / (pow(m_l_0/m_d_0, 2) + 1);
    m_chi_11 = (pow(m_l_1/m_d_1, 2) - 1) / (pow(m_l_1/m_d_1, 2) + 1);
    m_chi_01 = sqrt( (pow(m_l_0, 2) - pow(m_d_0, 2)) * (pow(m_l_1, 2) - pow(m_d_1, 2) )
               /(pow(m_l_1, 2) + pow(m_d_0, 2) ) / (pow(m_l_0, 2) + pow(m_d_1, 2)) );

    m_alpha_00 = 1.0;
    m_alpha_11 = 1.0;
    m_alpha_01 = pow(((pow(m_l_0, 2) - pow(m_d_0, 2) ) * (pow(m_l_1, 2) + pow(m_d_0, 2) )
               /  (pow(m_l_1, 2) - pow(m_d_1, 2) ) / (pow(m_l_0, 2) + pow(m_d_1, 2) ) ) ,0.25); // i=0,j=1

    m_epsilon_0_0 = K_B;
    m_epsilon_0_0 = K_B;


    m_chi_tag_00 = (1 - pow(m_ee_div_es_0 ,( 1 / m_miu )) / (1 + pow(m_ee_div_es_0,(1/ m_miu)) ) );
    m_chi_tag_11 = (1 - pow(m_ee_div_es_1 ,( 1 / m_miu )) / (1 + pow(m_ee_div_es_1,(1/ m_miu)) ) );
    m_chi_tag_01 = (1 - pow(m_ee_div_es_0 * m_ee_div_es_1, (1 / (2 * m_miu)) ) / (1 + pow(m_ee_div_es_0 * m_ee_div_es_1, 1 / (2 * m_miu)) ) );

    m_alpha_tag_00 = sqrt(1 / (1 + pow(m_ee_div_es_0, (1/m_miu)) ) );
    m_alpha_tag_11 = sqrt(1 / (1 + pow(m_ee_div_es_1, (1/m_miu)) ) );
    m_alpha_tag_01 = sqrt(1 / (1 + pow(m_ee_div_es_0 * m_ee_div_es_1, 1/(2 * m_miu)) ) );

}

Model::~Model()
{
    //dtor
}
