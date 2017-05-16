#pragma once

#include "opencv2/imgproc.hpp"  
#include "opencv2/core/core.hpp"  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
#include <stdlib.h>  
#include <complex>  
#include "math.h"  

using namespace std;
using namespace cv;

namespace customCV {

	class Cloning
	{

	public:

		//output: ÿ��ͨ���ĺϳɽ������  
		//rbgx_channel, rgby_channel��gxx�� gyy ��ͨ�����  
		vector <Mat> rgb_channel, rgbx_channel, rgby_channel, output;

		//smask��sourceͼƬ��mask�� smask1��smaskȡ���Ľ��  
		//grx, gry ��dstͼƬ���ݶȡ� grx32�� gry32��smask1������ݶ�  
		//sgx, sgy ��sourceͼƬ���ݶȡ� srx32, sry32��smask������ݶ�  
		Mat grx, gry, sgx, sgy, srx32, sry32, grx32, gry32, smask, smask1;
		void init_var(Mat &I, Mat &wmask);
		void initialization(Mat &I, Mat &mask, Mat &wmask);
		void scalar_product(Mat mat, float r, float g, float b);
		void array_product(Mat mat1, Mat mat2, Mat mat3);
		void poisson(Mat &I, Mat &gx, Mat &gy, Mat &sx, Mat &sy);
		void evaluate(Mat &I, Mat &wmask, Mat &cloned);
		void getGradientx(const Mat &img, Mat &gx);
		void getGradienty(const Mat &img, Mat &gy);
		void lapx(const Mat &img, Mat &gxx);
		void lapy(const Mat &img, Mat &gyy);
		void dst(double *mod_diff, double *sineTransform, int h, int w);
		void idst(double *mod_diff, double *sineTransform, int h, int w);
		void transpose(double *mat, double *mat_t, int h, int w);
		void solve(const Mat &img, double *mod_diff, Mat &result);
		void poisson_solver(const Mat &img, Mat &gxx, Mat &gyy, Mat &result);
		void normal_clone(Mat &I, Mat &mask, Mat &wmask, Mat &cloned, int num);
		void local_color_change(Mat &I, Mat &mask, Mat &wmask, Mat &cloned, float red_mul, float green_mul, float blue_mul);
		void illum_change(Mat &I, Mat &mask, Mat &wmask, Mat &cloned, float alpha, float beta);
		void texture_flatten(Mat &I, Mat &mask, Mat &wmask, double low_threshold, double high_threhold, int kernel_size, Mat &cloned);
	};



	Mat b_convert(const Mat& Mask, const Scalar c);//�õ���Ӧ��ɫ�Ķ�ֵͼ
	void seamlessClone(InputArray _src, InputArray _dst, InputArray _mask, Point p, OutputArray _blend, int flags);
	void colorChange(InputArray _src, InputArray _mask, OutputArray _dst, float r, float g, float b);
	void illuminationChange(InputArray _src, InputArray _mask, OutputArray _dst, float a, float b);
	void textureFlattening(InputArray _src, InputArray _mask, OutputArray _dst, double low_threshold, double high_threshold, int kernel_size);
	void simple_clone(InputArray _src, InputArray _dst, InputArray _mask, Point p, OutputArray _blend);
}
