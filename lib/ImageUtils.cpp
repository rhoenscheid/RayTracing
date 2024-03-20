#include "ImageUtils.hpp"
#include <iostream> 

void SaveToFile(const PixelMap &image_data, const string &filename)
{
    size_t n_rows = image_data.size();
    if(image_data.size() == 0)
    {
        throw;
    }
    size_t n_cols = image_data[0].size();

    //Write the file header
    fstream image_file;
    image_file.open(filename, fstream::out);
    if(!image_file)
    {
        throw;
    }
    image_file << "P3\n" << n_rows << " " << n_cols << "\n255\n";

    for(size_t i = 0; i < n_rows; i++)
    {
        if(image_data[i].size() != n_cols)
        {
            throw;
        }
        for(size_t j = 0; j < n_cols; j++)
        {
            for(auto &&x : image_data[i][j])
            {
                image_file << int(x > 255 ? 255 : x) << " ";  // fix this
            }
            image_file << "\n";
        }
    }
}