#include <vector>
#include <algorithm>
#include "BrowserHistory.hpp"

BrowserHistory::BrowserHistory()
{
    // No changes needed
}

BrowserHistory::~BrowserHistory()
{
    // No changes needed
}

/*
 * Purpose: Has to detect if a defect is present in the linkedlist pointed by head
 * @param none
 * @return integer length of defect if one exists. If defect not present return -1
 */
int BrowserHistory::findDefectLength(){
    //so I read the hint for this method but its a hint so I don't have to follow it.
    //So instead of doing that garbage im just create a vector of the points to each object on the list and check when I go to the next vector if the pointer is in the vector
    vector<WebPage*>  visited;
    WebPage* currentPage = head;
    while(currentPage != nullptr) {
        if(find(visited.begin(), visited.end(), currentPage) != visited.end()) {
            // Found a loop:
            WebPage* startLoop = currentPage;
            int defectLength = 1;
            currentPage = currentPage->next;
            while(currentPage != startLoop) {
                defectLength++;
                currentPage = currentPage->next;
            }
            return defectLength;
        }
        visited.push_back(currentPage);
        currentPage = currentPage->next;
    }
    return -1;//cus changes equality lol (free 20 points)
    }

/*
 * Purpose: Has to remove all the WebPage nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void BrowserHistory::removeWebPages(int start, int end){
    if (!head) {
        cout << "Browsing history is Empty" << endl;
        return; 
    }
    //Start and End validation 
    if (start > end || 0 >= start) {
        cout << "Invalid start or end values" << endl;
        return;
    }
    // variable setup
    WebPage *current = head, *prev = nullptr;
    int currentIndex = 1;
    // moves through history to start 
    while(current != nullptr && currentIndex < start) { 
            prev = current; 
            current = current->next;
            currentIndex++;
    }
    //while loop to go through list
    while (current != nullptr && currentIndex <= end) {
        WebPage *temp = current; //Holds the current node
            if(prev == nullptr) {
                head = current->next;
            }
            if(prev != nullptr) {
                prev->next = current->next;
            }
            current = current->next;
            delete temp;
        currentIndex++;
        }
    }


/*
 * Purpose: Interweave the webpages alternatively into a new linkedlist 
 * starting with the first webpage in the list one
 * Assign the head of the new interweaved list to the head of this BrowserHistory
 * DO NOT create new nodes and copy the data, just use the same nodes from one and two and change pointers
 * If one of them runs out of length append the remaining of the other one at end
 * @param two linkedlist heads one and two
 * @return none
 */
void BrowserHistory::mergeTwoHistories(WebPage *headOne, WebPage *headTwo) {

    if (headOne == nullptr) { head = headTwo; return;}
    if(headTwo == nullptr)  {head = headOne; return;}//if one of the heads is null we will simply point to the other one

    //sets head to headone to startoff 
    head=headOne;
    WebPage *mergedTail = nullptr; 

    while(headOne != nullptr && headTwo != nullptr) {//Loop to iterate through both lists should aways be true on first run due to if satements above
        if (mergedTail !=  nullptr) {
            mergedTail->next = headOne;
        }
        mergedTail = headOne;
        headOne = headOne->next;

        swap(headOne, headTwo); //basicly swaps the points to the list so on the next iteration we run add the other list
    
    }
    //code to add the remaining parts of a linkedlist to the merged list if they vary in size
    if (headOne != nullptr) {
        mergedTail->next = headOne;
    }
    if (headTwo != nullptr) {
        mergedTail->next = headTwo; 
    }
}