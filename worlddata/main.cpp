//
//  main.cpp
//  worlddata
//
//  Created by Kai on 2014-07-12.
//  Copyright (c) 2014 world data assignment. All rights reserved.
//

#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	vector<string> read;
	string store_data;
	int total_lines=0;
	ifstream infile("consumption.txt");
    
	while(getline(infile, store_data))
    {
	    ++total_lines;
		read.push_back(store_data);
	}
	cout << "Initialising from consumption.txt: " << total_lines << " lines," << endl;
	string str2 ("Canada");
    
    for(vector<string>::size_type i=0; i<read.size(); i++)
	{
		cout << read.at(i) << endl;
        
	}
}
