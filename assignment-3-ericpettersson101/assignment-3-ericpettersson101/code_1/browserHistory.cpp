/*************************************************************/
/*                BrowserHistory Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of BrowserHistory    */
/*     This class uses a linked-list of WebPage structs to   */
/*     represent the schedule of web pages                   */
/*************************************************************/

#include "browserHistory.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
//Added cus guy in CESEL Said I should to provent memory leaks 
BrowserHistory::~BrowserHistory() {
    WebPage* current = head;
    while (current != NULL) {
        WebPage* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}
BrowserHistory::BrowserHistory() {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool BrowserHistory::isEmpty() {
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: prints the current list of pages 
 * in the given format.
 * [ID::1]-(URL::url1) -> ... -> NULL
 * @param none
 * @return none
 */
void BrowserHistory::displayHistory() {
    if(isEmpty()) {
        cout << "== CURRENT BROWSER HISTORY ==\nEmpty History\nNULL\n===\n";
    } else {
        cout << "== CURRENT BROWSER HISTORY ==\n";
        WebPage* currentPage = head;
        while(currentPage != NULL) {
            cout << "[ID:: " << currentPage->id << "]-" << "(URL::" << currentPage->url << ") -> ";
            currentPage = currentPage->next;
        }
        cout << "NULL\n===\n";
    }
}

/*
 * Purpose: Add a new webpage to the browser history LL
 *   between the previous and the page that follows it in the list.
 * @param previousPage, the show that comes before the new page
 * @param newPage, the webpage to be added. 
 * @return none
 */
void BrowserHistory::addWebPage(WebPage* previousPage, WebPage* newPage) {
    // TODO
    if (previousPage == NULL) {
        newPage->next = head;
        head = newPage;
        cout << "adding: [" << newPage->id << "]-" << newPage->url << " (HEAD)\n";
    } else {
        newPage->next = previousPage->next;
        previousPage->next = newPage;
        cout << "adding: [" << newPage->id << "]-" << newPage->url << " (prev: [" << previousPage->id << "])\n";
    }
}

/*
 * Purpose: populates the BrowserHistory with the predetermined pages
 * @param none
 * @return none
 */
void BrowserHistory::buildBrowserHistory() {
    //constructs a starting broswer history
    WebPage* previous = NULL;
    string startingHistory[] = {
        "https://www.colorado.edu/", "https://www.wikipedia.org/", "https://brilliant.org/", "https://www.khanacademy.org/", "https://www.numberphile.com/" };
    
    for(int i=0; i < 5; i++ ) {
        addWebPage(previous, new WebPage{i+10, 0, startingHistory[i], "", nullptr}); 
        previous = searchPageByID(i+10); 
    }
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by ID and return a pointer to that node.
 * @param int id - ID of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByID(int id) {
    WebPage* currentPage = head;
    while (currentPage != NULL) {
        if (currentPage->id == id)  {
            return currentPage;
        }
    currentPage = currentPage->next;
    }
    return nullptr;
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by the URL and return a pointer to that node.
 * @param string url - url of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByURL(std::string url) {
        WebPage* currentPage = head;
    while (currentPage != NULL) {
        if (currentPage->url == url)  {
            return currentPage;
        }
    currentPage = currentPage->next;
    }
    return NULL;
}

/*
 * Purpose: Give an owner to a web page.
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void BrowserHistory::addOwner(std::string url, string owner) {
    WebPage* page = searchPageByURL(url);
    if(page) { 
        page->owner = owner;
        cout << "The owner (" << owner << ") has been added for the ID - "<< page->id << "\n";
    } else {
        cout << "Page not found\n";
    }
}

void BrowserHistory::updateViews(string url) {
    WebPage* currentPage = head;
    while (currentPage != nullptr) {
        if (currentPage->url.compare(url) == 0) { 
            currentPage->views++; 
        }
        currentPage = currentPage->next; 
    }
}

