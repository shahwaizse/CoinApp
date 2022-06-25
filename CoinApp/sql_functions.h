#pragma once
#include "sqlobj.h"
#include<iostream>
#include<string>

using namespace std;

int registeruser(string username, string password) {
	sqlobj registerobj;
	//wstring wuid = to_wstring(userid);
	wstring un(username.begin(), username.end());
	wstring pw(password.begin(), password.end());
	int sum = 0;
	for (int x = 0; x < username.size(); x++) {
		sum = sum + username[x];
	}
	wstring cid = to_wstring(sum);
	//registerobj.exec((SQLWCHAR*)L"use bitcoin1");
	string check;
	wstring query0 = L"select cus_id from authenticate where cus_id = " + cid;
	check = registerobj.queryreturn_string30(query0);
	wstring wcheck(check.begin(), check.end());
	if (cid != wcheck) {
		sqlobj wowobj;
		wstring query = L"insert into customer (cus_id, username) values (" + cid + L", '" + un + L"')";
		wstring query2 = L"insert into waltet_main(wallet_id) values(" + cid + L")";
		wstring query3 = L"insert into authenticate (pass_word, cus_id) values ('" + pw + L"', " + cid + L")";
		wowobj.exec_dynamic(query);
		wowobj.exec_dynamic(query2);
		wowobj.exec_dynamic(query3);
		return sum;
	}
	else {
		return 0;
	}
}

int loginuser(string username, string password) {
	sqlobj loginobj;
	wstring un(username.begin(), username.end());
	wstring pw(password.begin(), password.end());
	int sum = 0;
	for (int x = 0; x < username.size(); x++) {
		sum = sum + username[x];
	}
	wstring cid = to_wstring(sum);
	wstring query = L"select pass_word from authenticate where cus_id = "+cid;
	string check;
	check = loginobj.queryreturn_string30(query);
	if (check == password) {
		return sum;
	}
	else {
		return 0;
	}
}

void updateprice(float price, float c_rate, string c_id) {
	sqlobj priceobj;
	//priceobj.exec((SQLWCHAR*)L"use bitcoin1");
	wstring wcid(c_id.begin(), c_id.end());
	wstring wprice = to_wstring(price);
	wstring wrate = to_wstring(c_rate);
	wstring query = L"update coin set coin_price = " + wprice + L", change_rate = " + wrate + L" where coin_id = '" + wcid + L"'";
	priceobj.exec_dynamic(query);
}

void buycoin(string coinid, int amount, int walletid) {
	sqlobj obj1;
	wstring wcoinid(coinid.begin(), coinid.end());
	wstring wamount = to_wstring(amount);
	wstring wid = to_wstring(walletid);

	sqlobj obj2;
	wstring query0 = L"select coin_price from coin where coin_id = '" + wcoinid + L"'";
	float cprice = obj2.queryreturn_float(query0);
	cprice = cprice * amount;
	wstring wprice = to_wstring(cprice);

	sqlobj obj3;
	wstring checkcoin = L"select coin_id from walet where wallet_id = " + wid + L" AND coin_id = '" + wcoinid + L"'";
	string result;
	result = obj3.queryreturn_string30(checkcoin);

	if (result == coinid) {
		sqlobj obj;
		wstring query1 = L"update walet set coin_amount = (coin_amount + " + wamount + L") where wallet_id = " + wid + L" AND coin_id = '" + wcoinid + L"'";
		wstring query2 = L"update waltet_main set totalbalance = (totalbalance - " + wprice + L") where wallet_id = " + wid;
		obj.exec_dynamic(query1);
		obj.exec_dynamic(query2);
	}
	else {
		sqlobj obj8;
		wstring query3 = L"insert into walet(wallet_id, coin_id, coin_amount) values (" + wid + L", '" + wcoinid + L"', " + wamount + L")";
		wstring query4 = L"update waltet_main set totalbalance = (totalbalance - " + wprice + L") where wallet_id = " + wid;
		obj8.exec_dynamic(query3);
		obj8.exec_dynamic(query4);
	}
}

void sellcoin(string coinid, float c_amount, int walletid) {
	sqlobj sellobj;
	wstring wcoinid(coinid.begin(), coinid.end());
	wstring query0 = L"select coin_price from coin where coin_id = '" + wcoinid + L"'";
	float cprice = sellobj.queryreturn_float(query0);
	wstring wamount = to_wstring(c_amount);
	wstring wprice = to_wstring(cprice);
	float updatetotalbalance = c_amount * cprice;
	wstring wid = to_wstring(walletid);
	wstring wbalance = to_wstring(updatetotalbalance);

	sqlobj obj0;
	wstring holdcoin = L"select coin_amount from walet where wallet_id = " + wid + L" AND coin_id = '" + wcoinid + L"'";
	int coin_amount = obj0.queryreturn_int(holdcoin);
	if (c_amount > coin_amount) {
		cout << "error";
	}
	if (c_amount == coin_amount) {
		sqlobj obj1;
		wstring query1 = L"delete from Walet where coin_id = '" + wcoinid + L"' AND wallet_id = " + wid;
		wstring query2 = L"update waltet_main set totalbalance = (totalbalance + " + wbalance + L") where wallet_id = " + wid;
		obj1.exec_dynamic(query1);
		obj1.exec_dynamic(query2);
	}
	if (c_amount < coin_amount) {
		sqlobj obj2;
		wstring query3 = L"update walet set coin_amount = (coin_amount - " + wamount + L") where wallet_id = " + wid + L" AND coin_id = '" + wcoinid + L"'";
		wstring query4 = L"update waltet_main set totalbalance = (totalbalance + " + wbalance + L") where wallet_id = " + wid;
		obj2.exec_dynamic(query3);
		obj2.exec_dynamic(query4);
	}
}

void transfercoin(int sender_walletid, int receiver_walletid, int transferamount) {
	sqlobj transferobj;

	wstring s_wid = to_wstring(sender_walletid);
	wstring r_wid = to_wstring(receiver_walletid);
	wstring wamount = to_wstring(transferamount);
	wstring query1 = L"update waltet_main set totalbalance = (totalbalance + " + wamount + L") where wallet_id = " + r_wid;
	wstring query2 = L"update waltet_main set totalbalance = (totalbalance - " + wamount + L") where wallet_id = " + s_wid;
	transferobj.exec_dynamic(query1);
	transferobj.exec_dynamic(query2);
}

walletdata displaywallet(int wallet_id) {
	wstring w_id = to_wstring(wallet_id);
	wstring query = L"select coin_id, coin_amount from walet where wallet_id = "+w_id;
	sqlobj booj;
	walletdata w2 = booj.showwallet(query);
	return w2;
}

int main()
{
}