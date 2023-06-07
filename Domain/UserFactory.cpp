#pragma once
#include "UserFactory.h"

User UserFactory::CreateUser(string login,
	string password,
	string name,
	string surname,
	string personalCode,
	string mail,
	string phoneNumber)
{
	User user;
	user.login = login;
	user.password = password;
	user.name = name;
	user.surname = name;
	user.personalCode = personalCode;
	user.mail = mail;
	user.phoneNumber = phoneNumber;
	user.isEmployee = false;
	return user;
}