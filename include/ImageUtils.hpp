#pragma once 

#include <vector>
#include <array>
#include <fstream>
#include <math.h> 
#include <algorithm>

using std::string;
using std::vector;
using std::array;
using std::fstream;

using Colour = array<double, 3>;
using PixelMap = vector<vector<Colour>>;

struct Image
{
    PixelMap image_data;
    const uint n_rows;
    const uint n_cols;

    Image(uint rows, uint cols) : n_rows(rows), n_cols(cols)
    {
        image_data = PixelMap(n_rows, vector<Colour>(n_cols));
    }
};


void SaveToFile(const PixelMap &image_data, const string &filename);