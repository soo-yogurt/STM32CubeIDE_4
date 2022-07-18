#pragma once
#include <vector>
#include "CValueData.h"
#include <mysql.h>

#define DB_HOST "127.0.0.1"	// 서버 아이피
#define DB_USER "root"	// DB 접속계정
#define DB_PASS "1234"	// DB 계정암호
#define DB_NAME "adcdb"	// DB 이름

using namespace std;

class CMysqlController
{
public:
	CMysqlController();
	~CMysqlController();
	bool SelectQuery(char* sql, vector<CValueData*>& result);
	bool InsertQuery(char* sql);
};

