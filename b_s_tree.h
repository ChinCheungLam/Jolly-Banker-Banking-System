#ifndef B_S_TREE_H_
#define B_S_TREE_H_
#include<queue>
#include"account.h"

class BSTree
{
	
public:
	BSTree();
	BSTree(const BSTree& tree);
	~BSTree();

	bool Insert(Account* account);

	// retrieve object, first parameter is the ID of the account 
	// second parameter holds pointer to found object, NULL if not found 
	bool Retrieve(const int& account_id, Account*& account) const;

	// Delete object, first parameter is the ID of the account 
	// second parameter holds pointer to found object, NULL if not found 
	bool Delete(const int& account_id, Account*& account);
	void Empty();

	BSTree& operator=(const BSTree& tree);


	// displays the contents of a tree to cout;  you could also overload operator<<
	void Display() const;
	int Size() const;
private:
	struct Node
	{
		Account* p_acct;
		Node* right;
		Node* left;
	};
	Node* root_;
	int size_;
	void recursive_display(Node* node) const;
	bool RecInsert(Node* node, Account* account);
};
#endif
