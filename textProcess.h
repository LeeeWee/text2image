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
//初始化midword
int initMap(void);
vector<string> stringToVector(stringstream &stream);
//分析句子单词词性
int generateText(string words, vector<wordLine> &outputWords);
//对句子进行切割
int slits(vector<wordLine> outputWords, vector<vector<wordLine>> &splitsWords);
//分析场景物体个数
int semantic(vector<vector<wordLine>> splitsWords, vector<info> &Info, vector<Prep> &ObjPrep);
//将英文的数字转换成int类型
int stringToNum(string instr);
//判断是否为符号或者空格
bool isComma(char c);

int textProcess(string &word, vector<info> &objInfo, vector<prep> &objPrep);

#endif