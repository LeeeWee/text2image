#ifndef MCMCPROC_H
#define MCMCPROC_H

#include <iostream>
#include <map>
#include <string>
#include "textProcess.h"
#include "opencv2/core/core.hpp"  
using namespace std;
using namespace cv;

const int Width = 600;//�ϳ�ͼƬ���
const int Height = 450;//�ϳ�ͼƬ�߶�
const int Itertions = 10000;  //MCMC�㷨��������

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
//��ʼ��typeIdMap
int initTypeIdMap(void);

//����һ���������
class Object
{
public:
	Object(string name) :typeName(name)
	{
		typeId = typeIdMap[name];
	}
	string typeName;
	int typeId;
	Size origin_size; //ǰ����������ͼƬ�ĳ�ʼ�ߴ�
	Rect rect;        //ͼƬ�����ճߴ�λ��
	int imagesetId;
	int notationR;   //maskͼ���������ɫRֵ
	int notationG;	 //maskͼ���������ɫGֵ
	int notationB;   //maskͼ���������ɫBֵ
	int direction;   //ͼƬ����
	string sourcePath;
	string maskPath;
	float size_scale; //ǰ������ߴ����
};

static Scene _scene;
static vector<info> defaultInfo;
static vector<Object> bg_objects;
static vector<Object> fg_objects;
static map<int, vector<int>> categories;
static map<int, float> priority;  //��Ӧÿ��ǰ���������ȼ��������ص����ʱ�����ȼ����������
static float relativity[5][13] = { { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
								   { 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
								   { 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
								   { 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
	                               { 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 } };  //ǰ�������뱳������֮�������

//����ǰ���������ȼ�
int setPriority(void);
//���峡��ģ����Ϣ
int sceneDef(Scene scene);
//ʶ�𳡾���Ϣ
//objInfo:��������а�����������Ϣ��objsʶ�𳡾�����������������Ϣ������ֵΪ����Scene
Scene sceneRecognize(vector<info> objInfo, vector<info> &objs);
//�����ݿ���ѡ��ͼƬ
int selectPictures(vector<info> objs);
//MCMC�㷨�Ż�ǰ������λ��
int mcmcProcess(void);

int mcmc(vector<info> objInfo, vector<Object> &bg_objs, vector<Object> &fg_objs);

#endif