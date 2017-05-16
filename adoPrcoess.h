#ifndef ADOPROCESS_H
#define ADOPROCESS_H

#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include "mcmcProc.h"
using namespace std;

//对数据库中的图片类别进行归类
int imagesetClassify(map<int, vector<int>> &categories);

//从originV中随机选出n个数组成v
int randomSelectN(int n, vector<int> originV, vector<int> &v);

//从originV中随机选出1个数
int randomSelect(vector<int> originV);

//从数据库中选出id为n的图片数据
int selectImage(Object *obj);

#endif