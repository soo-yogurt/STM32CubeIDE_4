#pragma once
#include <mysql.h> // 여기서 오류가 나타난다면 라이브러리 설정에 실패했음을 뜻한다.
#include <vector>
#include "CbookData.h"



#define USER 1

#if (USER == 1)
#define DB_HOST "127.0.0.1" // 서버 아이피를 적는곳이다 해당 아이피는 본인의 서버를 뜻한다.
#define DB_USER "root"//DB 접속 계정
#define DB_PASS "1234"//DB 계정 암호
#define DB_NAME "bookdb"//DB 이름

#elif (USER == 2)

// 내 컴퓨터 IP
#define DB_HOST "192.168.22.30"
#define DB_USER "testuser1"//DB 접속 계정
#define DB_PASS "4321"//DB 계정 암호
#define DB_NAME "bookdb"//DB 이름


#elif (USER == 3)
// 교수님 컴퓨터 IP
#define DB_HOST "192.168.22.10"
#define DB_USER "testuser1"//DB 접속 계정
#define DB_PASS "4321"//DB 계정 암호
#define DB_NAME "book_db"//DB 이름

#endif




using namespace std;

class CbookData; // 헤더를 선언했지만 인식 하지 못할 때 추가 해야하는 것

class CMysqlController
{
public:
	CMysqlController();
	~CMysqlController();
	bool SelectQuery(char* sql, vector<CbookData*> &books);
	bool InsertQuery(char* sql);
};

