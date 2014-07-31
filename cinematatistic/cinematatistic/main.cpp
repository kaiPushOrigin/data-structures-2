/*
 *  Assignment 2 Sample Solution
 *  Tami Meredith, July 2014
 *  Uses some heap code from course text book
 */
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <vector>

using namespace std;

static const int tableSize = 200;

class movie {
public:
	string name, year, summary, director, stars;
	string oscars, oscarNominations, baftaAwards, baftaNominations;
	string goldenGlobes, goldenGlobeNominations, space;
    int nameLength;
};

struct movieList {
    string name, summary, director, stars;
	string oscars, oscarNominations, baftaAwards, baftaNominations;
	string goldenGlobes, goldenGlobeNominations, space;
    int nameLength;
    movieList* next;
};

movieList* HashTable[tableSize];

 //Global Variable

void display(movie movies[], int n)
{
 for (int i = 0; i < n; i++)
 {
        cout << "The lenght of " << movies[i].name << " is " << movies[i].nameLength << endl;
 }
}

void CreateHashTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        HashTable[i] = new movieList;
        HashTable[i]->name = "empty";
        HashTable[i]->summary = "empty";
        HashTable[i]->director = "empty";
        HashTable[i]->stars = "empty";
        HashTable[i]->oscars = "empty";
        HashTable[i]->oscarNominations = "empty";
        HashTable[i]->baftaAwards = "empty";
        HashTable[i]->baftaNominations = "empty";
        HashTable[i]-> goldenGlobes = "empty";
        HashTable[i]->goldenGlobeNominations = "empty";
        HashTable[i]->next = NULL;
    }
}

int hashFunction(string key)
{
    int hash = 0;
    int location;
    location = key.length();
    for(int i = 0; i < key.length(); i++)
    {
        hash = hash + int(char(tolower(key[i])));
        cout << int(char(tolower(key[i]))) << endl;
    }
    location = hash % tableSize;
    return location;
    
    //for (int i = 0; i < n; i++)
    //{
       // hash = 0;
        //for (int j = 0; j < movies[i].nameLength; j++)
       // {
         //   hash = hash + int(movies[i].name[j]);
        //}
        //location = hash % tableSize;
   // }
}

void Additem(movie movies[], string key, int indexValue)
{
    //string name = movies[indexValue].name;
    int location = hashFunction(key);
    if(HashTable[location]->name == "empty")
    {
        HashTable[location]->name = movies[indexValue].name;
        HashTable[location]->summary = movies[indexValue].summary;
        HashTable[location]->director = movies[indexValue].director;
        HashTable[location]->stars = movies[indexValue].stars;
        HashTable[location]->oscars = movies[indexValue].oscars;
        HashTable[location]->oscarNominations = movies[indexValue].oscarNominations;
        HashTable[location]->baftaAwards = movies[indexValue].baftaAwards;
        HashTable[location]->baftaNominations = movies[indexValue].baftaNominations;
        HashTable[location]->goldenGlobes = movies[indexValue].goldenGlobes;
        HashTable[location]->goldenGlobeNominations = movies[indexValue].goldenGlobeNominations;
    }
    else
    {
        movieList* Ptr = HashTable[location];  //Link other items
        movieList* n = new movieList;
        n->name = movies[indexValue].name;
        n->summary = movies[indexValue].summary;
        n->director = movies[indexValue].director;
        n->stars = movies[indexValue].stars;
        n->oscars = movies[indexValue].oscars;
        n->oscarNominations = movies[indexValue].oscarNominations;
        n->baftaAwards = movies[indexValue].baftaAwards;
        n->baftaNominations = movies[indexValue].baftaNominations;
        n->goldenGlobes = movies[indexValue].goldenGlobes;
        n->goldenGlobeNominations = movies[indexValue].goldenGlobeNominations;
        n->next = NULL;
        while (Ptr->next != NULL)   // the next eement is not pointing to null
        {
            Ptr = Ptr->next;        //make pointer advance down the list
        }
        Ptr->next = n;
    }
    //cout << "Item found for " << HashTable[12]->name;
}

int numberOfItemsInLocation(int index)
{
    int count = 0;
    if(HashTable[index]->name == "empty")
    {
        return count;
    }
    else
    {
        count++;
        movieList* Ptr = HashTable[index];
        while(Ptr->next!= NULL)
        {
            count++;
            Ptr = Ptr->next;
        }
    }
    return count;
}

void PrintItemsInIndex(int index)
{
    movieList* Ptr = HashTable[index];
    if(Ptr->name == "empty")
    {
        cout << index << "is empty";
    }
    else
    {
        cout << "index " << index << " contains the following items\n";
        while(Ptr!=NULL)
        {
            cout << Ptr->name << endl;
            cout << Ptr->director << endl;
            Ptr = Ptr->next;
        }
    }
    
}

void FindData(string name)
{
    string lowerName = name;
    string hashCopy;
    for (int i = 0; i < name.length(); i++)
    {
        char(tolower(lowerName[i]));
        
    }
    int index = hashFunction(lowerName);
    bool foundName = false;
    movieList* Ptr = HashTable[index];
    string movName;
    string movDirector;
    string movStars;
    string movSummary;
    
    while(Ptr != NULL)
    {
        if((Ptr->name) == name)
        {
            foundName = true;
            
            movName = Ptr->name;
            movSummary = Ptr->summary;
            movDirector = Ptr->director;
            movStars = Ptr->stars;
        }
        Ptr = Ptr->next;
    }
    if(foundName == true)
    {
        cout << movName << endl;
        cout << movDirector << endl;
        cout << movStars << endl;
        cout << movSummary << endl;
    }
    else
    {
        cout << "Not Found";
    }
    
}

void PrintHashTable()
{
    int number;
    for(int i = 0; i < tableSize; i++)
    {
        number = numberOfItemsInLocation(i);
        cout << "index = " << i << endl;
        cout << HashTable[i]->name << endl;
        cout << HashTable[i]->director << endl;
        cout << "Number of items = " << number << "\n\n\n" << endl;
    }
}



int main()
{
    CreateHashTable();
    int indexValue = 0;
	movie  movies[1100];
	int count = 0;
    string name;
	string line, token, input;
	ifstream infile("movies.txt");

    while (getline(infile,line) )
	{
		switch (count)
		{
			case 0:
            {
                std::size_t pos = line.find("(");
                string movieName = line.substr(0, pos-1);
                //string movieYear = line.substr(pos-1, 2);
                movies[indexValue].name = movieName;
                //movies[indexValue].year = movieName;
                cout << movieName<<endl;
                //cout << movieYear << endl;
                movies[indexValue].nameLength = movies[indexValue].name.length();
                name = movies[indexValue].name;
                break;
            }
			case 1: movies[indexValue].summary = line; break;
			case 2: movies[indexValue].director = line; break;
			case 3: movies[indexValue].stars = line; break;
			case 4: movies[indexValue].oscars = line; break;
			case 5: movies[indexValue].oscarNominations = line; break;
			case 6: movies[indexValue].baftaAwards = line; break;
			case 7: movies[indexValue].baftaNominations = line; break;
			case 8: movies[indexValue].goldenGlobes = line; break;
			case 9: movies[indexValue].goldenGlobeNominations = line; break;
			case 10:
            {
                movies[indexValue].space = line; count = -1; indexValue++;
                //cout << name << endl;
                Additem(movies, name, indexValue-1);
                break;
			default: break;
            }
	    }
        count++;
        
	}
    
    //PrintItemsInIndex(5);
    PrintHashTable();
    string key = " ";
    while(key != "exit")
    {
        cout << "Search for ?";
        getline(cin,key,'\n');
        cout << key;
        if(key != "exit")
        {
            FindData(key);
        }
    }
    
    
   
    //hashFunction(movies, indexValue);
	//display(movies, indexValue);
    //cout <<  movies[5].name;
}



