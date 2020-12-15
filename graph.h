#pragma once

#include "gate.h"
#include <iostream>
#include <vector>
#include <memory>
#include "armadillo.h"

class GRAPH
{
public:
	~GRAPH();
	void parseFile();
	void solve();

private:
	std::vector<std::vector<std::string>> circuit;
	std::vector<Gate *> gates;
	int in_cnt, out_cnt, gates_cnt;
	arma::Mat<int> adj_mat;
	std::vector<std::vector<bool>> ins_vecs; 
	std::vector<bool> in_vec;				 
	std::vector<bool> out_vec;				 

	
	void fillAdjMat(int size, int in, int out);
	void DFS(int index);
};
