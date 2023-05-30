#PRAGMA ONCE
#include <cstdlib>
#include "User.h"

public class Employee : User
{
private:
	string rank;
public:
	Employee(int id,
		string login,
		string password,
		string name,
		string surname,
		string personalCode,
		string mail,
		string phoneNumber)
	{
		this->User(id, login, password, name, surname, personalCode, mail, phoneNumber);
	}
	string GetRank()
	{
		return this->rank;
	}
	//TO DO: coœ ciekawszego temu pracownikowi banku daæ

};