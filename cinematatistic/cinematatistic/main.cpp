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
    string name, year, summary, director, stars;
	string oscars, oscarNominations, baftaAwards, baftaNominations;
	string goldenGlobes, goldenGlobeNominations, space;
    int nameLength;
    movieList* next;
};

movieList* HashTable[tableSize];

void CreateHashTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        HashTable[i] = new movieList;
        HashTable[i]->name = "empty";
        HashTable[i]->year = "empty";
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
    string lowerCaseKey = key;
    for (int i = 0; i < key.length(); i++)
    {
        lowerCaseKey[i] = char(tolower(lowerCaseKey[i]));
        
    }
    for(int i = 0; i < key.length(); i++)
    {
        hash = hash + int(char(lowerCaseKey[i]));
    }
    location = hash % tableSize;
    return location;
    
}

void Additem(movie movies[], string key, int indexValue)
{
    int location = hashFunction(key);
    if(HashTable[location]->name == "empty")
    {
        HashTable[location]->name = movies[indexValue].name;
        HashTable[location]->year = movies[indexValue].year;
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
        n->year = movies[indexValue].year;
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
        while (Ptr->next != NULL)   // the next element is not pointing to null
        {
            Ptr = Ptr->next;        //make pointer advance down the list
        }
        Ptr->next = n;
    }
}

void FindData(string name)
{
    string lowerName = name;
    
    // make the entered name lowercase and send to hashfunction to see its location
    for (int i = 0; i < name.length(); i++)
    {
       lowerName[i] = char(tolower(lowerName[i]));
    }
    int index = hashFunction(lowerName);
    
    bool foundName = false;
    movieList* Ptr = HashTable[index];           // Pointer to its location in Hash Table
    string movName, movDirector, movStars, movSummary;
    string movOscars, movBafta, movGoldenGlobe, movYear;
    
    // lowercase the actual value in the Hash Table and compare it with the value entered
    string compareCase = Ptr->name;
    for (int i = 0; i < Ptr->name.length(); i++)
    {
        compareCase[i] = char(tolower(compareCase[i]));
    }
    
    while(Ptr != NULL)
    {
        if(Ptr->name == name || name == compareCase)
        {
            foundName = true;
            movName = Ptr->name;
            movSummary = Ptr->summary;
            movDirector = Ptr->director;
            movStars = Ptr->stars;
            movOscars = Ptr->oscars;
            movBafta = Ptr->baftaAwards;
            movGoldenGlobe = Ptr->goldenGlobes;
            movYear = Ptr->year;
        }
        Ptr = Ptr->next;
    }
   if(foundName == true)
    {
        cout << movName << endl;
        cout << movYear << ";" << movOscars << " Oscar(s)" << movBafta << " BAFTA(s)"
        << movGoldenGlobe << " Golden Globe(s)" << endl;
        cout << movDirector << endl;
        cout << movStars;
        cout << movSummary << "\n\n";

    }
    else
    {
        cout << "That is a great movie, but it is not one of the top 100. \n\n";
    }
    
}

string parseNumber(string value)
{
    std:: size_t pos = value.find(":");
    string answer = value.substr(pos+1, 3);
    return answer;
}

int main()
{
    CreateHashTable();
    int indexValue = 0;
	movie  movies[1100]; // 100 movies, each having 11 lines
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
                string movieYear = line.substr(pos+1, 4);
                movies[indexValue].name = movieName;
                movies[indexValue].year = movieYear;
                movies[indexValue].nameLength = movies[indexValue].name.length();
                name = movies[indexValue].name;
                break;
            }
			case 1: movies[indexValue].summary = line; break;
			case 2: movies[indexValue].director = line; break;
			case 3: movies[indexValue].stars = line; break;
			case 4: movies[indexValue].oscars = parseNumber(line); break;
			case 5: movies[indexValue].oscarNominations = line; break;
			case 6: movies[indexValue].baftaAwards = parseNumber(line); break;
			case 7: movies[indexValue].baftaNominations = line; break;
			case 8: movies[indexValue].goldenGlobes = parseNumber(line); break;
			case 9: movies[indexValue].goldenGlobeNominations = line; break;
			case 10:
            {
                movies[indexValue].space = line; count = -1; indexValue++;
                Additem(movies, name, indexValue-1);
                break;
			default: break;
            }
	    }
        count++;
        
	}
    string key = " ";
    while(key != "exit")
    {
        cout << "Search for ?";
        getline(cin,key,'\n');
        if(key != "exit")
        {
            FindData(key);
        }
    }
}



