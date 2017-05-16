#ifndef MCMCPROC_H
#define MCMCPROC_H

#include <iostream>
#include <map>
#include <string>
#include "textProcess.h"
#include "opencv2/core/core.hpp"  
using namespace std;
using namespace cv;

const int Width = 600;//合成图片宽度
const int Height = 450;//合成图片高度
const int Itertions = 10000;  //MCMC算法迭代次数

enum Scene
{
	SCENE_SKY    = 0,
	SCENE_LAWN = 1,
	SCENE_GROUND = 2,
	SCENE_SEA = 3,
	SCENE_STREET = 4,
	SCENE_GARDEN = 5,
	SCENE_FARM = 6,
	SCENE_WRONGSCENE
};

static map<string, int> typeIdMap;
//初始化typeIdMap
int initTypeIdMap(void);

//定义一个物体的类
class Object
{
public:
	Object(string name) :typeName(name)
	{
		typeId = typeIdMap[name];
	}
	string typeName;
	int typeId;
	Size origin_size; //前景物体区域图片的初始尺寸
	Rect rect;        //图片的最终尺寸位置
	int imagesetId;
	int notationR;   //mask图标记区域颜色R值
	int notationG;	 //mask图标记区域颜色G值
	int notationB;   //mask图标记区域颜色B值
	int direction;   //图片方向
	string sourcePath;
	string maskPath;
	float size_scale; //前景物体尺寸比例
};

static Scene _scene;
static vector<info> defaultInfo;
static vector<Object> bg_objects;
static vector<Object> fg_objects;
static map<int, vector<int>> categories;
static map<int, float> priority;  //对应每类前景物体优先级，计算重叠面积时，优先级大的在上面
static float relativity[5][13] = { { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
								   { 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
								   { 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
								   { 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
	                               { 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 } };  //前景物体与背景物体之间相关性

//设置前景物体优先级
int setPriority(void);
//定义场景模板信息
int sceneDef(Scene scene);
//识别场景信息
//objInfo:输入语句中包含的物体信息，objs识别场景后所包含的物体信息，返回值为场景Scene
Scene sceneRecognize(vector<info> objInfo, vector<info> &objs);
//从数据库中选择图片
int selectPictures(vector<info> objs);
//MCMC算法优化前景物体位置
int mcmcProcess(void);

int mcmc(vector<info> objInfo, vector<Object> &bg_objs, vector<Object> &fg_objs);

#endif