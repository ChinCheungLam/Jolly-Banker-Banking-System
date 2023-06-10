#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include "transaction.h"
#include"fund.h"
#include<iostream>
#include <string>
#include <vector>

using namespace std;

class Account
{
	
public:
	Account();
	Account(int account_id, string first_name, string last_name);
	~Account();

	// Getters and Setters
	string first_name() const;
	string last_name() const;
	int account_id() const;
	void set_first_name(string first_name);
	void set_last_name(string last_name);
	void set_account_id(int account_id);

	// Class functions
	bool Deposit(Transaction& transaction);
	bool Withdraw(Transaction& transaction);
	bool Transfer(Transaction& transaction, Account*& account);
	void PrintFundHistory(const Transaction& transaction) const;
	void PrintHistory() const;

	friend ostream& operator<<(ostream& stream, const Account& acc);

private:
	string first_name_, last_name_;
	int account_id_;
	vector<Fund> fund_;
};
#endif
