#include "PriorityQueue.hpp"
#include <limits.h>//not used
#include <stdexcept>
#include <iostream>


using namespace std;



/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap) {
    capacity = cap;
    currentSize = 0;
    heapArr = new ReviewInfo[capacity];
}

/*
Destructor
*/
PriorityQ::~PriorityQ() {
    delete[] heapArr;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index) {
    return (index - 1) / 2;
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index) {
    return (2 * index) + 1;
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index) {
    return (2 * index) + 2;
}

//moved after utility functions  & implmented as a member function
void swap(ReviewInfo *a, ReviewInfo *b) {
    ReviewInfo temp = *a;
    *a = *b;
    *b = temp;
}

void PriorityQ::peek() {
    if (currentSize <= 0) {
        throw std::runtime_error("Heap is empty");
    }
    cout << "Top Element: " << heapArr[0].review << endl;
}

void PriorityQ::heapify(int index) {
    int left = leftChild(index);
    int right = rightChild(index);
    int smallest = index;

    if (left < currentSize && heapArr[left].time < heapArr[smallest].time) {
        smallest = left;
    }
    if (right < currentSize && heapArr[right].time < heapArr[smallest].time) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heapArr[index], &heapArr[smallest]);
        heapify(smallest);
    }
}

void PriorityQ::insertElement(ReviewInfo value) {
   
    if (currentSize == capacity) {
        throw overflow_error("Heap capacity overflow");
    } 

    // Place the new element at the end of the heap
    heapArr[currentSize] = value;
    int current = currentSize;
    currentSize++;

    // Fix the min heap property if it is violated
while (current != 0 && heapArr[parent(current)].time > heapArr[current].time) {
    swap(&heapArr[current], &heapArr[parent(current)]);
    current = parent(current);
}
}

/*
Prints the elements in the heap
*/
void PriorityQ::print() {
    cout << "Priority Queue Elements:" << endl;
    for (int i = 0; i < currentSize; i++) {
        cout << "Restaurant: " << heapArr[i].restaurantName << ", Review: " << heapArr[i].review
             << ", Customer: " << heapArr[i].customer << ", Time: " << heapArr[i].time << endl;
    }
}

// Remove the element at the root of the heap
void PriorityQ::pop() {
    if (currentSize <= 0) {
        throw std::underflow_error("Heap underflow");
    }
    if (currentSize == 1) {
        currentSize--;
        return;
    }

    // Move the last element to the root and reduce heap size
    heapArr[0] = heapArr[currentSize - 1];
    currentSize--;
    heapify(0);
}