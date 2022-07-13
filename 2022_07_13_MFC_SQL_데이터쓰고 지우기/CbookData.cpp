#include "pch.h"
#include "CbookData.h"


CbookData::CbookData(CString _id, CString _bookName, CString _author, CString _price, CString _other)
{
	this->id = _id;
	bookName = _bookName;
	author = _author;
	price = _price;
	other = _other;
}

CString CbookData::Getid()
{
	return id;
}

CString CbookData::GetbookName()
{           
	return bookName;
}
CString CbookData::Getauthor()
{
	return author;
}
CString CbookData::Getprice()
{
	return price;
}
CString CbookData::Getother()
{
	return other;
}
