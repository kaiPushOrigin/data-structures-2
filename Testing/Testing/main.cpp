//
//  main.cpp
//  Testing
//
//  Created by Kai on 2014-08-01.
//  Copyright (c) 2014 data structures assignment. All rights reserved.
//

#include <iostream>
#include <string>

int main ()
{
    std::string str="Oscars: 3";
    // (quoting Alfred N. Whitehead)
    
    //std::string str2 = str.substr (12,12);   // "generalities"
    
    std::size_t pos = str.find(" ");      // position of "live" in str
    
    std::string str3 = str.substr (pos);     // get from "live" to the end
    
    std::cout  << ' ' << str3 << '\n';
    
    return 0;
}
