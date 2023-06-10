#pragma once
#include "Domain.h"
#include "UserFactory.h"

class CustomerFactory : public UserFactory
{
public:
	User CreateUser(
		string password,
		string name,
		string surname,
		string personalCode,
		string mail,
		string phoneNumber
	);
};