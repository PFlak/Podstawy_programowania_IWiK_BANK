#pragma once
#include "Domain.h"

class UserFactory
{
public:
	virtual User CreateUser(
		string password,
		string name,
		string surname,
		string personalCode,
		string mail,
		string phoneNumber
	) = 0;
};