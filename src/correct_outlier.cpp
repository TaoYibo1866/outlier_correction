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

void correctOutlier(vector<double>& pts, vector<int> inliers, vector<int> outliers)
{
	;
}
// 如果想要得到比较好的结果那么需要保证数据中存在下标间隔为span的内点，且内点总数大于len/2+1
// void rejectOutlier(double* array, int len, int span, int ls_k)
// {
// 	// 以直线为模型，最小化误差绝对值的中位数(LMeds)
// 	double best_k = 0;
// 	double best_b = 0;
// 	double* err = new double[len];
// 	double min_med_err = FLT_MAX;
// 	for (int i = 0; i < len - span; i++)
// 	{
// 		int x1 = i;
// 		int x2 = i + span;
// 		double y1 = array[x1];
// 		double y2 = array[x2];
// 		double k = (y2 - y1) / (x2 - x1);
// 		double b = y1 - k * x1;
// 		for (int j = 0; j < len; j++)
// 		{
// 			int x = j;
// 			double y = array[x];
// 			err[j] = abs(k * x + b - y);
// 		}
// 		bubbleSort(err, len, len / 2 + 1);
// 		double med_err = err[len / 2];
// 		if (med_err < min_med_err)
// 		{
// 			min_med_err = med_err;
// 			best_k = k;
// 			best_b = b;
// 		}
// 	}
	
// 	// min_med_err相当于自适应得出的野点判别阈值，先利用它进行初筛
// 	int inlier_cnt = 0, outlier_cnt = 0;
// 	Point* inliers = new Point[len];
// 	Point* outliers = new Point[len];
// 	linearFilt(array, len, inliers, outliers, best_k, best_b, min_med_err, inlier_cnt, outlier_cnt);
// 	// 此时必有 inlier_cnt = len / 2 + 1
// 	// printf("%d %d\n", inlier_cnt, outlier_cnt);
	
// 	// 对内点最小二乘，优化模型参数，最大化内点个数
// 	int max_inlier_cnt = 0;
// 	for (int i = 0; i < ls_k; i++)
// 	{
// 		double k, b;
// 		leastSquare(inliers, inlier_cnt, k, b);
// 		linearFilt(array, len, inliers, outliers, k, b, min_med_err, inlier_cnt, outlier_cnt);
// 		if (inlier_cnt > max_inlier_cnt)
// 		{
// 			best_k = k;
// 			best_b = b;
// 			max_inlier_cnt = inlier_cnt;
// 		}
// 	}

// 	// 用内点的分段线性插值对野点进行矫正
// 	for (int i = 0; i < outlier_cnt; i++)
// 	{	
// 		// 野点左边没有内点
// 		if (outliers[i].idx < inliers[0].idx)
// 		{
// 			array[outliers[i].idx] = inliers[0].val;
// 			continue;
// 		}

// 		// 野点右边没有内点
// 		if (outliers[i].idx > inliers[inlier_cnt - 1].idx)
// 		{
// 			array[outliers[i].idx] = inliers[inlier_cnt - 1].val;
// 			continue;
// 		}

// 		// 野点左右有内点
// 		for (int j = 1; j < inlier_cnt; j++)
// 		{
// 			if (inliers[j].idx > outliers[i].idx)
// 			{
// 				double x1 = inliers[j - 1].idx;
// 				double y1 = inliers[j - 1].val;
// 				double x2 = inliers[j].idx;
// 				double y2 = inliers[j].val;
// 				double x = outliers[i].idx;
// 				array[outliers[i].idx] = y2 * (x - x1) / (x2 - x1) + y1 * (x2 - x) / (x2 - x1);
// 				break;
// 			}
// 		}
// 	}
	
// 	delete[] err;
// 	delete[] inliers;
// 	delete[] outliers;
// }
}