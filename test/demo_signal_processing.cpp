#include <fstream>
#include <vector>
#include "correct_outlier.h"

using correct_outlier::findOutlier;
using correct_outlier::correctOutlier;
using std::vector;

int readFile(const char* filename, vector<double>& signal)
{
    std::fstream file;
    file.open(filename, std::ios::in);
    if (file.is_open() != true) return -1;
    signal.clear();
    std::string tp;
    while (std::getline(file, tp))
    {
        double data;
        std::sscanf(tp.c_str(), "%lf", &data);
        signal.push_back(data);
    }
    file.close();
    return 0; 
}

int writeFile(const char* filename, vector<double> signal)
{
    std::fstream file;
    file.open(filename, std::ios::trunc | std::ios::out);
    if (file.is_open() != true) return -1;
    for (int i = 0; i < signal.size(); i++)
    {
        file << signal[i] << std::endl;
    }
    file.close();
    return 0; 
}

int main()
{
    vector<double> input, output;
    if (readFile("../test/input.csv", input) == -1)
    {
        printf("fail open input file\n");
    }
    int len = 20;
    vector<double> cache(len), _cache(len);
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < len - 1; j++)
        {
            cache[j] = _cache[j + 1];
            _cache[j] = _cache[j + 1];
        }
        cache[len - 1] = input[i];
        _cache[len - 1] = input[i];
        double k, b;
        vector<int> inliers, outliers;
        findOutlier(_cache, inliers, outliers, k, b, 2, 1);
        correctOutlier(cache, inliers, outliers);
        output.push_back(cache.back());
    }
    if (writeFile("../test/output.csv", output) == -1)
    {
        printf("fail open output file\n");
    }
    return 0;
}