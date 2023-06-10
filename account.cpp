#include "account.h"
Account::Account()
{}

Account::Account(int account_id, string first_name, string last_name)
{
    this->first_name_ = first_name;
    this->last_name_ = last_name;
    this->account_id_ = account_id;

    string accountTitles[] = { "Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund"};

    // Initializing all the Fund objects in the funds vector with the appropriate account titles
    for (int i = 0; i < 8; i++)
    {
        fund_.push_back(Fund(accountTitles[i]));
    }
}

Account::~Account()
{
}

string Account::first_name() const
{
    return first_name_;
}

string Account::last_name() const
{
    return last_name_;
}

int Account::account_id() const
{
    return account_id_;
}

void Account::set_first_name(string first_name)
{
    this->first_name_ = first_name;
}

void Account::set_last_name(string last_name)
{
    this->last_name_ = last_name;
}

void Account::set_account_id(int account_id)
{
    this->account_id_ = account_id;
}

bool Account::Deposit(Transaction& transaction)
{
    bool pass = (fund_[transaction.fund_id()]).AddAmount(transaction.amount());

    if (!pass) // If the transaction failed
    {
        transaction.set_status("(Failed)");
        cerr << "ERROR: Cannot deposit a negative amount into " << first_name_ << " " << last_name_ << " " << (fund_[transaction.fund_id()]).fund_name() << endl;
    }

    (fund_[transaction.fund_id()]).AddFundHistory(transaction); // Adds to fund history
    return pass;
}

bool Account::Withdraw(Transaction& transaction)
{
    bool pass = (fund_[transaction.fund_id()]).SubtractAmount(transaction.amount());

    // If the transaction failed but the account type is fund[0],[1],[2],[3]
    if (!pass && (transaction.amount() > 0) && (transaction.fund_id() == 0 || transaction.fund_id() == 1 || transaction.fund_id() == 2 || transaction.fund_id() == 3))
    {
        
        bool money_markets = (fund_[0].balance() + fund_[1].balance()) >= transaction.amount();
        bool bonds = (fund_[2].balance() + fund_[3].balance()) >= transaction.amount();

        if (money_markets || bonds) // If the accounts can be combined
        {
            pass = true; // Set to true since the transaction is valid in this situation
            int withdraw_amount, withdraw_fund;

            if (transaction.fund_id() >= 0 || transaction.fund_id() <= 3)
            {
                // Sets up variables for a transaction from PMV to MM fund
                if (transaction.fund_id() == 0)
                {
                    withdraw_amount = transaction.amount() - fund_[0].balance();
                    withdraw_fund = 1;
                }
                // Sets up variables for a transaction from MM to PMV fund
                else if (transaction.fund_id() == 1)
                {
                    withdraw_amount = transaction.amount() - fund_[1].balance();
                    withdraw_fund = 0;
                }
                // Sets up variables for a transaction from STB to LTB fund
                else if (transaction.fund_id() == 2)
                {
                    withdraw_amount = transaction.amount() - fund_[2].balance();
                    withdraw_fund = 3;
                }
                // Sets up variables for a transaction from LTB to STB fund
                else
                {
                    withdraw_amount = transaction.amount() - fund_[3].balance();
                    withdraw_fund = 2;
                }

                // Creates a new Transaction object for a transfer between the two mutual accounts
                Transaction withdrawDesired('W', account_id_, withdraw_fund, withdraw_amount, "");

                transaction.set_amount((fund_[transaction.fund_id()]).balance());

                // Subtracting and adding funds to/from the appropriate amounts
                fund_[withdraw_fund].SubtractAmount(withdraw_amount);

                // Adding to the transaction history of each fund
                fund_[withdraw_fund].AddFundHistory(withdrawDesired);

                // Subtracting the full balance from the initial account
                fund_[transaction.fund_id()].SubtractAmount((fund_[transaction.fund_id()]).balance());
            }
        }
    }
    // If the transaction failed
    if (!pass) 
    {
        transaction.set_status("(Failed)");

        if (transaction.transaction_type() != 'T')
        {
            cerr << "ERROR: Not enough funds to withdraw " << transaction.amount() << " from " << first_name_ << " " << last_name_ << " " << (fund_[transaction.fund_id()]).fund_name() << endl;
        }
    }

    (fund_[transaction.fund_id()]).AddFundHistory(transaction); // Adds to fund history does the WHOLE AMOUNT

    return pass;
}

bool Account::Transfer(Transaction& processing, Account*& account)
{
    bool pass = this->Withdraw(processing);

    // If the transaction failed but the account type is fund[0],[1],[2],[3]
    if (pass)
    {
        account->fund_[processing.transfer_fund_id()].AddAmount(processing.amount());
    }
    else // Transaction cannot be completed
    {
        processing.set_status("(Failed)");
        cerr << "ERROR: Not enough funds to withdraw " << processing.amount() << " from " << first_name_ << " " << last_name_ << " " << (fund_[processing.fund_id()]).fund_name() << ". Transferal refused." << endl;
    }

    // Adding to the history of each fund
    (account->fund_[processing.transfer_fund_id()]).AddFundHistory(processing);
    return pass;
}

void Account::PrintFundHistory(const Transaction& processing) const
{
    string fund_name = fund_[processing.fund_id()].fund_name();
    Fund fund;
    for (int i = 0; i < fund_.size(); i++) {
        if (fund_[i].fund_name() == fund_name) {
            fund = fund_[i];
            break;
        }
    }
    cout << "Transaction History for " << last_name_ << " " << first_name_ << " " << fund.fund_name() << ": $" << fund.balance() << endl;
    fund.PrintFundHistory();
}

void Account::PrintHistory() const
{
    cout << "Transaction History for " << last_name_ << " " << first_name_ << " by fund." << endl;
    for (int i = 0; i < fund_.size(); i++) {
        if (!fund_[i].isEmpty())
        {
            cout << fund_[i].fund_name() << ": $" << fund_[i].balance() << endl;
            fund_[i].PrintFundHistory();
        }
    }
}

ostream& operator<<(ostream& stream, const Account& account)
{
    stream << account.last_name_ << " " << account.first_name_ << " Account ID: " << account.account_id_ << endl;

    for (int i = 0; i < (account.fund_).size(); i++)
    {
        stream << "    " << (account.fund_[i]).fund_name() << ": $" << (account.fund_[i]).balance() << endl;
    }
    return stream;
}