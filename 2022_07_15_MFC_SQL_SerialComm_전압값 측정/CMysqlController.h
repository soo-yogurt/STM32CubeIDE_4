#pragma once
#include <vector>
#include "CValueData.h"
#include <mysql.h>

#define DB_HOST "127.0.0.1"	// ���� ������
#define DB_USER "root"	// DB ���Ӱ���
#define DB_PASS "1234"	// DB ������ȣ
#define DB_NAME "adcdb"	// DB �̸�

using namespace std;

class CMysqlController
{
public:
	CMysqlController();
	~CMysqlController();
	bool SelectQuery(char* sql, vector<CValueData*>& result);
	bool InsertQuery(char* sql);
};

