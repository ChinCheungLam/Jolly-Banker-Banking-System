#include "jolly_banker.h"

JollyBanker::JollyBanker()
{
}

JollyBanker::JollyBanker(string file_name)
{
    ReadFile(file_name);
}

JollyBanker::~JollyBanker()
{
}

bool JollyBanker::ReadFile(string file_name)
{
    ifstream in_file(file_name);
    if (!in_file)
    {
        cout << "Invalid input file" << endl;
        return false;
    }

    // Variables that will be used as arguments to create transactions
    string readLine, firstName, lastName;
    char transactionType;
    int account_id, fund_id, amount, transfer_account_id, transfer_fund_id;

    while (!in_file.eof())
    {
        getline(in_file, readLine); // Reads the line and stores it in a string variable
        istringstream parseLine(readLine); // Parses the string and splits it up after spaces
        parseLine >> transactionType; // Stores the transaction type

        // If the transaction wants to open and account
        if (toupper(transactionType) == 'O')
        {
            parseLine >> account_id >> lastName >> firstName;

            transaction_list_.push(Transaction(transactionType, account_id, lastName, firstName));
        }
        // If the transaction wants to make a deposit or a withdrawal
        else if (toupper(transactionType) == 'D' || transactionType == 'W')
        {
            parseLine >> account_id >> fund_id >> amount;

            transaction_list_.push(Transaction(transactionType, account_id, fund_id, amount, ""));
        }
        // If the transaction wants to make a transfer
        else if (toupper(transactionType) == 'T')
        {
            parseLine >> account_id >> fund_id  >> transfer_account_id >> transfer_fund_id >> amount;
            transaction_list_.push(Transaction(transactionType, account_id, fund_id, transfer_account_id, transfer_fund_id, amount, ""));
        }
        // If the transaction wants to display account fund history
        else if (toupper(transactionType) == 'F')
        {
            parseLine >> account_id >> fund_id;
            transaction_list_.push(Transaction(transactionType, account_id, fund_id));
        }
        // If the transaction wants to display account history
        else if (toupper(transactionType) == 'A')
        {
            parseLine >> account_id;
            transaction_list_.push(Transaction(transactionType, account_id));
        }
        // If the transaction type is invalid
        else
        {
            cerr << "ERROR: Transaction type: '" << transactionType << "' is invalid" << endl;
        }
    }
    in_file.close();
    return false;
}

bool JollyBanker::ProcessQueue()
{
	while (!transaction_list_.empty())
	{
        bool isOpen; // Will hold a boolean value depending on whether an account is already open or not
        Account* current_account;

        Transaction processing = transaction_list_.front(); // Gets the next Transaction in the queue

        // Opening an account
        if (processing.transaction_type() == 'O')
        {
            // Checks to see if the account ID is a valid value
            if (processing.account_id() >= 100 && processing.account_id() <= 9999)
            {
                isOpen = account_list_.Retrieve(processing.account_id(), current_account);

                // If the account is not already open create a new Account object and add it to the BSTree
                if (!isOpen)
                {
                    Account* creating = new Account(processing.account_id(), processing.last_name(), processing.first_name());
                    account_list_.Insert(creating);
                }
                // Else the account is already open
                else
                {
                    cerr << "ERROR: Account " << processing.account_id() << " is already open. Transaction refused." << endl;
                }
            }
            // Account ID is invalid
            else
            {
                cerr << "ERROR: Invalid account number. Must be between 100-9999." << endl;
            }
        }
        // Making a deposit
        else if (processing.transaction_type() == 'D')
        {
            // Checks to see if the account ID/account type is a valid value
            if (processing.account_id() >= 100 && processing.account_id() <= 9999)
            {
                isOpen = account_list_.Retrieve(processing.account_id(), current_account);

                // If the account is already open attempt to make the deposit
                if (isOpen)
                {
                    current_account->Deposit(processing);
                }
                // Else the account is not found
                else
                {
                    cerr << "ERROR: Account " << processing.account_id() << " not found. Deposit refused." << endl;
                }
            }
            // Account ID is invalid
            else
            {
                cerr << "ERROR: Invalid account number. Deposit refused." << endl;
            }
        }
        // Making a withdrawal
        else if (processing.transaction_type() == 'W')
        {
            // Checks to see if the account ID is a valid value
            if (processing.account_id() >= 100 && processing.account_id() <= 9999)
            {
                isOpen = account_list_.Retrieve(processing.account_id(), current_account);

                // If the account is already open attempt to make the withdrawal
                if (isOpen)
                {
                    current_account->Withdraw(processing);
                }
                // Else the account is not found
                else
                {
                    cerr << "ERROR: Account " << processing.account_id() << " not found. Withdrawal refused." << endl;
                }
            }
            // Account ID is invalid
            else
            {
                cerr << "ERROR: Invalid account number. Withdrawal refused." << endl;
            }
        }
        // Making a transfer between accounts
        else if (processing.transaction_type() == 'T')
        {
            // Checks to see if the account and receiving account information is valid
            if ((processing.account_id() >= 100 && processing.account_id() <= 9999) && (processing.transfer_account_id() >= 100 && processing.transfer_account_id() <= 9999))
            {
                Account* receiving;

                isOpen = account_list_.Retrieve(processing.account_id(), current_account);
                bool receiving_is_open = account_list_.Retrieve(processing.transfer_account_id(), receiving);

                // If both accounts are open attempt to make the transfer
                if (isOpen && receiving_is_open)
                {
                    current_account->Transfer(processing, receiving);
                }
                // If the initial account isn't found
                else if (!isOpen)
                {
                    cerr << "ERROR: Account " << processing.account_id() << " not found. Transfer refused." << endl;
                }
                // If the receiving account isn't found
                else if (!receiving_is_open)
                {
                    cerr << "ERROR: Account " << processing.transfer_account_id() << " not found. Transfer refused." << endl;
                }
            }
            // If the account and/or receiving account information is invalid
            else
            {
                cerr << "ERROR: Invalid account number/s. Transfer refused." << endl;
            }
        }
        // Displaying account fund information
        else if (processing.transaction_type() == 'F')
        {
            isOpen = account_list_.Retrieve(processing.account_id(), current_account);

            // If the account is already open, attempt to print fund history
            if (isOpen)
            {
                if (processing.fund_id() >= 0 && processing.fund_id() <= 8)
                {
                    current_account->PrintFundHistory(processing);
                }
                else
                {
                    cerr << "ERROR: Invalid Fund number." << processing.fund_id() << endl;
                }
            }
            // If the account is not found
            else
            {
                cerr << "ERROR: Account " << processing.account_id() << " not found. Cannot display history." << endl;
            }
        }
        // Displaying account information
        else if (processing.transaction_type() == 'A')
        {
            isOpen = account_list_.Retrieve(processing.account_id(), current_account);

            // If the account is already open, attempt to print transaction history
            if (isOpen)
            {
                current_account->PrintHistory();
            }
            // If the account is not found
            else
            {
                cerr << "ERROR: Account " << processing.account_id() << " not found. Cannot display history." << endl;
            }
        }

        // Remove completed transaction from queue
        transaction_list_.pop();
    }

    return true;
}

void JollyBanker::Display()
{
	cout << endl;
	cout << "FINAL BALANCES:" << endl;
	account_list_.Display();
}
