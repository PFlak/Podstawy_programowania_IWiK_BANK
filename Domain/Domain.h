#pragma once
#include <string>

using namespace std;

struct Account
{
	int id;
	int accountNumber;
	int userId;
	string currency;
	int balance;
	string type;
	int interestRate;
};

struct User
{
	int id;
	string login;
	string password;
	string name;
	string surname;
	string personalCode;
	string mail;
	string phoneNumber;
	bool isEmployee;
};

struct Transfer
{
	int id;
	string action;
	int senderaccountid;
	int recipientaccountid;
	string currency;
	int amout;
	string header;
	string info;
	string time;
};	

struct Transaction
{
	int id;
	string action;
	int accountid;
	string currency;
	int amount;
	string time;
};
