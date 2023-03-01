//
//  stack.hpp
//  emu8086
//
//  Created by Elizaveta Sidorenkova on 25.02.2023.
//

#ifndef stack_hpp
#define stack_hpp

#include <stdio.h>
#include <string>
#include <iostream>

// класс стек
class Stack {
    const int MAX = 16;
    std::string* stack;
    int top;
    int size;
    
    bool IsEmpty();
    bool IsFull();
    
    public :
    Stack();
    void push(std::string newElement);
    std::string pop();
    void peek();
};
#endif /* stack_hpp */
