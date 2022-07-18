#include "pch.h"
#include "CVendingMachine.h"
CVendingMachine::CVendingMachine()
{
	money = 0;

	vdrink[0] = new CDrink((CString)"��ī�ݶ�", 2000, 10);
	vdrink[1] = new CDrink((CString)"��ī�ݶ� ����", 2000,10);
	vdrink[2] = new CDrink((CString)"���", 2000,10);
	vdrink[3] = new CDrink((CString)"��� ����", 2000,10);


}
// ���Ḧ �߰��ϱ� ���� �Լ�
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
	// ������ ���� �ݾ��� 0 �̻��̸� ����� �����ȴ�.
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