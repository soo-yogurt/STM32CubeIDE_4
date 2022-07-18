#include "pch.h"
#include "AccidentData.h"

AccidentData::AccidentData(string _sido, string _sigungu, int _data[11])
	:sido(_sido), sigungu(_sigungu)
{
	for (int i = 0; i < 11; i++)
	{
		data[i] = _data[i];
	}
}

string AccidentData::GetSido()
{
	return sido;
}
string AccidentData::GetSigungu()
{
	return sigungu;
}
int AccidentData::GetDatas(int i)
{
	return data[i];
}
