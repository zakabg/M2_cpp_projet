#include "Vector.h"
#include <fstream>

using namespace std;

vector<vector<bool>> Vector::parseVectors(const string &file)    // parsing vector
{
    fstream f(file);
    vector<vector<bool>> vectors;

    if (f.good())
    {
        int vectors_cnt;       
        f >> vectors_cnt;

        vectors.resize(vectors_cnt); 

        for (int i = 0; i < vectors_cnt; i++)      
        {
            string line;
            f >> line;

            for (int j = 0; j< line.size(); j++)    
                if (line[j] == '1')
                    vectors[i].push_back(true);
                else
                    vectors[i].push_back(false);
        }
    }

    return vectors;
}
