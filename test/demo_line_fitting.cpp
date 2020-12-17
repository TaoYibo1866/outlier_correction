#include <stdio.h>
#include <vector>
#include "correct_outlier.h"

using correct_outlier::findOutlier;
using correct_outlier::correctOutlier;
using correct_outlier::leastSquare;
using std::vector;

int main()
{
    double k, b;
    vector<int> inliers, outliers;
    vector<double> pts = {10, 1.1, 2.0, 3.5, 3.7, -20, -15, 7.0, 8.2, -5, 9.5, 10.3, 11.6};
    leastSquare(pts, k, b);
    printf("leastSquare: k=%lf, b=%lf\n", k, b);
    findOutlier(pts, inliers, outliers, k, b, 1, 2);
    printf("findOutlier: k=%lf, b=%lf\n", k, b);
    return 0;
}