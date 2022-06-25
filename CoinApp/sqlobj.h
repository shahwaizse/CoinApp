#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdlib.h>
#include <sal.h>

using namespace std;

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000
#define SQL_QUERY_LEN 1000

struct walletdata {
    vector<int> amount;
    vector<string> coin_id;
};

class sqlobj {
public:
    //define handles and variables
    SQLHANDLE sqlConnHandle;
    SQLHSTMT    hStmt;
    SQLHANDLE sqlEnvHandle;
    SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
    WCHAR wszInput[SQL_QUERY_LEN];
    SQLRETURN rc;
    sqlobj() {
        SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle);
        SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
        SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle);
        SQLDriverConnectW(sqlConnHandle,
            NULL,
            (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=KOMPOOTER;DATABASE=bitcoin1;Trusted=true;",
            SQL_NTS,
            retconstring,
            1024,
            NULL,
            SQL_DRIVER_NOPROMPT);
        SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &hStmt);
    }
    void exec(SQLWCHAR* s) {
        SQLExecDirect(hStmt, s, SQL_NTS);
    }
    void exec_dynamic(std::wstring s) {
        SQLWCHAR* statement = (SQLWCHAR*)s.c_str();
        SQLExecDirect(hStmt, statement, SQL_NTS);
    }
    std::string queryreturn_string30(std::wstring s) {
        //SQLExecDirect(hStmt, (SQLWCHAR*)L"use bitcoin1", SQL_NTS);
        char result[30] = "";
        SQLBindCol(hStmt, 1, SQL_C_CHAR, result, sizeof(result), 0);
        SQLWCHAR* statement = (SQLWCHAR*)s.c_str();
        SQLExecDirect(hStmt, statement, SQL_NTS);
        SQLFetch(hStmt);
        std::string to_return(result);
        return to_return;
    }

    int queryreturn_int(std::wstring s) {
        //SQLExecDirect(hStmt, (SQLWCHAR*)L"use bitcoin1", SQL_NTS);
        int result;
        SQLBindCol(hStmt, 1, SQL_C_ULONG, &result, 0, 0);
        SQLWCHAR* statement = (SQLWCHAR*)s.c_str();
        SQLExecDirect(hStmt, statement, SQL_NTS);
        SQLFetch(hStmt);
        return result;
    }

    float queryreturn_float(std::wstring s) {
        //SQLExecDirect(hStmt, (SQLWCHAR*)L"use bitcoin1", SQL_NTS);
        float result;
        SQLBindCol(hStmt, 1, SQL_C_FLOAT, &result, 0, 0);
        SQLWCHAR* statement = (SQLWCHAR*)s.c_str();
        SQLExecDirect(hStmt, statement, SQL_NTS);
        SQLFetch(hStmt);
        return result;
    }

    walletdata showwallet(std::wstring s) {
        walletdata w1;
        char coinid[30];
        int amount0;

        SQLWCHAR* statement = (SQLWCHAR*)s.c_str();
        SQLExecDirect(hStmt, statement, SQL_NTS);
        SQLBindCol(hStmt, 1, SQL_C_CHAR, coinid, sizeof(coinid), 0);
        SQLBindCol(hStmt, 2, SQL_C_ULONG, &amount0, 0, 0);

        SQLExecDirect(hStmt, statement, SQL_NTS);

        while (SQLFetch(hStmt) != SQL_NO_DATA) {
            w1.amount.push_back(amount0);
            string s(coinid);
            w1.coin_id.push_back(s);
        }

        return w1;
    }

    ~sqlobj() {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        SQLDisconnect(sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
    }
};