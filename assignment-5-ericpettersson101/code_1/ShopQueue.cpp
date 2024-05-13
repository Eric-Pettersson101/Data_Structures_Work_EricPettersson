#include "ShopQueue.hpp"
#include <iostream>

using namespace std;

ShopQueue::ShopQueue() : queueFront(nullptr), queueEnd(nullptr) {}


ShopQueue::~ShopQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}


bool ShopQueue::isEmpty() {
return (queueFront == nullptr);
}

/**
 * Looks at the shopqueue and returns the most 'urgent' order on the queue. No elements should be removed.
 * @return A customer order
 */
CustomerOrder* ShopQueue::peek() {
   if (isEmpty()) {
        cout << "Queue empty, cannot peek!" << endl;
        return nullptr; 
    } else {
        return queueFront; 
    }
}

 
void ShopQueue::enqueue(string name, int num_pancakes, int type_of_pancake) {
   CustomerOrder* newOrder = new CustomerOrder; 
    newOrder->name = name;
    newOrder->number_of_pancakes = num_pancakes;
    newOrder->type_of_pancakes = type_of_pancake;
    newOrder->next = nullptr;

    if (isEmpty()) { 
        queueFront = newOrder; 
        queueEnd = newOrder; 
    } else { 
        queueEnd->next = newOrder; 
        queueEnd = newOrder; 
    }
}

void ShopQueue::dequeue() {
   if (isEmpty()) { 
        cout << "Queue empty, cannot dequeue!" << endl;
    } else {
        CustomerOrder* temp = queueFront; 
        queueFront = queueFront->next; 
        delete temp; 

        if (queueFront == nullptr) { 
            queueEnd = nullptr; 
        }
    }
}


int ShopQueue::queueSize(){
    int count = 0;
    CustomerOrder* current = queueFront; 

    while (current != nullptr) { 
        count++; 
        current = current->next; 
    }

    return count; 
}


CustomerOrder* ShopQueue::getQueueEnd(){
   return queueEnd;
}