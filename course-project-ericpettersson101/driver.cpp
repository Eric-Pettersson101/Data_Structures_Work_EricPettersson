#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>//added




using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    HashTable ht(tableSize);

    int ch = 0;
    bool isBuilt = false;
    
while (ch != 8)
    {
        displayMenu();
        cout << "Enter your choice >> ";
        string choice;
        getline(cin, choice);
        ch = stoi(choice);

        switch (ch)
        {
            case 1:
                if (!isBuilt) {
                    ht.setup(fname);
                    isBuilt = true;
                    cout << "Data structure built successfully." << endl;
                } else {
                    cout << "Data structure has already been built." << endl;
                }
                break;
            
            case 2:
                {
                    string restaurantName, review, customer, stringTime;
                    cout << "Enter restaurant name: ";
                    getline(cin, restaurantName);
                    cout << "Enter review: ";
                    getline(cin, review);
                    cout << "Enter customer name: ";
                    getline(cin, customer);
                    cout << "Enter time (integer): ";
                    getline(cin, stringTime);

                    ReviewInfo newReview {restaurantName, review, customer, stoi(stringTime)};//stoi used to deal with no instace of getline for int
                    ht.insertItem(newReview);
                    cout << "Review added successfully." << endl;
                }
                break;
            case 3:
                {
                    string restaurantName;
                    cout << "Enter restaurant name to retrieve the most recent review: ";
                    getline(cin, restaurantName);
                    node* foundNode = ht.searchItem(restaurantName);
                    if (foundNode) {
                        foundNode->pq.peek();
                    } else {
                        cout << "Restaurant not found." << endl;
                    }
                }
                break;
            case 4:
                {
                    string restaurantName;
                    cout << "Enter restaurant name to pop the most recent review: ";
                    getline(cin, restaurantName);
                    node* foundNode = ht.searchItem(restaurantName);
                    if (foundNode && !foundNode->pq.isEmpty()) {
                        foundNode->pq.pop();
                        cout << "Most recent review popped." << endl;
                    } else {
                        cout << "No reviews available or restaurant not found." << endl;
                    }
                }
                break;
            case 5:
                {
                    string restaurantName;
                    cout << "Enter restaurant name to print reviews: ";
                    getline(cin, restaurantName);
                    node* foundNode = ht.searchItem(restaurantName);
                    if (foundNode) {
                        foundNode->pq.print();
                    } else {
                        cout << "Restaurant not found." << endl;
                    }
                }
                break;
            case 6:
                {
                    int collisions = ht.getNumCollision();
                    cout << "Number of collisions: " << collisions << endl;
                }
                break;
            case 7:
                ht.displayTable();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
}
