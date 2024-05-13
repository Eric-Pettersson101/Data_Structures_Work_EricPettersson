#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

ShowCatalog::ShowCatalog() {
    root = nullptr;  // Assuming you have a ShowItem* root in your ShowCatalog class
}

void deleteTree(ShowItem* node) {  // Helper function for destructor
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

ShowCatalog::~ShowCatalog() {
    deleteTree(root);
}

void printPreOrder(ShowItem* node) {
    if (node == nullptr) return;
    cout << "Show: " << node->title << " " << node->userRating << endl;
    printPreOrder(node->left);
    printPreOrder(node->right);
}

void ShowCatalog::printShowCatalog() {
    if (root != nullptr) {
        printPreOrder(root);

    } else {
        cout << "Tree is Empty. Cannot print" << endl;

    }
}

void ShowCatalog::getShow(string title) {
    ShowItem* current = root;
    while (current != nullptr) {
        if (title == current->title) {
            cout << "Show Info:" << endl;
            cout << "==================" << endl;
            cout << "Title :" << current->title << endl;
            cout << "Year :" << current->year << endl;
            cout << "Show Rating :" << current->showRating << endl;
            cout << "User Rating :" << current->userRating << endl;//expected 
            return;
        } else if (title < current->title) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    cout << "Show not found." << endl;
}


void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating) {
    ShowItem* newItem = new ShowItem(title, year, showRating, userRating);
    if (root == nullptr) {
        root = newItem;
    } else {
        ShowItem* current = root;
        while (true) {
            if (title < current->title) {
                if (current->left == nullptr) {
                    current->left = newItem;
                    break;
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = newItem;
                    break;
                }
                current = current->right;
            }
        }
    }
}


void printLeaves(ShowItem* node) {
    if (node == nullptr) return;
    if (node->left == nullptr && node->right == nullptr) {
        cout << node->title << endl;
    } else {
        printLeaves(node->left);
        printLeaves(node->right);
    }
}

void ShowCatalog::printLeafNodes() {
    printLeaves(root);
}


void searchTitles(ShowItem* node, char titleChar) {
    if (node == nullptr) return;
    if (node->title[0] == titleChar) {
        cout << node->title << "("  << node->year << ") "<< node->userRating << endl;
    }
    searchTitles(node->left, titleChar);
    searchTitles(node->right, titleChar);
}

void ShowCatalog::searchShows(char titleChar) {
    cout << "Shows that starts with " << titleChar << ":"<< endl;
    searchTitles(root, titleChar);
}

void countRatings(ShowItem* node, int &count, string rating) {
    if (node == nullptr) return;
    if (node->showRating == rating) count++;
    countRatings(node->left, count, rating);
    countRatings(node->right, count, rating);
}
void ShowCatalog::displayNumShowRating(int &count, string showRating) {
    count = 0; // Initialize count to zero before counting
    countRatings(root, count, showRating);//calls a method that will be called resusivly this extra method maxs intalizing value simplier
}
