#include <fstream>
#include <vector>
#include "correct_outlier.h"

using namespace correct_outlier;

int readFile(const char* filename, std::vector<float> signal)
{
    std::fstream file;
    file.open(filename, std::ios::in);
    if (file.is_open() != true) return -1;
    signal.clear();
    std::string tp;
    while (std::getline(file, tp))
    {
        float data;
        std::sscanf(tp.c_str(), "%f", &data);
        signal.push_back(data);
    }
    return 0; 
}

int main()
{
    std::vector<float> input, output;
    if (readFile("../test/input.csv", input) == -1)
    {
        printf("fail open file\n");
    }
    int len = 20;
    float* cache = new float[len]();
    float* _cache = new float[len]();
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < len - 1; j++)
        {
            temp[j] = temp[j + 1];
        }
        temp[len - 1] = input[i];
        correctOutlier(temp, len, 2, 1);
        output.push_back(temp[len - 1]);
    }
    delete[] temp;
    return 0;
}