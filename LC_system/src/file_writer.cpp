#include "./../include/file_writer.h"



File_Writer::File_Writer()
{
	m_xyz_file_counter = 0;
}

File_Writer::~File_Writer()
{
    //dtor
}

void File_Writer::make_model_directory()
/// create folder in runs dir with the model name.
{
	string model_name = MODEL_NAME;
	string original_dir = ".//runs//" + model_name;
	string dir_to_create = original_dir;
	int nError = 0, i = 0;

	do
	{
#if defined _MSC_VER
		nError = _mkdir(dir_to_create.c_str());
#elif defined __GNUC__
		nError = mkdir(dir_to_create.c_str(), 0777);
#endif
		i++;
		dir_to_create = original_dir + "_" + to_string(i);
	} while (nError != 0);

	i--;
	dir_to_create = original_dir + "_" + to_string(i);

	//copy the model file to the the model directory
	std::ifstream  src(".//include//defined.h", std::ios::binary);
	string defined_file = dir_to_create + "//defined_file.h";
	std::ofstream  dst(defined_file, std::ios::binary);

	dst << src.rdbuf();

	//make output directory for all the xyz files.
	m_output_dir = dir_to_create + "//output";
#if defined _MSC_VER
	nError = _mkdir(m_output_dir.c_str());
#elif defined __GNUC__
	nError = mkdir(m_output_dir.c_str(), 0777);
#endif
	if (nError != 0)
	{
		cout << "couldnt create output directory, exiting..." << endl;
		exit(EXIT_FAILURE);
	}
}

void File_Writer::write_state2xyz(const vector<Molecule> & molecules)
{
	//craeting file in format: lqs_sys_0002
	ofstream xyz_file;
	stringstream fn_suffix;
	string file_name = "lqs_sys_";
	fn_suffix << setfill('0') << setw(4) << m_xyz_file_counter;
	file_name = m_output_dir + "//" + file_name + fn_suffix.str() + ".xyz";
	xyz_file.open(file_name);

	int num_col_mol = 0;
	int num_of_molecules = molecules.size();

	for (int i = 0; i < num_of_molecules; i++)
		if (molecules[i].m_mol_type == col)
			num_col_mol++;

	//setting format of double for writing:


	int line_counter = num_of_molecules;
	line_counter += (360 / DIF_ANGLES_COL_REPRESENTATION - 1) * num_col_mol;
	xyz_file << line_counter << endl;
	xyz_file << "Liquid Crystals with Colloide" << endl;
	for (int i = 0; i < num_of_molecules; i++)
	{
		if (molecules[i].m_mol_type == col)
		{
			int lines_to_draw_x = 360 / DIF_ANGLES_COL_REPRESENTATION;
#if	DIMENSIONS == 2
			double phi;
			for (int j = 0; j < (DEGREES_IN_CIRCLE / DIF_ANGLES_COL_REPRESENTATION); j++)
			{
				phi = (2 * PI * DIF_ANGLES_COL_REPRESENTATION / DEGREES_IN_CIRCLE) * j;
				cout.precision(6);
				cout << fixed;
				xyz_file << "d 0.0 " << fixed << molecules[i].m_location[0] << " " << fixed << molecules[i].m_location[1] << " 0.0 "
					<< fixed << cos(phi) << " " << fixed << sin(phi) << endl;
			}
#elif DIMENSIONS == 3
			double phi, theta;
			for (int j = 0; j < (DEGREES_IN_CIRCLE / DIF_ANGLES_COL_REPRESENTATION); j++)
			{
				phi = (2 * PI * DIF_ANGLES_COL_REPRESENTATION / DEGREES_IN_CIRCLE) * j;
				for (int k = 0; k < (2 * DEGREES_IN_CIRCLE / DIF_ANGLES_COL_REPRESENTATION); k++)
				{
					theta = (2 * PI * DIF_ANGLES_COL_REPRESENTATION / DEGREES_IN_CIRCLE) * k;
					xyz_file << "d " << fixed << molecules[i].m_location[0] << " " << fixed << molecules[i].m_location[1] << " " << fixed << molecules[i].m_location[2]
						<< " " << fixed << sin(theta) * cos(phi) << " " << fixed << sin(theta) * sin(phi) << " " << fixed << cos(theta) << endl;
				}
			}
#endif
		}
		else
		{
#if DIMENSIONS == 2 //ommit x:
			xyz_file << "Sp 0.0 " << molecules[i].m_location[0] << " " << molecules[i].m_location[1] << " 0.0 "
				<< molecules[i].m_spin[0] << " " << molecules[i].m_spin[1] << endl;
#elif DIMENSIONS == 3
			xyz_file << "Sp " << molecules[i].m_location[0] << " " << molecules[i].m_location[1] << " " << molecules[i].m_location[2]
				<< " " << molecules[i].m_spin[0] << " " << molecules[i].m_spin[1] << " " << molecules[i].m_spin[2] << endl;
#endif
		}
	}
	xyz_file.close();
	m_xyz_file_counter++;
}