#include <iostream>
#include "textProcess.h"
#include "mcmcProc.h"
#include "seamless_cloning.h"

using namespace std;
using namespace cv;
using namespace customCV;



int main(int argc, char *argv[])
{
	string word;
	vector<info> objInfo;
	vector<prep> objPrep;
	cout << "please enter a word:";
	getline(cin, word);
	//word = "three dogs playing on the ground.";
	cout << word << endl;
	if (!textProcess(word, objInfo, objPrep)) {
		return 0;
	}

	vector<Object> bg_objs, fg_objs;
	if (!mcmc(objInfo, bg_objs, fg_objs)) {
		waitKey();
		return 0;
	}
	std::cout << " Seamless Cloning..." << endl;
	//Í¼ÏñºÏ³É
	Mat dst = imread(bg_objs[0].sourcePath, CV_LOAD_IMAGE_COLOR);
	resize(dst, dst, Size(600, 450));
	if (bg_objs.size() > 1) {
		for (vector<Object>::iterator iter = bg_objs.begin() + 1; iter != bg_objs.end(); iter++) {
			Mat src = imread(iter->sourcePath);
			Size new_size = Size(src.cols * (iter->rect.width / (float)iter->origin_size.width), src.rows * (iter->rect.height / (float)iter->origin_size.height));
			Mat mask = imread(iter->maskPath, CV_LOAD_IMAGE_COLOR);
			resize(src, src, new_size);
			resize(mask, mask, new_size);
			Scalar color;
			color[0] = iter->notationB; color[1] = iter->notationG; color[2] = iter->notationR;
			Point ex1;
			ex1.x = iter->rect.x;   ex1.y = iter->rect.y;
			Mat graymask = b_convert(mask, color);
			simple_clone(src, dst, graymask, ex1, dst);
		}
	}
	Mat bg = dst.clone();
	for (vector<Object>::iterator iter = fg_objs.begin(); iter != fg_objs.end(); iter++) {
		Mat src = imread(iter->sourcePath);
		Size new_size = Size(src.cols * (iter->rect.width / (float)iter->origin_size.width), src.rows * (iter->rect.height / (float)iter->origin_size.height));
		Mat mask = imread(iter->maskPath, CV_LOAD_IMAGE_COLOR);
		resize(src, src, new_size);
		resize(mask, mask, new_size);
		Scalar color;
		color[0] = iter->notationB; color[1] = iter->notationG; color[2] = iter->notationR;
		Point ex1;
		ex1.x = iter->rect.x;   ex1.y = iter->rect.y;
		Mat graymask = b_convert(mask, color);
		seamlessClone(src, dst, graymask, ex1, dst, 1);
	}
	//imshow("Scene", bg);
	imshow("Blending", dst);
	//char str[200];
	//sprintf_s(str, "D:\\Desktop\\result\\new_image_%d.bmp", i);
	imwrite("D:\\Desktop\\result\\new_image.bmp", dst);

	waitKey();
	return 1;
}
