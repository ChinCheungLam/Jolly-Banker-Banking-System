#include "transaction.h"

Transaction::Transaction()
{
}

Transaction::Transaction(char transaction_type, int account_id, int fund_id, int amount,string status)
{
	transaction_type_ = transaction_type;
	account_id_ = account_id;
	fund_id_ = fund_id;
	amount_ = amount;
	status_ = status;
}

Transaction::Transaction(char transaction_type, int account_id, int fund_id, int transfer_account_id, int transfer_fund_id, int amount, string status)
{
	transaction_type_ = transaction_type;
	account_id_ = account_id;
	fund_id_ = fund_id;
	transfer_account_id_ = transfer_account_id;
	transfer_fund_id_ = transfer_fund_id;
	amount_ = amount;
	status_ = status;
}

Transaction::Transaction(char transaction_type, int account_id)
{
	transaction_type_ = transaction_type;
	account_id_ = account_id;
}

Transaction::Transaction(char transaction_type, int account_id, int fund_id)
{
	transaction_type_ = transaction_type;
	account_id_ = account_id;
	fund_id_ = fund_id;
}

Transaction::Transaction(char transaction_type, int account_id, string last_name, string first_name)
{
	transaction_type_ = transaction_type;
	account_id_ = account_id;
	last_name_ = last_name;
	first_name_ = first_name;
}

Transaction::~Transaction()
{
}

char Transaction::transaction_type() const
{
	return transaction_type_;
}

string Transaction::first_name() const
{
	return first_name_;
}

string Transaction::last_name() const
{
	return last_name_;
}

string Transaction::status() const
{
	return status_;
}

int Transaction::account_id() const
{
	return account_id_;
}


int Transaction::fund_id() const
{
	return fund_id_;
}

int Transaction::transfer_account_id() const
{
	return transfer_account_id_;
}

int Transaction::transfer_fund_id() const
{
	return transfer_fund_id_;
}

int Transaction::amount() const
{
	return amount_;
}

void Transaction::set_transaction_type(char transaction_type)
{
	this->transaction_type_ = transaction_type;
}

void Transaction::set_first_name(string first_name)
{
	this->first_name_ = first_name;
}

void Transaction::set_last_name(string last_name)
{
	this->last_name_ = last_name;
}

void Transaction::set_status(string status)
{
	this->status_ = status;
}

void Transaction::set_account_id(int account_id)
{
	this->account_id_ = account_id;
}

void Transaction::set_fund_id(int fund_id)
{
	this->fund_id_ = fund_id;
}

void Transaction::set_transfer_account_id(int transfer_account_id)
{
	this->transfer_account_id_ = transfer_account_id;
}

void Transaction::set_transfer_fund_id(int transfer_fund_id)
{
	this->transfer_fund_id_ = transfer_fund_id;
}

void Transaction::set_amount(int amount)
{
	this->amount_ = amount;
}

ostream& operator<<(ostream& stream, const Transaction& trans)
{
	if (trans.transaction_type() == 'O')
	{
		stream << trans.transaction_type() << trans.account_id() << " " << trans.last_name() << " " << trans.first_name();
	}
	else if (trans.transaction_type() == 'D' || trans.transaction_type() == 'W')
	{
		stream << trans.transaction_type() << " " << trans.account_id() << " " << trans.fund_id() << " " << trans.amount() << " " << trans.status();
	}
	else if (trans.transaction_type() == 'T')
	{
		stream << trans.transaction_type() << " " << trans.account_id() << " " << trans.fund_id() <<  " " << trans.transfer_account_id() << " " << trans.transfer_fund_id() << " " << trans.amount() << " " << trans.status();
	}
	else if (trans.transaction_type() == 'F')
	{
		stream << trans.transaction_type() << " " << trans.account_id() << " " << trans.fund_id();
	}
	else if (trans.transaction_type() == 'A')
	{
		stream << trans.transaction_type() << " " << trans.account_id();
	}
	return stream;
}