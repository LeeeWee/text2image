#include "adoPrcoess.h"
#include <icrsint.h>
#include <string>
#include <ctime>
#include <algorithm>
#include "opencv2/imgproc.hpp"  
#include "opencv2/core/core.hpp"  
#include <opencv2/highgui/highgui.hpp>  
using namespace std;
using namespace cv;

#import "c:\program files\common files\system\ado\msado15.dll"  no_namespace rename("EOF", "adoEOF")
//这是导入连接数据库的库文件，必须的，而且这个字符串基本可以不变。

int ConnectImageNet(_ConnectionPtr &pMyConnect)
{
	CoInitialize(NULL);//初始化Com库
	HRESULT hr = pMyConnect.CreateInstance(__uuidof(Connection));//将对象指针实例化
	if (FAILED(hr)){
		cout << "_ConnectionPtr对象指针实例化失败！" << endl;
		return 0;
	}
	//这是连接到SQL SERVER数据库的连接字符串，其中的参数要自己改
	_bstr_t strConnect = "Driver={sql server};server=DELL-PC;uid=sa;pwd=lw19941014;database=ImageLib";  //SQLSERVER

	try{ pMyConnect->Open(strConnect, "", "", NULL); }//连接到数据库，要捕捉异常
	catch (_com_error &e){
		cout << e.ErrorMessage() << endl;
		return 0;
	}
	return 1;
}

int imagesetClassify(map<int, vector<int>> &categories)
{
	_ConnectionPtr pMyConnect = NULL;
	if (!ConnectImageNet(pMyConnect))
		return 0;

	//连接到数据库后，开始执行SQL语句
	_RecordsetPtr m_pRecordset;//记录集对象指针，用来执行SQL语句并记录查询结果
	if (FAILED(m_pRecordset.CreateInstance(__uuidof(Recordset)))){
		cout << "记录集对象指针实例化失败！" << endl;
		return 0;
	}

	try{
		m_pRecordset->Open(_variant_t("Image"),
			_variant_t((IDispatch *)pMyConnect, true),
			adOpenKeyset, adLockOptimistic, adCmdTable);//打开数据库Image表，执行SQL语句
	}
	catch (_com_error &e){
		cout << e.ErrorMessage() << endl;
	}

	vector<int> vector1, vector2, vector3, vector4, vector5,
		vector11, vector12, vector13, vector14, vector15, vector16,
		vector17, vector18, vector19, vector20, vector21, vector22, vector23;

	try{
		m_pRecordset->MoveFirst(); //记录集指针移动到查询结果集的前面
		while (m_pRecordset->adoEOF == VARIANT_FALSE)
		{
			int ino = (int)(m_pRecordset->Fields->GetItem(_variant_t("Ino"))->Value);
			int category = (int)(m_pRecordset->Fields->GetItem(_variant_t("Category"))->Value);
			switch (category)
			{
				case 1:		vector1.push_back(ino);			break;
				case 2:		vector2.push_back(ino);			break;
				case 3:		vector3.push_back(ino);			break;
				case 4:		vector4.push_back(ino);			break;
				case 5:		vector5.push_back(ino);			break;
				case 11:	vector11.push_back(ino);		break;
				case 12:	vector12.push_back(ino);		break;
				case 13:	vector13.push_back(ino);		break;
				case 14:	vector14.push_back(ino);		break;
				case 15:	vector15.push_back(ino);		break;
				case 16:	vector16.push_back(ino);		break;
				case 17:	vector17.push_back(ino);		break;
				case 18:	vector18.push_back(ino);		break;
				case 19:	vector19.push_back(ino);		break;
				case 20:	vector20.push_back(ino);		break;
				case 21:	vector21.push_back(ino);		break;
				case 22:	vector22.push_back(ino);		break;
				case 23:	vector23.push_back(ino);		break;
				default:	break;
			}
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error &e){
		cout << e.ErrorMessage() << endl;
		return 0;
	}
	categories.insert(pair<int, vector<int>>(1, vector1));
	categories.insert(pair<int, vector<int>>(2, vector2));
	categories.insert(pair<int, vector<int>>(3, vector3));
	categories.insert(pair<int, vector<int>>(4, vector4));
	categories.insert(pair<int, vector<int>>(5, vector5));
	categories.insert(pair<int, vector<int>>(11, vector11));
	categories.insert(pair<int, vector<int>>(12, vector12));
	categories.insert(pair<int, vector<int>>(13, vector13));
	categories.insert(pair<int, vector<int>>(14, vector14));
	categories.insert(pair<int, vector<int>>(15, vector15));
	categories.insert(pair<int, vector<int>>(16, vector16));
	categories.insert(pair<int, vector<int>>(17, vector17));
	categories.insert(pair<int, vector<int>>(18, vector18));
	categories.insert(pair<int, vector<int>>(19, vector19));
	categories.insert(pair<int, vector<int>>(20, vector20));
	categories.insert(pair<int, vector<int>>(21, vector21));
	categories.insert(pair<int, vector<int>>(22, vector22));
	categories.insert(pair<int, vector<int>>(23, vector23));
	return 1;
}

//随机选取n张图片
int randomSelectN(int n, vector<int> originV, vector<int> &v) 
{ 
	srand(unsigned(time(NULL)));
	int temp;
	for (int i = 0; i < n; ) {
		temp = originV[rand() % originV.size()];
		vector<int>::iterator it;
		it = find(v.begin(), v.end(), temp);
		if (it == v.end()) { //vec中不存在value值
			v.push_back(temp);
			i++;
		}
	}

	//随机打乱originV，然后取前n个值
	//random_shuffle(originV.begin(), originV.end());
	//for (int i = 0; i < n; i++) {
	//	v.push_back(originV[i]);
	//}
	return 1;
}

int randomSelect(vector<int> originV)
{
	srand(unsigned(time(NULL)));
	int temp;
	temp = originV[rand() % originV.size()];
	return temp;
}

//获得物体区域尺寸
Size getImageSize(short R, short G, short B, string imagePath)
{
	Mat mask = imread(imagePath, CV_LOAD_IMAGE_COLOR);
	int nr = mask.rows;
	int nc = mask.cols;
	Mat b_mask(nr, nc, CV_8UC1);
	if (mask.isContinuous())
	{
		nr = 1;
		nc = nc*mask.rows;
	}
	Scalar color = Scalar(B, G, R);
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
			if (chscl == color)
				//if(chscl[0] == c[0] && chscl[1] == c[1] && chscl[2] == c[2])
				*Data1++ = 255;
			else
				*Data1++ = 0;
		}
	}
	threshold(b_mask, b_mask, 99, 255, CV_THRESH_BINARY);

	int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;
	for (int i = 0; i < mask.rows; i++){
		for (int j = 0; j < mask.cols; j++){
			if (b_mask.at<uchar>(i, j) == 255)
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
	Size size = Size(leny, lenx);
	return size;
}

int selectImage(Object *obj)
{
	int n = obj->imagesetId;
	_ConnectionPtr pMyConnect = NULL;
	if (!ConnectImageNet(pMyConnect))
		return 0;

	//连接到数据库后，开始执行SQL语句
	_RecordsetPtr m_pRecordset;//记录集对象指针，用来执行SQL语句并记录查询结果
	if (FAILED(m_pRecordset.CreateInstance(__uuidof(Recordset)))){
		cout << "记录集对象指针实例化失败！" << endl;
		return 0;
	}

	try{
		m_pRecordset->Open(_variant_t("Image"),
			_variant_t((IDispatch *)pMyConnect, true),
			adOpenKeyset, adLockOptimistic, adCmdTable);//打开数据库Image表，执行SQL语句
	}
	catch (_com_error &e){
		cout << e.ErrorMessage() << endl;
	}

	try{
		m_pRecordset->MoveFirst(); //记录集指针移动到查询结果集的前面
		while (m_pRecordset->adoEOF == VARIANT_FALSE)
		{
			int ino = (int)(m_pRecordset->Fields->GetItem(_variant_t("Ino"))->Value);
			if (ino != n)
				m_pRecordset->MoveNext();
			else {
				_StreamPtr pStm;
				pStm.CreateInstance("ADODB.Stream");
				variant_t varOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
				pStm->PutType(adTypeBinary);//类型为二进制
				pStm->Open(varOptional, adModeUnknown, adOpenStreamUnspecified, _bstr_t(), _bstr_t());
				//打开pStm
				pStm->Write(_variant_t(m_pRecordset->GetFields()->GetItem("Source")->Value));
				char source_path[50];
				sprintf_s(source_path, "D:/Desktop/GraduationImage/source %d.bmp", n);
				pStm->SaveToFile(source_path, adSaveCreateOverWrite);
				pStm->Close();
				pStm->Open(varOptional, adModeUnknown, adOpenStreamUnspecified, _bstr_t(), _bstr_t());
				pStm->Write(_variant_t(m_pRecordset->GetFields()->GetItem("Mask")->Value));
				char mask_path[50];
				sprintf_s(mask_path, "D:/Desktop/GraduationImage/mask %d.bmp", n);
				pStm->SaveToFile(mask_path, adSaveCreateOverWrite);
				pStm->Close();
				int category = (int)(m_pRecordset->Fields->GetItem(_variant_t("Category"))->Value);
				short r = (short)(m_pRecordset->Fields->GetItem(_variant_t("NotationColorR"))->Value);
				short g = (short)(m_pRecordset->Fields->GetItem(_variant_t("NotationColorG"))->Value);
				short b = (short)(m_pRecordset->Fields->GetItem(_variant_t("NotationColorB"))->Value);
				short d = (short)(m_pRecordset->Fields->GetItem(_variant_t("Direction"))->Value);
				if (category >= 11 && category <= 23) {
					float sizeScale = (float)(m_pRecordset->Fields->GetItem(_variant_t("SizeScale"))->Value);
					obj->size_scale = sizeScale;
				}
				obj->sourcePath = source_path;
				obj->maskPath = mask_path;
				obj->notationR = r;
				obj->notationG = g;
				obj->notationB = b;
				obj->direction = d;
				obj->origin_size = getImageSize(r, g, b, mask_path);
				break;
			}
		}
	}
	catch (_com_error &e){
		cout << e.ErrorMessage() << endl;
		return 0;
	}
	return 1;
}
