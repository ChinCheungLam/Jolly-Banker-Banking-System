#ifndef FUND_H_
#define FUND_H_
#include "transaction.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Fund
{
public:
    Fund();
    Fund(string fund_name);
    ~Fund();

    // Getters and Setters
    int balance() const;
    string fund_name() const;
    void set_balance(int balance);
    void set_fund_name(string fund_name);
    bool isEmpty() const;

    // Class functions
    bool AddAmount(int amount);
    bool SubtractAmount(int amount);
    void AddFundHistory(Transaction transaction);
    void PrintFundHistory() const;

private:
	string fund_name_;
	int balance_ = 0;
	vector<Transaction> transactions_history_;
};
#endif
