/*
 *  Assignment 3 Sample Solution
 *  Author - Kashif
 *  GitHub Link - https://github.com/kashifkai28/data-structures-2/tree/Assignment-3/cinematatistic
 */
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class movie {
public:
	string name, year, summary, director, stars;
	string oscars, baftaAwards, goldenGlobes;
    int nameLength;
};

struct movieList {
    string name, year, summary, director, stars;
	string oscars, baftaAwards, goldenGlobes;
    int nameLength; string lowerCase;
    movieList* next;
};

static const int tableSize = 200;
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
        HashTable[i]->baftaAwards = "empty";
        HashTable[i]-> goldenGlobes = "empty";
        HashTable[i]-> lowerCase = "empty";
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
        HashTable[location]->baftaAwards = movies[indexValue].baftaAwards;
        HashTable[location]->goldenGlobes = movies[indexValue].goldenGlobes;
        HashTable[location]->lowerCase = movies[indexValue].name;
        for (int i = 0; i < HashTable[location]->lowerCase.length(); i++)
        {
            HashTable[location]->lowerCase[i] = char(tolower(HashTable[location]->lowerCase[i]));
        }
        
    }
    else
    {
        movieList* Ptr = HashTable[location];  // Link other items - separate chaining
        movieList* n = new movieList;
        n->name = movies[indexValue].name;
        n->year = movies[indexValue].year;
        n->summary = movies[indexValue].summary;
        n->director = movies[indexValue].director;
        n->stars = movies[indexValue].stars;
        n->oscars = movies[indexValue].oscars;
        n->baftaAwards = movies[indexValue].baftaAwards;
        n->goldenGlobes = movies[indexValue].goldenGlobes;
        n->lowerCase = movies[indexValue].name;
        for (int i = 0; i < n->lowerCase.length(); i++)
        {
            n->lowerCase[i] = char(tolower(n->lowerCase[i]));
        }
        n->next = NULL;
        while (Ptr->next != NULL)   // the next element is not pointing to null
        {
            Ptr = Ptr->next;        // make pointer advance down the list
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
        if(lowerName == Ptr->lowerCase)
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
        cout << movYear << ";" << movOscars << flush << "Oscar(s),";
        cout << movBafta << "BAFTA(s)," << movGoldenGlobe << "Golden Globe(s)" << endl;
        cout << movDirector << movStars << movSummary << "\n\n";
    }
    else
        cout << "That is a great movie, but it is not one of the top 100. \n\n";
}

string parseNumber(string value)
{
    size_t pos = value.find(":");
    string answer = value.substr(pos+1);
    for (int i = 0; i < answer.length(); i++)
    {
        if(answer.at(i) == '\r')   // if the name has a return character, convert it into a space character
            answer.at(i) = ' ';
    }
    return answer;
}

int main()
{
    CreateHashTable();
    int indexValue = 0;
	movie  movies[1100]; // 100 movies, each having 11 lines
	int count = 0;
    string name, line;   // name is the key
	ifstream infile("movies.txt");
    while (getline(infile,line) )
	{
		switch (count)
		{
			case 0:
            {
                size_t pos = line.find("(");
                string movieName = line.substr(0, pos-1);
                string movieYear = line.substr(pos+1, 4);
                movies[indexValue].name = movieName;
                movies[indexValue].year = movieYear;
                name = movies[indexValue].name;  // name is the key
                break;
            }
			case 1: movies[indexValue].summary = line; break;
			case 2: movies[indexValue].director = line; break;
			case 3: movies[indexValue].stars = line; break;
			case 4: movies[indexValue].oscars = parseNumber(line); break;
			case 6: movies[indexValue].baftaAwards = parseNumber(line); break;
			case 8: movies[indexValue].goldenGlobes = parseNumber(line); break;
			case 10:
            {
                count = -1; indexValue++;
                Additem(movies, name, indexValue-1);   // Add item into Hash Table
                break;
            }
            default: break;
	    }
        count++;
	}
    string key = " ";
    while(key != "the terminator")
    {
        cout << "What movie interests you? ";
        getline(cin, key);
        if(key != "the terminator")
        {
            FindData(key);
        }
        else
        {
            cout << "Shutting down. Hasta la vista, baby." << endl;
            return 0;
        }
    }
}