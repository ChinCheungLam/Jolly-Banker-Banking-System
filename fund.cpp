#include "fund.h"
Fund::Fund()
{
	balance_ = 0;
}

Fund::Fund(string fund_name):fund_name_(fund_name), balance_(0)
{
}

Fund::~Fund()
{
}

int Fund::balance() const
{
	return balance_;
}

string Fund::fund_name() const
{
	return fund_name_;
}

void Fund::set_balance(int balance)
{
	this->balance_ = balance;
}

void Fund::set_fund_name(string fund_name)
{
	this->fund_name_ = fund_name;
}

bool Fund::isEmpty() const
{
	if (transactions_history_.size() > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Fund::AddAmount(int amount)
{
	if (amount < 0)
	{
		return false;
	}

	balance_ += amount;
	return true;
}

bool Fund::SubtractAmount(int amount)
{
	if (amount < 0 || amount > balance_)
	{
		return false;
	}

	balance_ -= amount;
	return true;
}

void Fund::AddFundHistory(Transaction transaction)
{
	transactions_history_.push_back(transaction);
}

void Fund::PrintFundHistory() const
{
	for (int i = 0; i < transactions_history_.size(); i++)
	{
		cout << "  " << transactions_history_[i] << endl;
	}
}