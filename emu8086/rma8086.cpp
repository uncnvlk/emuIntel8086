//
//  rma8086.cpp
//  emu8086
//
//  Created by Elizaveta Sidorenkova on 25.02.2023.
//
#include <unistd.h>
#include "rma8086.hpp"
#include <stdio.h>
#include "register.hpp"
#include "stack.hpp"
#include <cmath>


RMA8086::RMA8086(){
    
};
    void RMA8086::push (string* newElement) {
        this->stack.push(*newElement);
    };

    // POP – вытащить из стека
    // 10
    void RMA8086::pop (string *reg) {
        *reg = this->stack.pop();
    };



    string* RMA8086::checkreg(string xReg) {
        string *p = &xReg;
        this-> d = false;
        if (xReg == "AX") {
            this->AX.X = true;
            string temp = *(this->AX.highReg) + *(this->AX.lowReg);
            *(this->AX.xReg) = temp;
            return this->AX.xReg;
        } else
            if (xReg == "BX") {
                this->BX.X = true;
                string temp = *(this->BX.highReg) + *(this->BX.lowReg);
                *(this->BX.xReg) = temp;
                return this->BX.xReg;
            } else
                if (xReg == "CX") {
                    this->CX.X = true;
                    string temp = *(this->CX.highReg) + *(this->CX.lowReg);
                    *(this->CX.xReg) = temp;
                    return this->CX.xReg;
                } else
                    if (xReg == "DX") {
                        this->DX.X = true;
                        string temp = *(this->DX.highReg) + *(this->DX.lowReg);
                        *(this->DX.xReg) = temp;
                        return this->DX.xReg;
                    } else
                        if (xReg == "AL"){
                            return this->AX.lowReg;
                        } else
                            if (xReg == "BL"){
                                return this->BX.lowReg;
                            } else
                                if (xReg == "CL"){
                                    return this->CX.lowReg;
                                } else
                                    if (xReg == "DL"){
                                        return this->DX.lowReg;
                                    } else
                                        if (xReg == "AH"){
                                            return this->AX.highReg;
                                        } else
                                            if (xReg == "BH"){
                                                return this->BX.highReg;
                                            } else
                                                if (xReg == "CH"){
                                                    return this->CX.highReg;
                                                } else
                                                    if (xReg == "DH"){
                                                        return this->DX.highReg;
                                                    } else {
                                                        this-> d = true;
                                                        return p;
                                                    }
    }


    // перевод 10->2
    string RMA8086::fromDecToBin(unsigned int decNum) {
        string binNum;
        while (decNum > 0) {
            int r = decNum % 2;
            binNum += to_string(r);
            decNum /= 2;
        }

        reverse(binNum.begin(), binNum.end());
        return binNum;
    }

    // перевод 2->10
    string RMA8086::fromBinToDec(string binNum) {
        int decNum = 0;
        for (int i = binNum.length() - 1; i >= 0; i--) {
            if (binNum[binNum.length() - i - 1] == '1') {
                decNum += pow(2.0, 1.0 * i);
            }
        }
        return to_string(decNum);
    }

    // разделение
    void RMA8086::split (Register AX) {
        if (this->AX.X == true) {
            string temp = "";
            string temp1 = *(AX.xReg);
            for (int i = 0; i < 8; i++) {
                temp += temp1[i];
            }
            *(AX.highReg) = temp;

            temp = "";
            for (int i = 8; i < 16; i++) {
                temp += temp1[i];
            }
            *(AX.lowReg) = temp;
        }
        this->AX.X = false;
    }

    // добавление нулей
    void RMA8086::addNULL (string* reg) {
        int length = reg->length();
        string temp = *reg;
        *reg = "";
        if (length != 8 and stoi(fromBinToDec(temp)) <= 255) {
            int n  = 8 - length;
            for (int i = 0; i < n; i ++) {
                *reg += "0";
            }
            *reg += temp;
        }
        else {
            if (length != 16 and stoi(fromBinToDec(temp)) > 255) {
                int n  = 16 - length;
                for (int i = 0; i < n; i ++) {
                    *reg += "0";
                }
                *reg += temp;
            } else *reg = temp;
        }
    };

    // mov
    // 1
    void RMA8086::mov(string* reg, string* num) {
        string*  N = num;
        if (this-> d == true) *N = fromDecToBin(stoi(*num));
        addNULL(N);
        *reg = *N;
        }

    // add
    // 2
    void RMA8086::add(string* reg, string* num) {
        string R = fromBinToDec(*reg);
        string N = *num;
        if (this-> d == false)  N = fromBinToDec(*num);
        int sum = stoi(R) + stoi(N);
        if (sum < 65535){
            *reg = fromDecToBin(sum);
            addNULL(reg);
        } else {
            string temp = fromDecToBin(sum);
            string temp1 = "";
            for (int i = 0; i < 16; i++) {
                temp1[i] = temp[i];
            }
            *reg = temp1;
        }
    }

    // sub
    // 3
    void RMA8086::sub (string* reg, string* num) {
        string R = fromBinToDec(*reg);
        string N = *num;
        if (this-> d == false) N = fromBinToDec(*num);
        int sub = stoi(R) - stoi(N);
        *reg = fromDecToBin(sub);
    }

    // dec
    // 4
    void RMA8086::dec (string* reg) {
        int decr = stoi(fromBinToDec(*reg)) - 1;
        *reg = fromDecToBin(decr);
    }

    // inc
    // 5
    void RMA8086::inc (string *reg) {
        int decr = stoi(fromBinToDec(*reg)) + 1;
        *reg = fromDecToBin(decr);
    }

    // mul
    // 6
    void RMA8086::mul (string *AX, string *DX, string *AL, string *reg, int N) {
        // int intAX = stoi(fromBinToDec(*AX));
        int intAL = stoi(fromBinToDec(*AL));
        int intReg = stoi(fromBinToDec(*reg));
        int intAX = stoi(*AX);
        string DXAX;
        int intDXAX;

        if (N == 1) {
            *AX = fromDecToBin(intAL * intReg);
        }
        else {
            intDXAX = intAX * intReg;
            DXAX = fromDecToBin(intDXAX);
            // организовать разделение двоичного числа на AX DX
        }
    }

    // div
    // 7
    void RMA8086::div (string *AX, string *DX, string *AL, string *AH, string *reg, int N) {
        int intAL = stoi(fromBinToDec(*AL));
        int intReg = stoi(fromBinToDec(*reg));
        int intAX = stoi(*AX);
        int intDXAX = stoi(*DX + *AX);
        int intAH = stoi(*AH);

        if (N == 1) {
            *AL = fromDecToBin(intAX / intReg);
            *AH = fromDecToBin(intAX % intReg);
        }
        else {
            *AX = fromDecToBin(intDXAX / intReg);
            *DX = fromDecToBin(intDXAX % intReg);
        }

    }

    // XCHG перестановка двух операндов
    // 8
    void RMA8086::xchg (string *reg1, string *reg2) {
        string  *temp = reg1;
        reg1 = reg2;
        reg2 = temp;
    }

    // NOT
    // 11
    void RMA8086::NOT (string *reg) {

        // двоичное число
        string temp = *reg;
        int n = temp.length();

        // инверсия
        for (int i = 0; i < n; i++) {
            if (temp[i] == '1') {
                temp[i] = '0';
            }
            else {
                temp[i] = '1';
            };
        };
        *reg = temp;
    };

    // OR
    // 12
    void RMA8086::OR (string *reg1, string *reg2) {
        // двоичное число
        string *temp;

        // ИЛИ
        for (int i = 0; i < temp->length(); i++) {
            *(temp +i) = to_string(stoi(*(reg1+i)) + stoi(*(reg2+i)));
        };
        reg1 = temp;
    };

    // AND
    // 13
    void RMA8086::AND (string *reg1, string *reg2) {
        // двоичное число
        string temp = "";
        string r1 = *reg1;
        string r2 = *reg2;

        // И
        for (int i = 0; i < reg1->length(); i++) {
            //int andd = stoi(r1[i]) * stoi(r2[i]);
            string str = to_string((r1[i] - '0') * (r2[i]-'0'));
            temp += str[0] ;
        };
        *reg1 = temp;
    };

    // NOP – задержка
    // 14
    void RMA8086::NOP () {
        sleep(5000);
    };
