#include "pch.h"
#include "DataHandler.h"
#include <iostream>
#include <conio.h>
#include <sstream> 
#include <fstream> 
#include <string>


DataHandler::DataHandler() {

	ifstream  data("ANSIData.csv");
	string line;
	while (std::getline(data, line)) // data 파일에서 읽은 자료를 line에 초기화 한다.
	{
		stringstream lineStream(line);
		string cell;
		string tmpsido;
		string tmpsigungu;
		int tmpdatas[11];
		int idx = 0;
		while (std::getline(lineStream, cell, ','))
		{
			if (idx == 0)
			{
				tmpsido = cell;
			}
			else if (idx == 1)
			{
				tmpsigungu = cell;
			}
			else
			{
				if (cell == "-")
					tmpdatas[idx - 2] = 0;
				else
					tmpdatas[idx - 2] = stoi(cell);
			}
			idx++;
		}
		myDatas.push_back(new AccidentData(tmpsido, tmpsigungu, tmpdatas));
	}
}
DataHandler::~DataHandler()
{

	for (int i = 0; i < myDatas.size(); i++)
		delete myDatas[i];
}


string DataHandler::GetSido(int line)
{
	return myDatas.at(line)->GetSido();
}
string DataHandler::GetSigungu(int line)
{
	return myDatas[line]->GetSigungu();
}
int DataHandler::GetDatas(int line, int j)
{
	return myDatas[line]->GetDatas(j);
}

int DataHandler::GetDataSize()
{
	return myDatas.size();
}