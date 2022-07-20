#pragma once
#include "AccidentData.h"
#include <vector>


class DataHandler
{
	vector<AccidentData* > myDatas;


	//void Menu3_SaveData();

public:
	DataHandler();
	~DataHandler();
	//void PrintDataSingleLine(int line);
	/*void DisplayNum_3();*/
	int GetDataSize();
	int GetDatas(int line, int j);
	string GetSido(int line);

	string GetSigungu(int line);

};