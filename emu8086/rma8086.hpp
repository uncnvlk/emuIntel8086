//
//  rma8086.hpp
//  emu8086
//
//  Created by Elizaveta Sidorenkova on 25.02.2023.
//

#ifndef rma8086_hpp
#define rma8086_hpp

#include <stdio.h>
#include "register.hpp"
#include "stack.hpp"
using namespace std;
//intel8086, 16bit
class RMA8086 {
    // регистры
public:
    Register AX;
    Register BX;
    Register CX;
    Register DX;
    Stack stack;

    // если двоичное, то false, иначе true
    bool d = false;
public:
    RMA8086();
    void push (string* newElement);
    void pop (string *reg);
    string* checkreg(string xReg);
    string fromDecToBin(unsigned int decNum);
    string fromBinToDec(string binNum);
    void split (Register AX);
    void addNULL (string* reg);
    void mov(string* reg, string* num);
    void add(string* reg, string* num);
    void sub (string* reg, string* num);
    void dec (string* reg);
    void inc (string *reg);
    void mul (string *AX, string *DX, string *AL, string *reg, int N);
    void div (string *AX, string *DX, string *AL, string *AH, string *reg, int N);
    void xchg (string *reg1, string *reg2);
    void NOT (string *reg);
    void OR (string *reg1, string *reg2);
    void AND (string *reg1, string *reg2);
    void NOP ();
};

#endif /* rma8086_hpp */
