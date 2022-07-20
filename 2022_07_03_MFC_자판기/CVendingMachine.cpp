#include "pch.h"
#include "CVendingMachine.h"
CVendingMachine::CVendingMachine()
{
	money = 0;

	vdrink[0] = new CDrink((CString)"코카콜라", 2000, 10);
	vdrink[1] = new CDrink((CString)"코카콜라 제로", 2000,10);
	vdrink[2] = new CDrink((CString)"펩시", 2000,10);
	vdrink[3] = new CDrink((CString)"펩시 제로", 2000,10);


}
// 음료를 추가하기 위한 함수
void CVendingMachine::PushDrink() 
{}
void CVendingMachine::SetMoney(int _money)
{
	money += _money;
}
int CVendingMachine::GetMoney() const
{
	return money;
}

void CVendingMachine::Purchase(int num)
{
	// 음료의 수와 금액이 0 이상이면 계산이 차감된다.
	if(money - vdrink[num]->GetPrice() >= 0)
		money -= vdrink[num]->GetPrice();
	if(vdrink[num]->GetStock() > 0)
		vdrink[num]->SubStock();
}

CString CVendingMachine::GetName(int num)
{
	return vdrink[num]->GetName();
}

int CVendingMachine::GetPrice(int num)
{
	return vdrink[num]->GetPrice();
}