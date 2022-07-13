#pragma once
#include <mysql.h> // ���⼭ ������ ��Ÿ���ٸ� ���̺귯�� ������ ���������� ���Ѵ�.
#include <vector>
#include "CbookData.h"



#define USER 1

#if (USER == 1)
#define DB_HOST "127.0.0.1" // ���� �����Ǹ� ���°��̴� �ش� �����Ǵ� ������ ������ ���Ѵ�.
#define DB_USER "root"//DB ���� ����
#define DB_PASS "1234"//DB ���� ��ȣ
#define DB_NAME "bookdb"//DB �̸�

#elif (USER == 2)

// �� ��ǻ�� IP
#define DB_HOST "192.168.22.30"
#define DB_USER "testuser1"//DB ���� ����
#define DB_PASS "4321"//DB ���� ��ȣ
#define DB_NAME "bookdb"//DB �̸�


#elif (USER == 3)
// ������ ��ǻ�� IP
#define DB_HOST "192.168.22.10"
#define DB_USER "testuser1"//DB ���� ����
#define DB_PASS "4321"//DB ���� ��ȣ
#define DB_NAME "book_db"//DB �̸�

#endif




using namespace std;

class CbookData; // ����� ���������� �ν� ���� ���� �� �߰� �ؾ��ϴ� ��

class CMysqlController
{
public:
	CMysqlController();
	~CMysqlController();
	bool SelectQuery(char* sql, vector<CbookData*> &books);
	bool InsertQuery(char* sql);
};

