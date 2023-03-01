//
//  stack.cpp
//  emu8086
//
//  Created by Elizaveta Sidorenkova on 25.02.2023.
//

#include "stack.hpp"
#include <iostream>

Stack::Stack(){
}

    bool Stack::IsEmpty() {
        if (this->top != 0) {
            return 0;
        }
        else {
            return 1;
        }
    }

    bool Stack::IsFull() {
        if (this->top == this->MAX) {
            return 1;
        }
        else {
            return 0;
        }
    }

    void Stack::push(std::string newElement) {
        if (this->IsFull() == true) {
            std::cout << ("Стек заполнен") << std::endl;
        }
        else {
            this->top++;
            this->stack[this->top] = newElement;
        }
        this->size++;
    }

    std::string Stack::pop() {
        if (this->IsEmpty() == true) {
            std::cout << ("Стек пустой") << std::endl;
            return "0";
        }
        else {
            std::string temp = this->stack[this->top];
            this->top--;
            return temp;
        }
        this->size--;
    }

    void Stack::peek() {
        std::cout << "Стек:" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << this->stack[i] << std::endl;
        }
    }
