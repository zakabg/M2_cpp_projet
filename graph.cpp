#include "gate.h"
#include "graph.h"
#include "Vector.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include <memory>

using namespace std;
using namespace arma;   

void GRAPH::parseFile() 
{
	ifstream file("circuit.txt");
	string token;
	string line;

	if (file.good()) 
	{
		// read line by line
		while (getline(file, line))
		{
			stringstream line_stream(line);
			if (line != "")  
			{
				circuit.push_back({});   
				while (line_stream >> token)
				{
					circuit[circuit.size() - 1].push_back(token);
				}
			}
		}
	}

	// circuit read finish



	// calculat in, out, gates:
	in_cnt = circuit[0].size() - 2; 
	out_cnt = circuit[1].size() - 2; 
	gates_cnt = circuit.size() - 2;   

	const int mtrx_size = in_cnt + out_cnt + gates_cnt; 

	adj_mat.resize(mtrx_size, mtrx_size);
	adj_mat.fill(-555); 
	
	
	
	//////////cout << adj_mat << endl << endl;



	// fill adj_mat inputs connections
	for (int i = 2; i < circuit.size(); i++) 
	{
		for (int j = 3; j < circuit[i].size() - 1; j++) 
		{
			string input = circuit[i][j];     
			if (tolower(input[0]) == 'e')   
			{
				input.erase(input.begin()); 
				int input_nb = stoi(input);  

				const auto gate_in_index = j - 3;   

				adj_mat(input_nb - 1, in_cnt + out_cnt + i - 2) = gate_in_index;   
			}
		}
	}

	////cout << adj_mat << endl << endl;


	
	for (int i = 2; i < circuit.size(); i++) 
	{
		string output = circuit[i][2];
		
		if (tolower(output[0]) == 's')
		{
			output.erase(output.begin());
			int output_nb = stoi(output); 
			adj_mat(in_cnt + out_cnt + i - 2, in_cnt + output_nb - 1) = 1;   
		}
		else // gate output connected to a signal
		{
			for (int j = 2; j < circuit.size(); j++)									  
				for (int k = 3; k < circuit[j].size() - 1; k++)							 
					if (output == circuit[j][k])										  
						adj_mat(in_cnt + out_cnt + i - 2, in_cnt + out_cnt + j - 2) = k - 3; 
		}
	}

	//////cout << adj_mat << endl << endl;


	
	for (int i = 2; i < circuit.size(); i++) // loop throught gates linees
	{
		const int gate_ins_cnt = circuit[i].size() - 4;

		if (circuit[i][0] == "and")
			gates.push_back(new And(gate_ins_cnt));
		else if (circuit[i][0] == "or")
			gates.push_back(new Or(gate_ins_cnt));
		else if (circuit[i][0] == "xor")
			gates.push_back(new Xor(gate_ins_cnt));
		else if (circuit[i][0] == "not")
			gates.push_back(new Not(gate_ins_cnt));
	}
}

void GRAPH::solve()
{
	cout << "********************Zakaria BEGHI M2 SEI**********16/12/2019**********" << endl << endl;

	Vector vectors;
	
	ins_vecs = vectors.parseVectors("inputs.txt"); 

	cout << adj_mat;

	// loop throught the vectors and apply dfs to the primary inputs
	for (int i = 0; i < ins_vecs.size(); i++)
	{
		out_vec.resize(out_cnt);

		in_vec = ins_vecs[i];

		// apply DFS to all primarys
		for (int j = 0; j < in_cnt; j++)
			DFS(j);

		cout << "Le vecteur d'entree est :";
		for (const auto& in : in_vec)
			cout << " " << in;
		cout << endl;

		cout << "La sortie finale est :";
		for (const auto& out : out_vec)
			cout << " " << out;
		cout <<  endl;
	}
}

void GRAPH::DFS(const int index)
{
	for (int i = 0; i < adj_mat.n_cols; i++)
	{
		if (adj_mat(index, i) >= 0)
		{
			if (index >= 0 && index < in_cnt)
			{
				gates[i - (in_cnt + out_cnt)]->set_input(in_vec[index], adj_mat(index, i));
				DFS(i);
			}
			else if ((index >= (in_cnt + out_cnt)) && (index < adj_mat.n_rows)) // node is gate
			{
				gates[index - (in_cnt + out_cnt)]->calculate_output();

				if ((i >= (in_cnt + out_cnt)) && (i < adj_mat.n_rows))
				{
					const auto out = gates[index - (in_cnt + out_cnt)]->get_output();
					gates[i - (in_cnt + out_cnt)]->set_input(out, adj_mat(index, i));
					DFS(i);
				}else 
				// next node is output
				{
					const auto out = gates[index - (in_cnt + out_cnt)]->get_output();
					const auto out_index = i - in_cnt;
					out_vec[out_index] = out;
				}
			}
		}
	}
}

GRAPH::~GRAPH()
{

	for (auto gate : gates)
		delete gate;
}
