//worlddata.cpp
/*
 Author: Kashif Kashif
 Assignment No.: 0 - Bonus Assignment
 Algorithm Used : Linear Search
 */

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

int linear_search(
                  string &location,         //in
                  vector<string> &a  //in
);

int main(int argc, char* argv[])
{
    string location;                         //name of the country
    vector<string> data, data_stream;
    string store;
    string store_stream;
    int lines=0;                             //counts no. of lines
    ifstream inFile("consumption.txt");
    while(getline(inFile, store))
    {
        data.push_back(store);
        lines++;
    }
    
    for(vector<string>::size_type i=0; i<data.size(); ++i)
    {
        istringstream stream(data.at(i));           //string buffer
        while (!stream.eof())
        {
            getline(stream, store_stream, ',');
            data_stream.push_back(store_stream);
        }
    }
    
    cout <<"Initialising from consumption.txt: "<< lines <<" lines, "
    <<(lines-3)<<" records\n";
    do
    {
        cout<<"\nPlease enter the name of a country of interest: ";
        cin>>location;
        if(location=="Quit")
        {
            break;
        }
        int index;
        index=linear_search(location,data_stream);
        if(index==-1)
        {
            cout<<"\nNo data found for "<<location<<endl;
        }
        else
        {
            cout<<"> Average total consumption per person: "<<data_stream.at(index+1)
            <<" litres\n";
            cout<<"> "<<data_stream.at(index+4) <<"%  Beer, "
            <<data_stream.at(index+5) <<"% Wine, "
            <<data_stream.at(index+6) <<"% Spirits, "
            <<data_stream.at(index+7) <<"% Other" <<endl;
        }
    }while(location!="Quit");
}

int linear_search(
                  string &a,             //in
                  vector<string> &v      //in
)
{
    for(int i=0; i<(int)v.size(); ++i)
    {
        if(v.at(i)== a)
        {
            return i;
        }
    }
    return -1;  
}