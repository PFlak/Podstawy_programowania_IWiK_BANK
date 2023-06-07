#pragma once
#include "Domain.h"

class UserFactory
{
public:
	virtual User CreateUser(string login,
	string password,
	string name,
	string surname,
	string personalCode,
	string mail,
	string phoneNumber
	);
};