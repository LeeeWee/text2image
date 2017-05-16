#include "seamless_cloning.h"

using namespace std;
using namespace cv;

namespace customCV {

	void Cloning::getGradientx(const Mat &img, Mat &gx)
	{
		Mat kernel = Mat::zeros(1, 3, CV_8S);
		kernel.at<char>(0, 2) = 1;
		kernel.at<char>(0, 1) = -1;
		filter2D(img, gx, CV_32F, kernel);
	}

	void Cloning::getGradienty(const Mat &img, Mat &gy)
	{
		Mat kernel = Mat::zeros(3, 1, CV_8S);
		kernel.at<char>(2, 0) = 1;
		kernel.at<char>(1, 0) = -1;
		filter2D(img, gy, CV_32F, kernel);
	}

	//img是原始图像水平方向上的梯度。本函数是对梯度再求梯度  
	void Cloning::lapx(const Mat &img, Mat &gxx)
	{
		Mat kernel = Mat::zeros(1, 3, CV_8S);
		kernel.at<char>(0, 0) = -1;
		kernel.at<char>(0, 1) = 1;
		filter2D(img, gxx, CV_32F, kernel);
	}

	void Cloning::lapy(const Mat &img, Mat &gyy)
	{
		Mat kernel = Mat::zeros(3, 1, CV_8S);
		kernel.at<char>(0, 0) = -1;
		kernel.at<char>(1, 0) = 1;
		filter2D(img, gyy, CV_32F, kernel);
	}

	//离散正弦变换  
	//参考：http://www.mathworks.com/help/pde/ug/dst.html  
	//参考：http://www.mathworks.com/help/pde/ug/fast-solution-of-poissons-equation.html  
	void Cloning::dst(double *mod_diff, double *sineTransform, int h, int w)
	{

		unsigned long int idx;

		Mat temp = Mat(2 * h + 2, 1, CV_32F);
		Mat res = Mat(h, 1, CV_32F);

		Mat planes[] = { Mat_<float>(temp), Mat::zeros(temp.size(), CV_32F) };

		Mat result;
		int p = 0;
		for (int i = 0; i < w; i++)
		{
			temp.at<float>(0, 0) = 0.0;

			for (int j = 0, r = 1; j < h; j++, r++)
			{
				idx = j*w + i;
				temp.at<float>(r, 0) = (float)mod_diff[idx];
			}

			temp.at<float>(h + 1, 0) = 0.0;

			for (int j = h - 1, r = h + 2; j >= 0; j--, r++)
			{
				idx = j*w + i;
				temp.at<float>(r, 0) = (float)(-1.0 * mod_diff[idx]);
			}

			merge(planes, 2, result);

			dft(result, result, 0, 0);

			Mat planes1[] = { Mat::zeros(result.size(), CV_32F), Mat::zeros(result.size(), CV_32F) };

			split(result, planes1);

			std::complex<double> two_i = std::sqrt(std::complex<double>(-1));

			double factor = -2 * imag(two_i);

			for (int c = 1, z = 0; c < h + 1; c++, z++)
			{
				res.at<float>(z, 0) = (float)(planes1[1].at<float>(c, 0) / factor);
			}

			for (int q = 0, z = 0; q < h; q++, z++)
			{
				idx = q*w + p;
				sineTransform[idx] = res.at<float>(z, 0);
			}
			p++;
		}
	}

	void Cloning::idst(double *mod_diff, double *sineTransform, int h, int w)
	{
		int nn = h + 1;
		unsigned long int idx;
		dst(mod_diff, sineTransform, h, w);
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
			{
			idx = i*w + j;
			sineTransform[idx] = (double)(2 * sineTransform[idx]) / nn;
			}

	}

	void Cloning::transpose(double *mat, double *mat_t, int h, int w)
	{

		Mat tmp = Mat(h, w, CV_32FC1);
		unsigned long int idx;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{

				idx = i*(w)+j;
				tmp.at<float>(i, j) = (float)mat[idx];
			}
		}
		Mat tmp_t = tmp.t();

		for (int i = 0; i < tmp_t.size().height; i++)
			for (int j = 0; j < tmp_t.size().width; j++)
			{
			idx = i*tmp_t.size().width + j;
			mat_t[idx] = tmp_t.at<float>(i, j);
			}
	}

	void Cloning::solve(const Mat &img, double *mod_diff, Mat &result)
	{
		int w = img.size().width;
		int h = img.size().height;

		unsigned long int idx, idx1;

		double *sineTransform = new double[(h - 2)*(w - 2)];
		double *sineTransform_t = new double[(h - 2)*(w - 2)];
		double *denom = new double[(h - 2)*(w - 2)];
		double *invsineTransform = new double[(h - 2)*(w - 2)];
		double *invsineTransform_t = new double[(h - 2)*(w - 2)];
		double *img_d = new double[(h)*(w)];
		//结果存在img_d  


		dst(mod_diff, sineTransform, h - 2, w - 2);
		transpose(sineTransform, sineTransform_t, h - 2, w - 2);


		dst(sineTransform_t, sineTransform, w - 2, h - 2);

		transpose(sineTransform, sineTransform_t, w - 2, h - 2);

		int cy = 1;

		for (int i = 0; i < w - 2; i++, cy++)
		{
			for (int j = 0, cx = 1; j < h - 2; j++, cx++)
			{
				idx = j*(w - 2) + i;
				denom[idx] = (float)2 * cos(CV_PI*cy / ((double)(w - 1))) - 2 + 2 * cos(CV_PI*cx / ((double)(h - 1))) - 2;

			}
		}

		for (idx = 0; idx < (unsigned)(w - 2)*(h - 2); idx++)
		{
			sineTransform_t[idx] = sineTransform_t[idx] / denom[idx];
		}

		idst(sineTransform_t, invsineTransform, h - 2, w - 2);

		transpose(invsineTransform, invsineTransform_t, h - 2, w - 2);

		idst(invsineTransform_t, invsineTransform, w - 2, h - 2);

		transpose(invsineTransform, invsineTransform_t, w - 2, h - 2);

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				idx = i*w + j;
				img_d[idx] = (double)img.at<uchar>(i, j);
			}
		}
		for (int i = 1; i < h - 1; i++)
		{
			for (int j = 1; j < w - 1; j++)
			{
				idx = i*w + j;
				img_d[idx] = 0.0;
			}
		}
		for (int i = 1, id1 = 0; i < h - 1; i++, id1++)
		{
			for (int j = 1, id2 = 0; j < w - 1; j++, id2++)
			{
				idx = i*w + j;
				idx1 = id1*(w - 2) + id2;
				img_d[idx] = invsineTransform_t[idx1];
			}
		}


		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				idx = i*w + j;
				if (img_d[idx] < 0.0) {
					result.at<uchar>(i, j) = 0;
				}
				else if (img_d[idx] > 255.0)
					result.at<uchar>(i, j) = 255;
				else {
					result.at<uchar>(i, j) = (uchar)img_d[idx];
				}
			}
		}

		delete[] sineTransform;
		delete[] sineTransform_t;
		delete[] denom;
		delete[] invsineTransform;
		delete[] invsineTransform_t;
		delete[] img_d;
	}

	//由img和lap计算合成结果, 注意实际上lap有大量负数  
	void Cloning::poisson_solver(const Mat &img, Mat &gxx, Mat &gyy, Mat &result)
	{

		int w = img.size().width;
		int h = img.size().height;

		unsigned long int idx;

		Mat lap = Mat(img.size(), CV_32FC1);

		lap = gxx + gyy;

		Mat bound = img.clone();

		//rectangle 外围保持原样，rect内部变为scalar  
		rectangle(bound, Point(1, 1), Point(img.cols - 2, img.rows - 2), Scalar::all(0), -1);
		//rectangle(bound, Point(20, 20), Point(img.cols - 50, img.rows - 50), Scalar::all(0), -1);  


		double *boundary_point = new double[h*w];

		Mat bound_map = cv::Mat(img.size(), CV_8UC1, cv::Scalar(0));

		for (int i = 1; i < h - 1; i++)
			for (int j = 1; j < w - 1; j++)
			{
			idx = i*w + j;
			boundary_point[idx] = -4 * (int)bound.at<uchar>(i, j) + (int)bound.at<uchar>(i, (j + 1)) + (int)bound.at<uchar>(i, (j - 1))
				+ (int)bound.at<uchar>(i - 1, j) + (int)bound.at<uchar>(i + 1, j);
			bound_map.at<uchar>(i, j) = boundary_point[idx];
			}



		Mat diff = Mat(h, w, CV_32FC1);
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				idx = i*w + j;
				diff.at<float>(i, j) = (float)(lap.at<float>(i, j) - boundary_point[idx]);
			}
		}

		//diff和lap几乎没什么区别  

		double *mod_diff = new double[(h - 2)*(w - 2)];
		for (int i = 0; i < h - 2; i++)
		{
			for (int j = 0; j < w - 2; j++)
			{
				idx = i*(w - 2) + j;
				mod_diff[idx] = diff.at<float>(i + 1, j + 1);

			}
		}
		///////////////////////////////////////////////////// Find DST  /////////////////////////////////////////////////////  
		solve(img, mod_diff, result);

		delete[] mod_diff;
		delete[] boundary_point;
	}

	void Cloning::init_var(Mat &I, Mat &wmask)
	{
		grx = Mat(I.size(), CV_32FC3);
		gry = Mat(I.size(), CV_32FC3);
		sgx = Mat(I.size(), CV_32FC3);
		sgy = Mat(I.size(), CV_32FC3);

		split(I, rgb_channel);


		smask = Mat(wmask.size(), CV_32FC1);
		srx32 = Mat(I.size(), CV_32FC3);
		sry32 = Mat(I.size(), CV_32FC3);
		smask1 = Mat(wmask.size(), CV_32FC1);
		grx32 = Mat(I.size(), CV_32FC3);
		gry32 = Mat(I.size(), CV_32FC3);
	}

	void Cloning::initialization(Mat &I, Mat &mask, Mat &wmask)
	{
		//初始化各个mat  
		init_var(I, wmask);

		//grx, gry 分别表示dest的x，y方向的梯度  
		getGradientx(I, grx);
		getGradienty(I, gry);

		//sgx, sgy 分别表示在mask区域内的source图片在x，y方向的梯度  
		getGradientx(mask, sgx);
		getGradienty(mask, sgy);

		Mat Kernel(Size(3, 3), CV_8UC1);
		Kernel.setTo(Scalar(1));
		//腐蚀  
		erode(wmask, wmask, Kernel, Point(-1, -1), 3);

		wmask.convertTo(smask, CV_32FC1, 1.0 / 255.0);
		I.convertTo(srx32, CV_32FC3, 1.0 / 255.0);
		I.convertTo(sry32, CV_32FC3, 1.0 / 255.0);
	}

	void Cloning::scalar_product(Mat mat, float r, float g, float b)
	{
		vector <Mat> channels;
		split(mat, channels);
		multiply(channels[2], r, channels[2]);
		multiply(channels[1], g, channels[1]);
		multiply(channels[0], b, channels[0]);
		merge(channels, mat);
	}

	//mat1 = mat3.mul(mat2(:))  mat3为单通道，一般为mask  
	void Cloning::array_product(Mat mat1, Mat mat2, Mat mat3)
	{
		vector <Mat> channels_temp1;
		vector <Mat> channels_temp2;
		split(mat1, channels_temp1);
		split(mat2, channels_temp2);
		multiply(channels_temp2[2], mat3, channels_temp1[2]);
		multiply(channels_temp2[1], mat3, channels_temp1[1]);
		multiply(channels_temp2[0], mat3, channels_temp1[0]);
		merge(channels_temp1, mat1);
	}

	void Cloning::poisson(Mat &I, Mat &gx, Mat &gy, Mat &sx, Mat &sy)
	{
		//fx, fy是两者组合的梯度  
		Mat fx = Mat(I.size(), CV_32FC3);
		Mat fy = Mat(I.size(), CV_32FC3);

		fx = gx + sx;
		fy = gy + sy;


		Mat gxx = Mat(I.size(), CV_32FC3);
		Mat gyy = Mat(I.size(), CV_32FC3);

		//gxx, gyy 是在x，y方向的laplacian算子  
		lapx(fx, gxx);
		lapy(fy, gyy);


		split(gxx, rgbx_channel);
		split(gyy, rgby_channel);

		split(I, output);


		poisson_solver(rgb_channel[2], rgbx_channel[2], rgby_channel[2], output[2]);
		poisson_solver(rgb_channel[1], rgbx_channel[1], rgby_channel[1], output[1]);
		poisson_solver(rgb_channel[0], rgbx_channel[0], rgby_channel[0], output[0]);
	}

	void Cloning::evaluate(Mat &I, Mat &wmask, Mat &cloned)
	{
		//mask取反  
		bitwise_not(wmask, wmask);

		wmask.convertTo(smask1, CV_32FC1, 1.0 / 255.0);
		I.convertTo(grx32, CV_32FC3, 1.0 / 255.0);
		I.convertTo(gry32, CV_32FC3, 1.0 / 255.0);

		array_product(grx32, grx, smask1);
		array_product(gry32, gry, smask1);

		poisson(I, grx32, gry32, srx32, sry32);

		merge(output, cloned);
	}

	void Cloning::normal_clone(Mat &I, Mat &mask, Mat &wmask, Mat &cloned, int num)
	{
		int w = I.size().width;
		int h = I.size().height;
		int channel = I.channels();

		//初始化各个存储参数的mat，并计算原图于目标图的x，y方向梯度，对mask腐蚀  
		initialization(I, mask, wmask);

		if (num == 1) //NORMAL_CLONE  
		{
			//srx32, sry32是sgx，sgy的mask区域  
			array_product(srx32, sgx, smask);
			array_product(sry32, sgy, smask);
		}
		else if (num == 2) //MIXED_CLONE  
		{

			for (int i = 0; i < h; i++)
			{
				for (int j = 0; j < w; j++)
				{
					for (int c = 0; c<channel; ++c)
					{
						if (abs(sgx.at<float>(i, j*channel + c) - sgy.at<float>(i, j*channel + c)) >
							abs(grx.at<float>(i, j*channel + c) - gry.at<float>(i, j*channel + c)))
						{

							srx32.at<float>(i, j*channel + c) = sgx.at<float>(i, j*channel + c)
								* smask.at<float>(i, j);
							sry32.at<float>(i, j*channel + c) = sgy.at<float>(i, j*channel + c)
								* smask.at<float>(i, j);
						}
						else
						{
							srx32.at<float>(i, j*channel + c) = grx.at<float>(i, j*channel + c)
								* smask.at<float>(i, j);
							sry32.at<float>(i, j*channel + c) = gry.at<float>(i, j*channel + c)
								* smask.at<float>(i, j);
						}
					}
				}
			}

		}
		else if (num == 3) //FEATURE_EXCHANGE  
		{
			Mat gray = Mat(mask.size(), CV_8UC1);
			Mat gray8 = Mat(mask.size(), CV_8UC3);
			cvtColor(mask, gray, COLOR_BGR2GRAY);
			vector <Mat> temp;
			split(I, temp);
			gray.copyTo(temp[2]);
			gray.copyTo(temp[1]);
			gray.copyTo(temp[0]);

			merge(temp, gray8);

			getGradientx(gray8, sgx);
			getGradienty(gray8, sgy);

			array_product(srx32, sgx, smask);
			array_product(sry32, sgy, smask);

		}

		evaluate(I, wmask, cloned);
	}

	void Cloning::local_color_change(Mat &I, Mat &mask, Mat &wmask, Mat &cloned, float red_mul = 1.0,
		float green_mul = 1.0, float blue_mul = 1.0)
	{
		initialization(I, mask, wmask);

		array_product(srx32, sgx, smask);
		array_product(sry32, sgy, smask);
		scalar_product(srx32, red_mul, green_mul, blue_mul);
		scalar_product(sry32, red_mul, green_mul, blue_mul);

		evaluate(I, wmask, cloned);
	}

	void Cloning::illum_change(Mat &I, Mat &mask, Mat &wmask, Mat &cloned, float alpha, float beta)
	{
		initialization(I, mask, wmask);

		array_product(srx32, sgx, smask);
		array_product(sry32, sgy, smask);

		Mat mag = Mat(I.size(), CV_32FC3);
		magnitude(srx32, sry32, mag);

		//opencv3.0 alpha中有bug，需要加入一下代码才不能得到正确结果。已经提交bug  
		for (int i = 0; i < mag.cols; i++)
		{
			for (int j = 0; j < mag.rows; j++)
			{
				if (mag.at<cv::Vec3f>(j, i)[0] == 0)
					mag.at<cv::Vec3f>(j, i)[0] = 1e-8;

				if (mag.at<cv::Vec3f>(j, i)[1] == 0)
					mag.at<cv::Vec3f>(j, i)[1] = 1e-8;

				if (mag.at<cv::Vec3f>(j, i)[2] == 0)
					mag.at<cv::Vec3f>(j, i)[2] = 1e-8;
			}
		}

		Mat multX, multY, multx_temp, multy_temp;

		multiply(srx32, pow(alpha, beta), multX);
		pow(mag, -1 * beta, multx_temp);
		multiply(multX, multx_temp, srx32);

		multiply(sry32, pow(alpha, beta), multY);
		pow(mag, -1 * beta, multy_temp);
		multiply(multY, multy_temp, sry32);

		Mat zeroMask = (srx32 != 0);

		srx32.copyTo(srx32, zeroMask);
		sry32.copyTo(sry32, zeroMask);

		evaluate(I, wmask, cloned);
	}

	void Cloning::texture_flatten(Mat &I, Mat &mask, Mat &wmask, double low_threshold,
		double high_threshold, int kernel_size, Mat &cloned)
	{
		initialization(I, mask, wmask);

		Mat out = Mat(mask.size(), CV_8UC1);
		Canny(mask, out, low_threshold, high_threshold, kernel_size);

		Mat zeros(sgx.size(), CV_32FC3);
		zeros.setTo(0);
		Mat zerosMask = (out != 255);
		zeros.copyTo(sgx, zerosMask);
		zeros.copyTo(sgy, zerosMask);

		array_product(srx32, sgx, smask);
		array_product(sry32, sgy, smask);

		evaluate(I, wmask, cloned);
	}



	void seamlessClone(InputArray _src, InputArray _dst, InputArray _mask, Point p, OutputArray _blend, int flags)
	{
		Mat src = _src.getMat();
		Mat dest = _dst.getMat();
		Mat mask = _mask.getMat();
		_blend.create(dest.size(), CV_8UC3);
		Mat blend = _blend.getMat();

		int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;
		int h = mask.size().height;
		int w = mask.size().width;

		Mat gray = Mat(mask.size(), CV_8UC1);
		Mat dst_mask = Mat::zeros(dest.size(), CV_8UC1);
		Mat cs_mask = Mat::zeros(src.size(), CV_8UC3);
		Mat cd_mask = Mat::zeros(dest.size(), CV_8UC3);

		if (mask.channels() == 3)
			cvtColor(mask, gray, COLOR_BGR2GRAY);
		else
			gray = mask;

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (gray.at<uchar>(i, j) == 255)
				{
					minx = std::min(minx, i);
					maxx = std::max(maxx, i);
					miny = std::min(miny, j);
					maxy = std::max(maxy, j);
				}
			}
		}

		int lenx = maxx - minx;
		int leny = maxy - miny;

		int minxd = p.y - lenx / 2;
		int maxxd = p.y + lenx / 2;
		int minyd = p.x - leny / 2;
		int maxyd = p.x + leny / 2;

		CV_Assert(minxd >= 0 && minyd >= 0 && maxxd <= dest.rows && maxyd <= dest.cols);

		Rect roi_d(minyd, minxd, leny, lenx);
		Rect roi_s(miny, minx, leny, lenx);

		Mat destinationROI = dst_mask(roi_d);
		Mat sourceROI = cs_mask(roi_s);

		gray(roi_s).copyTo(destinationROI);
		src(roi_s).copyTo(sourceROI, gray(roi_s));

		destinationROI = cd_mask(roi_d);
		cs_mask(roi_s).copyTo(destinationROI);

		Cloning obj;
		obj.normal_clone(dest, cd_mask, dst_mask, blend, flags);

	}

	void colorChange(InputArray _src, InputArray _mask, OutputArray _dst, float r, float g, float b)
	{
		Mat src = _src.getMat();
		Mat mask = _mask.getMat();
		_dst.create(src.size(), src.type());
		Mat blend = _dst.getMat();

		float red = r;
		float green = g;
		float blue = b;

		Mat gray = Mat::zeros(mask.size(), CV_8UC1);

		if (mask.channels() == 3)
			cvtColor(mask, gray, COLOR_BGR2GRAY);
		else
			gray = mask;

		Mat cs_mask = Mat::zeros(src.size(), CV_8UC3);

		src.copyTo(cs_mask, gray);

		Cloning obj;
		obj.local_color_change(src, cs_mask, gray, blend, red, green, blue);
	}

	void illuminationChange(InputArray _src, InputArray _mask, OutputArray _dst, float a, float b)
	{

		Mat src = _src.getMat();
		Mat mask = _mask.getMat();
		_dst.create(src.size(), src.type());
		Mat blend = _dst.getMat();
		float alpha = a;
		float beta = b;

		Mat gray = Mat::zeros(mask.size(), CV_8UC1);

		if (mask.channels() == 3)
			cvtColor(mask, gray, COLOR_BGR2GRAY);
		else
			gray = mask;

		Mat cs_mask = Mat::zeros(src.size(), CV_8UC3);

		src.copyTo(cs_mask, gray);

		Cloning obj;
		obj.illum_change(src, cs_mask, gray, blend, alpha, beta);
	}

	void textureFlattening(InputArray _src, InputArray _mask, OutputArray _dst,
		double low_threshold, double high_threshold, int kernel_size)
	{

		Mat src = _src.getMat();
		Mat mask = _mask.getMat();
		_dst.create(src.size(), src.type());
		Mat blend = _dst.getMat();

		Mat gray = Mat::zeros(mask.size(), CV_8UC1);

		if (mask.channels() == 3)
			cvtColor(mask, gray, COLOR_BGR2GRAY);
		else
			gray = mask;

		Mat cs_mask = Mat::zeros(src.size(), CV_8UC3);

		src.copyTo(cs_mask, gray);

		Cloning obj;
		obj.texture_flatten(src, cs_mask, gray, low_threshold, high_threshold, kernel_size, blend);
	}


	Mat b_convert(const Mat& Mask, const Scalar c)//得到对应颜色的二值图
	{
		Mat mask;
		mask = Mask.clone();
		int nr = mask.rows;
		int nc = mask.cols;
		Mat b_mask(nr, nc, CV_8UC1);

		//erode(mask, mask,Mat(), Point(-1,-1),1);
		if (mask.isContinuous())
		{
			nr = 1;
			nc = nc*mask.rows;
		}
		Scalar chscl;
		for (int i = 0; i < nr; i++)
		{
			uchar* Data = mask.ptr<uchar>(i);
			uchar* Data1 = b_mask.ptr<uchar>(i);
			for (int j = 0; j < nc; j++)
			{
				chscl[0] = *Data++;
				chscl[1] = *Data++;
				chscl[2] = *Data++;
				if (chscl == c)
					//if(chscl[0] == c[0] && chscl[1] == c[1] && chscl[2] == c[2])
					*Data1++ = 255;
				else
					*Data1++ = 0;
			}
		}
		//std::cout << "b_mask = " << std::endl << b_mask << std::endl << std::endl;
		// imshow("Hm", b_mask);
		threshold(b_mask, b_mask, 99, 255, CV_THRESH_BINARY);
		return b_mask;

	}

	void simple_clone(InputArray _src, InputArray _dst, InputArray _mask, Point p, OutputArray _blend)
	{
		Mat src = _src.getMat();
		Mat dest = _dst.getMat();
		Mat mask = _mask.getMat();
		_blend.create(dest.size(), CV_8UC3);
		Mat blend = _blend.getMat();

		int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;
		int h = mask.size().height;
		int w = mask.size().width;

		Mat gray = Mat(mask.size(), CV_8UC1);
		Mat dst_mask = Mat::zeros(dest.size(), CV_8UC1);
		Mat cs_mask = Mat::zeros(src.size(), CV_8UC3);
		Mat cd_mask = Mat::zeros(dest.size(), CV_8UC3);

		if (mask.channels() == 3)
			cvtColor(mask, gray, COLOR_BGR2GRAY);
		else
			gray = mask;

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (gray.at<uchar>(i, j) == 255)
				{
					minx = std::min(minx, i);
					maxx = std::max(maxx, i);
					miny = std::min(miny, j);
					maxy = std::max(maxy, j);
				}
			}
		}

		int lenx = maxx - minx;
		int leny = maxy - miny;

		int minxd = p.y - lenx / 2;
		int maxxd = p.y + lenx / 2;
		int minyd = p.x - leny / 2;
		int maxyd = p.x + leny / 2;

		CV_Assert(minxd >= 0 && minyd >= 0 && maxxd <= dest.rows && maxyd <= dest.cols);

		Rect roi_d(minyd, minxd, leny, lenx);
		Rect roi_s(miny, minx, leny, lenx);

		Mat destinationROI = dst_mask(roi_d);
		Mat sourceROI = cs_mask(roi_s);

		gray(roi_s).copyTo(destinationROI);
		src(roi_s).copyTo(sourceROI, gray(roi_s));

		destinationROI = cd_mask(roi_d);
		cs_mask(roi_s).copyTo(destinationROI);


		int nr = dest.rows;
		int nc = dest.cols;
		int chn = dest.channels();
		for (int i = 0; i < nr; i++)
		{
			for (int j = 0; j < nc; j++)
			{
				for (int n = 0; n < chn; n++){
					if (dst_mask.at<uchar>(i, j) == 255)
						dest.at<uchar>(i, j * chn + n) = cd_mask.at<uchar>(i, j * chn + n);
				}
			}
		}
	}

}
