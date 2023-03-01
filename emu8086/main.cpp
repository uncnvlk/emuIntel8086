//
//  main.cpp
//  emu8086
//
//  Created by Elizaveta Sidorenkova on 25.02.2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "math.h"
#include <stack>
#include <sstream>
#include "stack.hpp"
#include "rma8086.hpp"
#include <iostream>
#include <filesystem>
#include <unistd.h>

using namespace std;

vector<std::string> split(string stringToBeSplitted, char delimeter)
{
    std::vector<std::string> splittedString;
    int startIndex = 0;
    int  endIndex = 0;
    while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
    {
        std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
        splittedString.push_back(val);
        startIndex = endIndex + 1;
    }
    if(startIndex < stringToBeSplitted.size())
    {
        std::string val = stringToBeSplitted.substr(startIndex);
        splittedString.push_back(val);
    }

    return splittedString;
}

string showReg(string *reg) {
    string temp = *reg;
    return temp;
}

void checkReg(RMA8086 emu) {
    emu.split(emu.AX);
    emu.split(emu.BX);
    emu.split(emu.CX);
    emu.split(emu.DX);
}

int main() {
    string path;
    string str;
    vector <string> arr;
    vector <string> elems;
    char tmp[256];
    getcwd(tmp, 256);
    string stmp(tmp);
    path = stmp + "/TEST.txt";
    ifstream f(path);

    while (f) {
        getline(f,str);
        arr.push_back(str);
    }

    f.close();
    int n = arr.size() - 1;
    for (int i = 0; i < n; i++) {
        cout << arr.at(i) << endl;
    }
    //int n = arr.size();
    int m = 6;
    RMA8086 emu = RMA8086();
    cout << "****************************" << endl;

    for (int i = 0; i < n; i++) {
        arr.at(i).erase(std::remove(arr.at(i).begin(), arr.at(i).end(), ','), arr.at(i).end());
        std::vector<std::string> spl = split(arr.at(i), ' ');

        if (spl.at(0) == "PUSH") {
            emu.push(emu.checkreg(spl.at(1)));
        }
        else if (spl[0] == "POP") {
            emu.push(emu.checkreg(spl.at(1)));
            checkReg(emu);
        }
        else if (spl[0] == "MOV") {
            emu.mov(emu.checkreg(spl.at(1)), emu.checkreg(spl.at(2)));
            checkReg(emu);
        }
        else if (spl[0] == "ADD") {
            emu.add(emu.checkreg(spl.at(1)), emu.checkreg(spl.at(2)));
            checkReg(emu);
        }
        else if (spl[0] == "SUB") {
            emu.sub(emu.checkreg(spl.at(1)), emu.checkreg(spl.at(2)));
            checkReg(emu);
        }
        else if (spl[0] == "DEC") {
            emu.dec(emu.checkreg(spl.at(1)));
            checkReg(emu);
        }
        else if (spl[0] == "INC") {
            emu.inc(emu.checkreg(spl.at(1)));
            checkReg(emu);
        }
        else if (spl[0] == "XCHG") {
            emu.xchg(emu.checkreg(spl.at(1)), emu.checkreg(spl.at(2)));
            checkReg(emu);
        }
        else if (spl[0] == "NOT") {
            emu.NOT(emu.checkreg(spl.at(1)));
            checkReg(emu);
        }
        else if (spl[0] == "OR") {
            emu.OR(emu.checkreg(spl.at(1)), emu.checkreg(spl.at(2)));
            checkReg(emu);
        }
        else if (spl[0] == "AND") {
            emu.AND(emu.checkreg(spl.at(1)), emu.checkreg(spl.at(2)));
            checkReg(emu);
        }
        else if (spl[0] == "NOP") {
            emu.NOP();
        }
    }
    //string S = showReg(emu.AX.lowReg);
//    cout << S << endl;
    cout << "AH: " << showReg(emu.AX.highReg) << endl;
    cout << "AL: " << showReg(emu.AX.lowReg) << endl;

    cout << "BH: " << showReg(emu.BX.highReg) << endl;
    cout << "BL: " << showReg(emu.BX.lowReg) << endl;

    cout << "CH: " << showReg(emu.CX.highReg) << endl;
    cout << "CL: " << showReg(emu.CX.lowReg) << endl;

    cout << "DH: " << showReg(emu.DX.highReg) << endl;
    cout << "DL: " << showReg(emu.DX.lowReg) << endl;

    return 0;
}
