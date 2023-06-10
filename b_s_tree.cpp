#include "b_s_tree.h"
BSTree::BSTree():root_(nullptr), size_(0)
{
}

BSTree::BSTree(const BSTree& tree):root_(nullptr), size_(0)
{
   
}

BSTree::~BSTree()
{
    Empty();
}

bool BSTree::Insert(Account* account)
{
    // Make inserting the root if the Tree is empty
    if (root_ == nullptr)
    {
        root_ = new Node{ account, nullptr, nullptr };
        size_++;
        return true;
    }
    return RecInsert(root_, account);
}

bool BSTree::Retrieve(const int& account_id, Account*& account) const
{
    Node* current = root_;

    while (current != nullptr)
    {
        if (account_id == current->p_acct->account_id())
        {
            account = current->p_acct;
            return true;
        }
        else if (account_id < current->p_acct->account_id())
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return false;
}

bool BSTree::Delete(const int& account_id, Account*& account)
{
    Node* parent = nullptr;
    Node* current = root_;

    // Look for the node with the given account ID
    while (current != nullptr && current->p_acct->account_id() != account_id)
    {
        parent = current;

        if (account_id < current->p_acct->account_id())
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    // If the node is not found, return false
    if (current == nullptr)
    {
        return false;
    }

    // Save a pointer to the node's Account object
    account = current->p_acct;

    // Case 1: The node has no children
    if (current->left == nullptr && current->right == nullptr)
    {
        // If the node is the root
        if (parent == nullptr)
        {
            root_ = nullptr;
        }
        // If the node is a left child
        else if (current == parent->left)
        {
            parent->left = nullptr;
        }
        // If the node is a right child
        else
        {
            parent->right = nullptr;
        }

        // Delete the node
        delete current;
    }
    // Case 2: The node has one child
    else if (current->left == nullptr || current->right == nullptr)
    {
        // Save a pointer to the node's child
        Node* child = current->left == nullptr ? current->right : current->left;

        // If the node is the root
        if (parent == nullptr)
        {
            root_ = child;
        }
        // If the node is a left child
        else if (current == parent->left)
        {
            parent->left = child;
        }
        // If the node is a right child
        else
        {
            parent->right = child;
        }

        // Delete the node
        delete current;
    }
    // Case 3: The node has two children
    else
    {
        Node* successor = current->right;
        Node* successor_parent = nullptr;

        // Find the leftmost child of the node's right subtree
        while (successor->left != nullptr)
        {
            successor_parent = successor;
            successor = successor->left;
        }

        // If the successor is not the node's immediate right child, rearrange the tree
        if (successor_parent != nullptr)
        {
            successor_parent->left = successor->right;
            successor->right = current->right;
        }

        // Update the node's parent to point to the successor
        if (parent == nullptr)
        {
            root_ = successor;
        }
        else if (current == parent->left)
        {
            parent->left = successor;
        }
        else
        {
            parent->right = successor;
        }

        // Update the successor's left child
        successor->left = current->left;

        // Delete the node
        delete current;
    }

    size_--;

    return true;
}

void BSTree::Empty()
{
    if (root_ == nullptr) return;
    queue<Node*> node_queue;
    node_queue.push(root_);

    while (!node_queue.empty()) {
        Node* curr_node = node_queue.front();
        node_queue.pop();

        if (curr_node->left != nullptr) node_queue.push(curr_node->left);
        if (curr_node->right != nullptr) node_queue.push(curr_node->right);

        delete curr_node->p_acct;
        delete curr_node;
    }

    root_ = nullptr;
    size_ = 0;
}

bool BSTree::RecInsert(Node* node, Account* account)
{
    // If the inserting account ID is greater than that of the current Node
    if (node == nullptr)
    {
        node = new Node{ account, nullptr, nullptr };
        size_++;
        return true;
    }

    if (account->account_id() == node->p_acct->account_id())
    {
        return false;
    }
    else if (account->account_id() < node->p_acct->account_id())
    {
        if (node->left == nullptr)
        {
            node->left = new Node{ account, nullptr, nullptr };
            size_++;
            return true;
        }
        else
        {
            return RecInsert(node->left, account);
        }
    }
    else
    {
        if (node->right == nullptr)
        {
            node->right = new Node{ account, nullptr, nullptr };
            size_++;
            return true;
        }
        else
        {
            return RecInsert(node->right, account);
        }
    }
}

BSTree& BSTree::operator=(const BSTree& tree)
{
    if (this != &tree) {
        Empty();
        size_ = tree.size_;

        if (tree.root_) {
            root_ = new Node{tree.root_->p_acct, nullptr, nullptr };
            RecInsert(root_, tree.root_->left->p_acct);
            RecInsert(root_, tree.root_->right->p_acct);
        }
    }
    return *this;
}

void BSTree::Display() const
{
    recursive_display(root_);
}

int BSTree::Size() const
{
    return size_;
}

void BSTree::recursive_display(Node* node) const
{
    if (node == nullptr)
    {
        return;
    }
    // If the current Node has Nodes for both both branches
    if (node->left != NULL && node->right != NULL)
    {
        recursive_display(node->right);
        cout << *(node->p_acct) << endl;
        recursive_display(node->left);
    }
    // If the current Node only has a Node for the left branch
    else if (node->left != NULL)
    {
        cout << *(node->p_acct) << endl;
        recursive_display(node->left);
    }
    // If the current Node only has a Node for the right branch
    else if (node->right != NULL)
    {
        cout << *(node->p_acct) << endl;
        recursive_display(node->right);
    }
    // If the root is the only Node in the tree
    else
    {
        cout << *(node->p_acct) << endl;
    }
}