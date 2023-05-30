#PRAGMA ONCE
#include <cstdlib>


public class User
{
private:
	int id;
	string login;
	string password;
	string name;
	string surname;
	string personalCode;
	string mail;
	string phoneNumber;
public:
	User(int id,
		string login,
		string password,
		string name,
		string surname,
		string personalCode,
		string mail,
		string phoneNumber)
	{
		this->id = id;
		this->login = login;
		this->password = password;
		this->name = name;
		this->surname = surname;
		this->personalCode = personalCode;
		this->mail = mail;
		this->phoneNumber = phoneNumber;
	}

	int GetId() 
	{
		return this->id;
	}

	string GetLogin() 
	{
		return this->login;
	}

	string GetName()
	{
		return this->name;
	}

	string GetSurname()
	{
		return this->surname;
	}

	string GetPersonalCode()
	{
		return this->personalCode;
	}

	string GetMail()
	{
		return this->mail;
	}

	string GetPhoneNumber()
	{
		return this->phoneNumber;
	}

	bool Login(string password)
	{
		return password == this->password;
	}
};