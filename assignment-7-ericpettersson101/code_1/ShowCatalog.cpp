#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::ShowCatalog()
{
    root = nullptr;
}

/* Completed functions. DO NOT MODIFY*/
void destroyNode(ShowItem *current)
{
    if (current != nullptr)
    {
        destroyNode(current->left);
        destroyNode(current->right);

        delete current;
        current = nullptr;
    }
}

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::~ShowCatalog()
{
    destroyNode(root);
}

/* Completed functions. DO NOT MODIFY*/
void printShowHelper(ShowItem *m)
{
    if (m != nullptr)
    {
        cout << "Show: " << m->title << " " << m->userRating << endl;
        printShowHelper(m->left);
        printShowHelper(m->right);
    }
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::printShowCatalog()
{
    if (root == nullptr)
    {
        cout << "Tree is Empty. Cannot print" << endl;
        return;
    }
    printShowHelper(root);
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *getShowHelper(ShowItem *current, string title)
{
    if (current == NULL)
        return NULL;

    if (current->title == title)
        return current;

    if (current->title > title)
        return getShowHelper(current->left, title);

    return getShowHelper(current->right, title);
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::getShow(string title)
{
    ShowItem *node = getShowHelper(root, title);
    if (node != nullptr)
    {
        cout << "Show Info:" << endl;
        cout << "==================" << endl;
        cout << "Title :" << node->title << endl;
        cout << "Year :" << node->year << endl;
        cout << "Show Rating :" << node->showRating << endl;
        cout << "User Rating :" << node->userRating << endl;
        return;
    }

    cout << "Show not found." << endl;
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *addNodeHelper(ShowItem *current, ShowItem *newNode)
{
    if (current == nullptr)
    {
        return newNode;
    }

    if (current->title > newNode->title)
    {
        current->left = addNodeHelper(current->left, newNode);
    }
    else
    {
        current->right = addNodeHelper(current->right, newNode);
    }

    return current;
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating)
{
    if (root == nullptr)
    {
        root = new ShowItem(title, year, showRating, userRating);
        return;
    }

    root = addNodeHelper(root, new ShowItem(title, year, showRating, userRating));
}
ShowItem* findMinShowItem(ShowItem* root) {
    while (root->left != NULL) root = root->left;
    return root;
}
ShowItem* deleteShowItemHelper(ShowItem* node, string title) {
    if (node == nullptr) return nullptr; // Base case: node not found

    // Navigate down the tree and call recursively for the matching subtree
    if (title < node->title) {
        node->left = deleteShowItemHelper(node->left, title);
    } else if (title > node->title) {
        node->right = deleteShowItemHelper(node->right, title);
    } else {
        // Node with only one child or no child
        if (node->left == nullptr) {
            ShowItem* temp = node->right;
            delete node; 
            return temp; // Return the new link for parent node
        } else if (node->right == nullptr) {
            ShowItem* temp = node->left;
            delete node; 
            return temp; // Return the new link for parent node
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        ShowItem* temp = findMinShowItem(node->right);
        
        // Replace node's data with that of its inorder successor
        node->title = temp->title;
        node->year = temp->year;
        node->showRating = temp->showRating;
        node->userRating = temp->userRating;

        // Delete the inorder successor
        node->right = deleteShowItemHelper(node->right, temp->title);
    }
    return node; // Return the (possibly updated) node pointer to the caller
}

void ShowCatalog::removeShow(string title) {
    root = deleteShowItemHelper(root, title);
}


/* TODO */
void ShowCatalog::rightRotate(string title) {
    if (!root) return; // Check if the tree is empty

    ShowItem *parent = nullptr;
    ShowItem *node = root;
    // Find the node and its parent
    while (node && node->title != title) {
        parent = node;
        if (title < node->title) node = node->left;
        else node = node->right;
    }

    if (!node || !node->left) return; // No rotation possible

    ShowItem *leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;

    // Update parent
    if (!parent) root = leftChild;
    else if (parent->left == node) parent->left = leftChild;
    else parent->right = leftChild;
}



/* TODO */
void ShowCatalog::leftRotate(string title) {
    if (!root) return; // Check if the tree is empty

    ShowItem *parent = nullptr;
    ShowItem *node = root;
    // Find the node and its parent
    while (node && node->title != title) {
        parent = node;
        if (title < node->title) node = node->left;
        else node = node->right;
    }

    if (!node || !node->right) return; // No rotation possible

    ShowItem *rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;

    // Update parent
    if (!parent) root = rightChild;
    else if (parent->left == node) parent->left = rightChild;
    else parent->right = rightChild;
}
