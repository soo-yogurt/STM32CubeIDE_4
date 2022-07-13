#pragma once
#include "CMysqlController.h"
#include <vector>

using namespace std;

class CbookData
{
	CString id;
	CString bookName;
	CString author;
	CString price;
	CString other;

public:
	CbookData(CString _id, CString _bookName, CString _author,
		CString _price, CString _other);
	~CbookData() {}
	

	CString Getid();
	CString GetbookName();
	CString Getauthor();
	CString Getprice();
	CString Getother();

};


