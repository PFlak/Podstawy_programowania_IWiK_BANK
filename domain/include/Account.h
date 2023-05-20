#using "Currency.h"

public class Account
{
	public class Currency
	{
	private:
		string name;
		float value;
	public:
		string GetName()
		{
			return this->name;
		}
		float GetValue()
		{
			return this->value;
		}
	};
private:
	int id;
	int accountNumber;
	int userId;
	Currency currency;
	int balance;
	string type;
	int interestRate;
public:
	int GetId()
	{
		return this->id;
	}

	int GetAccountNumber()
	{
		return this->accountNumber;
	}

	int GetUserId()
	{
		return this->userId;
	}

	Currency GetCurrency()
	{
		return this->currency;
	}

	int GetBalance()
	{
		return this->balance;
	}

	string GetType()
	{
		return this->type;
	}

	int GetInterestRate()
	{
		return this->InterestRate();
	}
};