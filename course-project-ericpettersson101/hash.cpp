// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>
#include <vector>//added for setup
using namespace std;

// Function to create a new node
node* HashTable::createNode(string restaurantName, node* next)
{
    node* newNode = new node{restaurantName, PriorityQ(50), next};//instructor said to use
    return newNode;
}


// Constructor for the HashTable
HashTable::HashTable(int bsize)
{
    this->tableSize = bsize;
    table = new node*[tableSize];
    numCollision = 0;  // Initialize collision count

    for(int i = 0; i < tableSize; i++)
        table[i] = nullptr;
}


// Destructor for the HashTable
HashTable::~HashTable()
{
    for (int i = 0; i < tableSize; i++) {
        node* entry = table[i];
        while (entry != nullptr) {
            node* prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
    delete[] table;
}

// Display the contents of the hash table
void HashTable::displayTable()
{
    for (int i = 0; i < tableSize; i++) {
        node* entry = table[i];
        if (entry == nullptr) continue;
        cout << "Bucket " << i << ": ";
        while (entry != nullptr) {
            cout << entry->restaurantName << " -> ";
            entry = entry->next;
        }
        cout << "NULL" << endl;
    }
}

// Hash function to calculate hash index
unsigned int HashTable::hashFunction(string restaurantName)
{
    unsigned int hashValue = 0;
    for (char c : restaurantName)
        hashValue = hashValue * 31 + c;  // Simple polynomial rolling hash function
    return hashValue % tableSize;
}

// Search for an item by its name
node* HashTable::searchItem(string restaurantName)
{
    int bucket = hashFunction(restaurantName);
    node* entry = table[bucket];
    while (entry != nullptr) {
        if (entry->restaurantName == restaurantName)
            return entry;
        entry = entry->next;
    }
    return nullptr;
}

// Insert an item into the hash table
void HashTable::insertItem(ReviewInfo restaurant)
{
    int bucket = hashFunction(restaurant.restaurantName);
    node* existingNode = searchItem(restaurant.restaurantName);
    if (existingNode != nullptr) {
        // Add the review to the existing node's priority queue
        existingNode->pq.insertElement(restaurant);
    } else {
        // No entry found, create a new node and add to the bucket
        node* newNode = createNode(restaurant.restaurantName, table[bucket]);
        newNode->pq.insertElement(restaurant); // Use PriorityQ's method to insert the review
        if(table[bucket]) { numCollision++;}
        table[bucket] = newNode;
    }
}





void HashTable::setup(string fname) {
    ifstream file(fname);
    if (!file.is_open()) {
        cout << "Failed to open file: " << fname << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string restaurantName, review, customerName, part;
        int time;

        // Get restaurant name
        getline(ss, restaurantName, ';');

        // Get review
        getline(ss, review, ';');

        // Get customer name
        getline(ss, customerName, ';');

        // Get time as string and convert to int
        getline(ss, part, ';');
        time = stoi(part);

        ReviewInfo newReview{restaurantName, review, customerName, time};
        insertItem(newReview);
    }
    file.close();
}