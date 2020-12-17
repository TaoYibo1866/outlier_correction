#ifndef _CORRECT_OUTLIER_H
#define _CORRECT_OUTLIER_H

#include <vector>

namespace correct_outlier
{
	using std::vector;

	void findOutlier(vector<double> pts, vector<int>& inliers, vector<int>& outliers, double& k, double& b, int sample_span=1, int max_refine=1);
	void findOutlierRANSAC(vector<double> pts, vector<int>& inliers, vector<int>& outliers, double& k, double& b, int max_iter=10, double threshold=0.5);
	void findOutlierLMEDS(vector<double> pts, vector<int>& inliers, vector<int>& outliers, double& k, double& b, int max_iter=10);
	void correctOutlier(vector<double>& pts, vector<int> inliers, vector<int> outliers);

	void bubbleSort(vector<double>& vec, int n);
	void leastSquare(vector<int> x, vector<double> y, double& k, double& b);
	void leastSquare(vector<double> pts, double& k, double& b);
	void split(vector<double> pts, double k, double b, double threshold, vector<int>& inliers, vector<int>& outliers);
	void subset(vector<double> pts, vector<int> idx, vector<double>& sub);
}

#endif