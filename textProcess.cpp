#include "textProcess.h"

vector<string> stringToVector(stringstream &stream)
{
	vector<string> collect;

	string ta;
	string front, rear;

	while (stream >> ta){
		if (isComma(ta[ta.length() - 1]))
		{
			front = ta.substr(0, ta.length() - 1);
			rear = ta.substr(ta.length() - 1, 1);

			collect.push_back(front);
			collect.push_back(rear);
		}
		else
			collect.push_back(ta);
	}

	return collect;
}

int generateText(string words, vector<wordLine> &outputWords)
{
	vector<string> b;
	stringstream stream(words);
	b = stringToVector(stream);

	ofstream outFile(InputTxt, ios::out);
	if (!outFile)
	{
		return 0;
	}
	else{
		for (vector<string>::iterator iter = b.begin(); iter != b.end(); iter++)
		{
			outFile << *iter << endl;
		}
		outFile.close();
	}

	string s1 = "D:/TreeTagger3/Multi/lib/tree-tagger.exe -token -lemma  D:/TreeTagger3/Multi/lib/english-utf8.par";
	char str[200];
	sprintf_s(str, " %s %s", InputTxt, OutputTxt);
	string s2 = str;
	s1 += s2;

	char *cmd = const_cast<char *>(s1.data());
	//在命令行输入cmd，使用TreeTagger进行词性分析,将输出句子保存到OutputTxt文件中
	system(cmd);

	//将词性和单词保存到vector<wordLine>中
	ifstream read(OutputTxt);
	string tmp_in;
	string infront, inrear;
	int countword = 0;
	while (read >> tmp_in)
	{
		if (1 == countword % 3)
			infront = tmp_in;
		if (2 == countword % 3)
		{
			inrear = tmp_in;
			WordLine tmp_line;
			tmp_line.PartofSpeech = infront;
			tmp_line.word = inrear;
			outputWords.push_back(tmp_line);
		}
		countword++;
	}

	read.close();
	return 1;
}

int slits(vector<wordLine> outputWords, vector<vector<wordLine>> &splitsWords)
{
	if (outputWords.empty())
		return 0;

	vector<WordLine> current;
	for (vector<WordLine>::iterator iter = outputWords.begin(); iter != outputWords.end(); iter++)
	{
		if ("CC" == iter->PartofSpeech || "SENT" == iter->PartofSpeech)
		{
			if (current.data())
			{
				splitsWords.push_back((current)); 
				current.clear();

			}
		}

		else
			current.push_back(*iter);

	}
	return 1;
}

int semantic(vector<vector<wordLine>> splitsWords, vector<info> &Info, vector<Prep> &ObjPrep)
{
	int Size0 = splitsWords.size();
	info tmpObj;
	Prep PrepTmp;
	for (int i = 0; i < Size0; i++)
	{
		int Size1 = splitsWords[i].size();
		for (int j = 0; j < Size1; j++)
		{
			//如果是名词
			if (3 == midword[splitsWords[i][j].PartofSpeech])
			{	
				tmpObj.TypeName = splitsWords[i][j].word;
				int a = j;
				while (a){
					if (5 == midword[splitsWords[i][a - 1].PartofSpeech]){//判断名词前的单词是否是基数词
						tmpObj.ucount = stringToNum(splitsWords[i][a - 1].word);
						break;
					}
					else if (6 == midword[splitsWords[i][a - 1].PartofSpeech]){//如果是形容词，判断前一个单词
						a--;
					}
					else{
						tmpObj.ucount = 1;
						break;
					}
				}
				//if (j && 5 == midword[splitsWords[i][j - 1].PartofSpeech])//判断名词前的单词是否是基数词
				//{
				//	tmpObj.ucount = stringToNum(splitsWords[i][j - 1].word);
				//}
				//else
				//{
				//	tmpObj.ucount = 1;
				//}
				Info.push_back(tmpObj);
			}
			if (1 == midword[splitsWords[i][j].PartofSpeech])
			{
				PrepTmp.PrepType = splitsWords[i][j].word;
				int m, n;
				bool confirm0 = false;
				bool confirm1 = false;
				m = n = j;
				while (m > 0 && n < Size1 && (!confirm0 || !confirm1))
				{
					if (midword[splitsWords[i][m].PartofSpeech] != 3)
						m--;
					else
					{
						PrepTmp.NameA = splitsWords[i][m].word;
						confirm0 = true;
					}
					if (midword[splitsWords[i][n].PartofSpeech] != 3)
						n++;
					else
					{
						PrepTmp.NameB = splitsWords[i][n].word;
						confirm1 = true;
					}
				}
				if (confirm1&&confirm0)
					ObjPrep.push_back(PrepTmp);
			}

		}
	}
	if (!ObjPrep.empty())
		return 2;
	else if (!Info.empty())
		return 1;
	else
		return 0;
}


int initMap(void)
{
	//名词或人称代词
	midword.insert(pair<string, int>("NNS", 3));
	midword.insert(pair<string, int>("NN", 3));
	midword.insert(pair<string, int>("NP", 3));
	midword.insert(pair<string, int>("NPS", 3));
	midword.insert(pair<string, int>("PP", 3));
	midword.insert(pair<string, int>("PP$", 3));

	//动词
	midword.insert(pair<string, int>("VV", 2));
	midword.insert(pair<string, int>("VVD", 2));
	midword.insert(pair<string, int>("VVP", 2));
	midword.insert(pair<string, int>("VVN", 2));
	midword.insert(pair<string, int>("VVZ", 2));
	midword.insert(pair<string, int>("VVG", 2));
	midword.insert(pair<string, int>("VH", 2));
	midword.insert(pair<string, int>("VHD", 2));
	midword.insert(pair<string, int>("VHG", 2));
	midword.insert(pair<string, int>("VHN", 2));
	midword.insert(pair<string, int>("VHZ", 2));
	midword.insert(pair<string, int>("VHP", 2));
	midword.insert(pair<string, int>("VB", 2));
	midword.insert(pair<string, int>("VBD", 2));
	midword.insert(pair<string, int>("VBN", 2));
	midword.insert(pair<string, int>("VBP", 2));
	midword.insert(pair<string, int>("VBG", 2));
	midword.insert(pair<string, int>("VBZ", 2));
	midword.insert(pair<string, int>("VD", 2));
	midword.insert(pair<string, int>("VDD", 2));
	midword.insert(pair<string, int>("VDG", 2));
	midword.insert(pair<string, int>("VDN", 2));
	midword.insert(pair<string, int>("VDP", 2));
	midword.insert(pair<string, int>("VDZ", 2));

	//冠词
	midword.insert(pair<string, int>("DT", 7));

	//基数词
	midword.insert(pair<string, int>("CD", 5));

	//介词
	midword.insert(pair<string, int>("IN", 1));

	//连词
	midword.insert(pair<string, int>("CC", 4));

	//形容词
	midword.insert(pair<string, int>("JJ", 6));

	return 0;
}

int stringToNum(string instr)
{
	if (instr.empty())
		return -1;
	if (instr[0] >= 'A' && instr[0] <= 'Z')
		instr[0] -= 'A' - 'a';

	map<string, int> Numbers;
	Numbers.insert(pair<string, int>("zero", 0));
	Numbers.insert(pair<string, int>("one", 1));
	Numbers.insert(pair<string, int>("two", 2));
	Numbers.insert(pair<string, int>("three", 3));
	Numbers.insert(pair<string, int>("four", 4));
	Numbers.insert(pair<string, int>("five", 5));
	Numbers.insert(pair<string, int>("six", 6));
	Numbers.insert(pair<string, int>("seven", 7));
	Numbers.insert(pair<string, int>("eight", 8));
	Numbers.insert(pair<string, int>("nine", 9));
	int ans;
	ans = Numbers[instr];
	return ans;
}

bool isComma(char c)
{

	char commas[] = { ',', '.', '!', '/', '?', ':', ':' };
	int s = sizeof(commas) / sizeof(char);
	while (s--)
	{
		if (commas[s] == c)
			return true;
	}
	return false;
}

int textProcess(string &word, vector<info> &objInfo, vector<prep> &objPrep)
{
	initMap();
	vector<wordLine> outputWords;
	vector<vector<wordLine>> splitsWords;
	if (!generateText(word, outputWords))
	{
		cout << "Text processing failed!" << endl;
		return 0;
	}
	if (!slits(outputWords, splitsWords))
	{
		cout << "Text processing failed!" << endl;
		return 0;
	}
	//for (vector <vector<wordLine>>::iterator iter0 = splitsWords.begin(); iter0 != splitsWords.end(); iter0++)
	//{
	//	for (vector<wordLine>::iterator iter1 = iter0->begin(); iter1 != iter0->end(); iter1++)
	//	{
	//		cout << distance(iter0, splitsWords.begin()) << iter1->word << " " << iter1->PartofSpeech << endl;
	//	}
	//}
	if (!semantic(splitsWords, objInfo, objPrep))
	{
		cout << "Failed to recognize the word's scene information!" << endl;
		return 0;
	}
	for (vector<info>::iterator iter = objInfo.begin(); iter != objInfo.end(); iter++)
	{
		cout << "Typename:" << iter->TypeName << " " << "ucount:" << iter->ucount << endl;
	}
	if (objPrep.size() != 0)
	{
		for (vector<prep>::iterator iter = objPrep.begin(); iter != objPrep.end(); iter++)
		{
			cout << "NameA:" << iter->NameA << " prep:" << iter->PrepType << " NameB:" << iter->NameB << endl;
		}
	}

	return 1;

}