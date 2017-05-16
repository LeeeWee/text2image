#ifndef TEXTPROCESS_H
#define TEXTPROCESS_H


#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

static const char * InputTxt = "D:/Desktop/InputText.txt";
static const char * OutputTxt = "D:/Desktop/OutputText.txt";

typedef struct WordLine{
	string PartofSpeech;
	string word;
}wordLine;

typedef struct Info{
	string TypeName;
	int ucount;
}info;

typedef struct Prep{
	string NameA;
	string NameB;
	string PrepType;
}prep;

static map<string, int> midword;
//��ʼ��midword
int initMap(void);
vector<string> stringToVector(stringstream &stream);
//�������ӵ��ʴ���
int generateText(string words, vector<wordLine> &outputWords);
//�Ծ��ӽ����и�
int slits(vector<wordLine> outputWords, vector<vector<wordLine>> &splitsWords);
//���������������
int semantic(vector<vector<wordLine>> splitsWords, vector<info> &Info, vector<Prep> &ObjPrep);
//��Ӣ�ĵ�����ת����int����
int stringToNum(string instr);
//�ж��Ƿ�Ϊ���Ż��߿ո�
bool isComma(char c);

int textProcess(string &word, vector<info> &objInfo, vector<prep> &objPrep);

#endif