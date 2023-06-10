#pragma once
#include "CustomerFactory.h"

User CustomerFactory::CreateUser(
	string password,
	string name,
	string surname,
	string personalCode,
	string mail,
	string phoneNumber)
{
	User user;
	user.password = password;
	user.name = name;
	user.surname = name;
	user.personalCode = personalCode;
	user.mail = mail;
	user.phoneNumber = phoneNumber;
	user.isEmployee = true;
	return user;
}