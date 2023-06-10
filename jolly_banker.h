#ifndef JOLLY_BANKER_H_
#define JOLLY_BANKER_H_
#include"b_s_tree.h"
#include"transaction.h"
#include<iostream>
#include<string>
#include <fstream>
#include<sstream>
#include<vector>
#include<queue>

using namespace std;

class JollyBanker
{
public:
	JollyBanker();
	JollyBanker(string file_name);
	~JollyBanker();

	bool ReadFile(string file_name);
	bool ProcessQueue();
	void Display();
private:
	queue<Transaction> transaction_list_;
	BSTree account_list_;
};
#endif
