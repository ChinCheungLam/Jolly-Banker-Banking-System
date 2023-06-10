#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include<string>
#include <iostream>
#include <vector>

using namespace std;
class Transaction
{
	
public:
	Transaction();
	Transaction(char transaction_type, int account_id, int fund_id, int amount, string status);
	Transaction(char transaction_type, int account_id, int fund_id, int transfer_account_id, int transfer_fund_id, int amount, string status);
	Transaction(char transaction_type, int account_id);
	Transaction(char transaction_type, int account_id, int fund_id);
	Transaction(char transaction_type, int account_id, string last_name, string first_name);
	~Transaction();


	char transaction_type() const;
	string first_name() const;
	string last_name() const;
	string status() const;
	int account_id() const;
	int fund_id() const;
	int transfer_account_id() const;
	int transfer_fund_id() const;
	int amount() const;

	// Setters
	void set_transaction_type(char transaction_type);
	void set_first_name(string first_name);
	void set_last_name(string last_name);
	void set_status(string status);
	void set_account_id(int account_id);
	void set_fund_id(int fund_id);
	void set_transfer_account_id(int transfer_account_id);
	void set_transfer_fund_id(int transfer_fund_id);
	void set_amount(int amount);

	friend ostream& operator<<(ostream& stream, const Transaction& trans);
private:
	char transaction_type_;
	string first_name_, last_name_, status_;
	int account_id_, transfer_account_id_, amount_, fund_id_, transfer_fund_id_;
};
#endif
