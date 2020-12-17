#ifndef _CORRECT_OUTLIER_H
#define _CORRECT_OUTLIER_H

#include <vector>

namespace correct_outlier
{
	using std::vector;

	void findOutlier(vector<double> pts, int sampleSpan, int refineCount, vector<int>& inliers, vector<int>& outliers);
	void findOutlierRANSAC();
	void findOutlierLMEDS();
	void correctOutlier(vector<double>& pts, vector<int> inliers, vector<int> outliers);
	void bubbleSort(vector<double>& vec, int n);
	void leastSquare(vector<double> pts, double& k, double& b);
	void threshold(vector<double> pts, double k, double b, double threshold, vector<int>& inliers, vector<int>& outliers);
}

#endif