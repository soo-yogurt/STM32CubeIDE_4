#include "pch.h"
#include "CDrink.h"

CDrink::CDrink(CString _name, int _price, int _stock)
	: name(_name), price(_price), stock(stock)
{
}

CDrink::~CDrink()
{}



int CDrink::GetPrice()
{
	return this->price;
}
int CDrink::GetStock()
{
	return this->stock;
}
void CDrink::SubStock()
{
	this->stock--;
}

CString CDrink::GetName()
{
	return name;
}

