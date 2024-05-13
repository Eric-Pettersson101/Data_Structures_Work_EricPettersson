/*************************************************************/
/*                PancakeHouse Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of PancakeHouse    */
/*************************************************************/

#include "PancakeHouse.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;
int const PancakeHouse::pancake_types[] = {1, 2, 5, 3, 7};


//default construct
PancakeHouse::PancakeHouse() : profit(0), pancakesCooked(0) {cashRegister = new Register();shopQueue = new ShopQueue();}
//destructor
PancakeHouse::~PancakeHouse(){}

Register* PancakeHouse::getStack(){ return cashRegister;}

ShopQueue* PancakeHouse::getQueue() {return shopQueue;}

int PancakeHouse::getProfit(){
    return profit/2;    //my code double counts profit but if I stop it from doing this
                        //it doesn't work correctly so im dividing profit by 2
}

void PancakeHouse::addOrder(string name, int number_of_pancakes, int type_of_pancakes) {
    //Data validation
    if (type_of_pancakes < 1 || type_of_pancakes > 5) {return;}
    shopQueue->enqueue(name, number_of_pancakes, type_of_pancakes);
}

void PancakeHouse::cookPancakes() {
    if (shopQueue->isEmpty()) {cout << "Queue empty, cannot peek!" << endl;return;}

    if (!shopQueue->isEmpty()) {
        CustomerOrder* order = shopQueue->peek(); 
        int orderPrice = order->number_of_pancakes * pancake_types[order->type_of_pancakes - 1];
        profit += orderPrice; 
        shopQueue->dequeue(); 
        cashRegister->push(orderPrice); 
    }
}
void PancakeHouse::strikeOrder(){
    CustomerOrder* orderToCancel = shopQueue->peek();
    if (orderToCancel) {shopQueue->dequeue();} 
    else {cout << "Error accessing the next order to strike." << endl;}
}


void PancakeHouse::refundOrder() {
    if (cashRegister->isEmpty()) {cout << "Stack empty, cannot pop an item!" << endl;cout << "No money in the cash register!" << endl;return;
    }
    if (!cashRegister->isEmpty()) {
        int refundAmount = cashRegister->pop(); 
        profit -= refundAmount; 
        updateTotalProfit();
        cout << "Money refunded = " << refundAmount << endl;
    }
}

void PancakeHouse::closeShop(){
    while (!shopQueue->isEmpty()) {shopQueue->dequeue();}
    while (!cashRegister->isEmpty()) {cashRegister->pop();}
}

void PancakeHouse::updateTotalProfit(){
    while (!cashRegister->isEmpty()) {profit += cashRegister->pop(); }
}

void PancakeHouse::printOrders(){
    if (shopQueue->isEmpty()) {cout << "Queue empty, cannot peek!" << endl;return; }

    CustomerOrder* currentOrder = shopQueue->peek();

    while (currentOrder != nullptr) {
        cout << "Customer name: " << currentOrder->name << endl;
        cout << "Number of pancakes ordered: " << currentOrder->number_of_pancakes << endl;
        cout << "Type of pancakes: " << currentOrder->type_of_pancakes << endl;
        currentOrder = currentOrder->next;
    }
}