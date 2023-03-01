//
//  register.hpp
//  emu8086
//
//  Created by Elizaveta Sidorenkova on 25.02.2023.
//

#ifndef register_hpp
#define register_hpp

#include <stdio.h>
#include <string>
#include <iostream>
struct Register {

public :
    // AL
    std::string lR;
    std::string *lowReg;

    // AH
    std::string hR;
    std::string *highReg = &lR;

    // AX
    std::string xR;
    std::string *xReg;

    // если меняется xReg, то true
    bool X;

};
#endif /* register_hpp */
