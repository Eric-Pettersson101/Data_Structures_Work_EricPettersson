#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "../code_1/browserHistory.hpp"
using namespace std;

void displayMenu();
int getOption();
string getInput();

int main(int argc, char* argv[]) {

    // DO NOT MODIFY THIS.
    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }
    // DO NOT MODIFY ABOVE.
    //setup
    int id; bool running = true;string url, prevUrl, owner; BrowserHistory history;
   
    //Run loop
    while(running) {
        displayMenu();
        //switch statement for options
        int choice = getOption(); 
        switch (choice) {
            case 1: {
                history.buildBrowserHistory();
                history.displayHistory();
                break;
            }
            case 2: {
                history.displayHistory();
                break;
            }
            case 3: {
                cout << "Enter the new web page's url:\n"; url = getInput(); 
                cout << "Enter the new web page's id:\n"; cin >> id; cin.ignore(); 
                WebPage *existingPage = history.searchPageByID(id); // If exists will return NULL
            
                while (existingPage != NULL) {//If page already exists it reiterates
                    cout << "This ID already exists. Try again.\n";
                    cout << "Enter the new web page's id:\n"; cin >> id; cin.ignore(); 
                    existingPage = history.searchPageByID(id); // Re-check with the new ID
                }
                cout << "Enter the previous page's url (or First):\n"; prevUrl = getInput();
                WebPage* previousPage = history.searchPageByURL(prevUrl); //if Invalid will return NULL
                while(previousPage == NULL && prevUrl != "First") { //checks to see if previous page is valid
                    cout << "INVALID(previous page url)... Please enter a VALID previous page url!\n";
                    cout << "Enter the previous page's url (or First):\n"; prevUrl = getInput();
                    previousPage = history.searchPageByURL(prevUrl); 
                    if(prevUrl != "First") {
                    previousPage = NULL;
                    break;
                    }
                }
                WebPage* newPage = new WebPage{id, 0, url, "", nullptr};
                history.addWebPage(previousPage, newPage);
                break;
            }
            case 4: {
                cout << "Enter url of the web page to add the owner:\n"; url = getInput();
                cout << "Enter the owner:"; owner = getInput();
                history.addOwner(url, owner); 
                break; 
            }
            case 5: {
                while(true) {//added to match testing equality so menu doesn't print again
                    cout << "Enter url of the web page to check the view count: \n"; url = getInput();
                    WebPage* page = history.searchPageByURL(url);
                    if (page != nullptr) {
                        cout << "View count for URL - " << url << " is " << page->views << endl;
                        break;
                    } else {
                        cout << "Page not found. Try again." << endl;
                    }
                }
                break; 
            }   
            case 6:  {
                cout << "Quitting...Goodbye!\n";
                running = false;
                break;
            }
            default: {
                cout << "Invalid option. Please try again.\n";
            }
        }
    }
    return 0;
}

int getOption() {
    string line;
    getline(cin, line);
    return stoi(line);
}
string getInput() {
    string line;
    getline(cin, line);
    return line;
}
/************************************************
           Definitions for main_1.cpp
************************************************/
void displayMenu()
{
    // COMPLETE: You DO NOT need to edit this
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build history " << endl;
    cout << " 2. Display history " << endl;
    cout << " 3. Add web page " << endl;
    cout << " 4. Add owner" << endl;
    cout << " 5. View count for a web page" << endl;
    cout << " 6. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
