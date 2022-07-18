#pragma once
#include <cstring>

using namespace std;

class CDrink
{
public:
	CDrink(CString _name, int _price, int _stock);
	~CDrink();
	int GetPrice();
	int GetStock();
	void SubStock();
	CString GetName();
private:
	CString name;
	int price;
	int stock;
};

