#ifndef ADOPROCESS_H
#define ADOPROCESS_H

#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include "mcmcProc.h"
using namespace std;

//�����ݿ��е�ͼƬ�����й���
int imagesetClassify(map<int, vector<int>> &categories);

//��originV�����ѡ��n�������v
int randomSelectN(int n, vector<int> originV, vector<int> &v);

//��originV�����ѡ��1����
int randomSelect(vector<int> originV);

//�����ݿ���ѡ��idΪn��ͼƬ����
int selectImage(Object *obj);

#endif