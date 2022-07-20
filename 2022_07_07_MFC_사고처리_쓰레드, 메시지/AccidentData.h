#pragma once
#include <cstring>
#include <string>
using namespace std;

class AccidentData {

	string sido;
	string sigungu;
	int data[11];

public:
	AccidentData(string _sido, string _sogungu, int _data[]);
	string GetSido();
	string GetSigungu();
	int GetDatas(int i);

};