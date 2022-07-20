#pragma once
#include "CDrink.h"
using namespace std;

class CVendingMachine {

	CDrink * vdrink[4];
	//CDrink vdrink[4];
	int money;

public:
	CVendingMachine();
	~CVendingMachine()
	{
		delete[0] vdrink;
		delete[1] vdrink;
		delete[2] vdrink;
		delete[3] vdrink;
	}
	void PushDrink();
	void SetMoney(int _money);
	void Purchase(int num); 
	int GetMoney() const;
	CString GetName(int num);
	int GetPrice(int nume);

};