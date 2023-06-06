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