#include<iostream>
#include<string>
#include"account.h"
#include"b_s_tree.h"
#include"jolly_banker.h"
#include"transaction.h"
#include"fund.h"
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    JollyBanker bank(argv[1]);
    if (!bank.ProcessQueue())
    {
        cerr << "Error processing transactions." << endl;
        return 1;
    }

    bank.Display();

    return 0;
}