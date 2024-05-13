#include <iostream>
#include <cstdlib>
#include <iostream>
#include "Register.hpp"


using namespace std;

Register::Register(){top = -1;}

/*
 * If the register is full or not
 * @returns 
 */
bool Register::isFull(){return top == SIZE - 1;}

/*
 * Adds money to stack.
 * @param money: the type of pancake's price times the quantity
 */
void Register::push( int money ){
   if(isFull()) {
        cout << "Stack overflow: " << endl;
    } else {
        a[++top] = money; 
    }
}

bool Register::isEmpty(){return top == -1;}

void Register::disp(){
   if (isEmpty()) {cout << "Stack is empty!" << endl;} 
   else {
        cout << "Stack contents from top to bottom:" << endl;
        for (int i = top; i >= 0; i--) {
            cout << a[i] << endl;
        }
    }
}

int Register::pop(){
   if(isEmpty()) {
        cout << "Stack empty, cannot pop an item!" << endl;
        return -1;
    } else {
        return a[top--]; 
    }
}