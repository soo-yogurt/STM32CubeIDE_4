#pragma once
class CValueData
{
	CString id;
	CString value;
	CString time;
public:
	CValueData(CString _id, CString _value, CString _time)
		: id(_id), value(_value), time(_time)
	{}
	~CValueData() {}

	CString Getid();
	CString Getvalue();
	CString Getime();
};

