#include <stdio.h>
#include <float.h>
#include <math.h>
#include "correct_outlier.h"

namespace correct_outlier
{
    
void bubbleSort(vector<double>& vec, int n)
{
	int len = vec.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = len - 1; j > i; j--)
		{
			if (vec[j - 1] > vec[j])
			{
				double temp = vec[j];
				vec[j] = vec[j - 1];
				vec[j - 1] = temp;
			}
		}
	}
}

void leastSquare(vector<int> x, vector<double> y, double& k, double& b)
{
	int len = x.size();
	double sigma_x=0, sigma_y=0, sigma_xx=0, sigma_xy=0;
	for (int i = 0; i < len; i++)
	{
		sigma_x += x[i];
		sigma_y += y[i];
		sigma_xx += x[i] * x[i];
		sigma_xy += x[i] * y[i];
	}
	k = (len * sigma_xy - sigma_x * sigma_y) / (len * sigma_xx - sigma_x * sigma_x);
	b = (sigma_xx * sigma_y - sigma_x * sigma_xy) / (len * sigma_xx - sigma_x * sigma_x);
}

void leastSquare(vector<double> pts, double& k, double& b)
{
	int len = pts.size();
	double sigma_x=0, sigma_y=0, sigma_xx=0, sigma_xy=0;
	for (int i = 0; i < len; i++)
	{
		sigma_x += i;
		sigma_y += pts[i];
		sigma_xx += i * i;
		sigma_xy += i * pts[i];
	}
	k = (len * sigma_xy - sigma_x * sigma_y) / (len * sigma_xx - sigma_x * sigma_x);
	b = (sigma_xx * sigma_y - sigma_x * sigma_xy) / (len * sigma_xx - sigma_x * sigma_x);
}

void threshold(vector<double> pts, double k, double b, double threshold, vector<int>& inliers, vector<int>& outliers)
{
	int len = pts.size();
	inliers.clear();
	outliers.clear();
	for (int i = 0; i < len; i++)
	{
		if (abs(k * i + b - pts[i]) <= threshold)
		{
			inliers.push_back(i);
		}
		else
		{
			outliers.push_back(i);
		}
	}
}

void subset(vector<double> pts, vector<int> idx, vector<double>& sub)
{
	sub.resize(idx.size());
	for (int i = 0; i < idx.size(); i++)
	{
		sub[i] = pts[idx[i]];
	}
}

void findOutlier(vector<double> pts, vector<int>& inliers, vector<int>& outliers, double& _k, double& _b, int sample_span, int max_refine)
{
	int len = pts.size();
	inliers.clear();
	outliers.clear();
	// 以直线为模型，最小化误差的中位数
	double best_k = 0;
	double best_b = 0;
	double min_med_err = DBL_MAX;
	vector<double> err(len);
	for (int i = 0; i < len - sample_span; i++)
	{
		int x1 = i;
		int x2 = i + sample_span;
		double y1 = pts[x1];
		double y2 = pts[x2];
		double k = (y2 - y1) / (x2 - x1);
		double b = y1 - k * x1;
		for (int j = 0; j < len; j++)
		{
			int x = j;
			double y = pts[x];
			err[j] = abs(k * x + b - y);
		}
		bubbleSort(err, len / 2 + 1);
		double med_err = err[len / 2];
		if (med_err < min_med_err)
		{
			min_med_err = med_err;
			best_k = k;
			best_b = b;
		}
	}
	// min_med_err相当于自适应得出的野点判别阈值，先利用它进行初筛
	threshold(pts, best_k, best_b, min_med_err, inliers, outliers);

	// 对内点最小二乘，优化模型参数，最大化内点个数
	int max_inlier_cnt = 0;
	vector<double> pts_in;
	for (int i = 0; i < max_refine; i++)
	{
		double k, b;
		subset(pts, inliers, pts_in);
		leastSquare(inliers, pts_in, k, b);
		threshold(pts, k, b, min_med_err, inliers, outliers);
		if (inliers.size() > max_inlier_cnt)
		{
			best_k = k;
			best_b = b;
			max_inlier_cnt = inliers.size();
		}
	}
	_k = best_k;
	_b = best_b;
}

// inliers outliers必须都是严格递增的
void correctOutlier(vector<double>& pts, vector<int> inliers, vector<int> outliers)
{
	// 用内点的分段线性插值对野点进行矫正
	for (int i = 0; i < outliers.size(); i++)
	{	
		// 野点左边没有内点
		if (outliers[i] < inliers.front())
		{
			pts[outliers[i]] = pts[inliers.front()];
			continue;
		}

		// 野点右边没有内点
		if (outliers[i] > inliers.back())
		{
			pts[outliers[i]] = pts[inliers.back()];
			continue;
		}

		// 野点左右有内点
		for (int j = 1; j < inliers.size(); j++)
		{
			if (inliers[j] > outliers[i])
			{
				int x1 = inliers[j - 1];
				double y1 = pts[x1];
				int x2 = inliers[j];
				double y2 = pts[x2];
				int x = outliers[i];
				pts[x] = y2 * (x - x1) / (x2 - x1) + y1 * (x2 - x) / (x2 - x1);
				break;
			}
		}
	}
}

}