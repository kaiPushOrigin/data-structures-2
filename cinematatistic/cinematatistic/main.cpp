/*
 *  Assignment 2 Sample Solution
 *  Tami Meredith, July 2014
 *  Uses some heap code from course text book
 */
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>

using namespace std;

class movie {
public:
	string name, summary, director, stars;
	string oscars, oscarNominations, baftaAwards, baftaNominations;
	string goldenGlobes, goldenGlobeNominations, space;
    int nameLength;
};


void display(movie movies[], int n)
{
 for (int i = 0; i < n; i++)
 {
        cout << "The lenght of " << movies[i].name << " is " << movies[i].nameLength << endl;
 }
}

int hashFunction(movie movies[], int n)
{
    int hash = 0;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < movies[i].nameLength; j++)
        {
            hash = hash + int(movies[i].name[j]);
            cout << "for " << movies[i].name << " hash = " << hash << endl;
            
        }
       cout << "\n\n\n";
        hash = 0;
        
        // cout << "for " << movies[i].name << " hash = " << hash << endl;
    }
    return hash;
    
}

int main()
{
	movie  movies[1100];
	int count = 0;
	string line, token, input;
	ifstream infile("movies.txt");
    int index = 0;
    while (getline(infile,line) )
	{
		switch (count)
		{
			case 0: movies[index].name = line;
                movies[index].nameLength = movies[index].name.length();
			case 1: movies[index].summary = line; break;
			case 2: movies[index].director = line; break;
			case 3: movies[index].stars = line; break;
			case 4: movies[index].oscars = line; break;
			case 5: movies[index].oscarNominations = line; break;
			case 6: movies[index].baftaAwards = line; break;
			case 7: movies[index].baftaNominations = line; break;
			case 8: movies[index].goldenGlobes = line; break;
			case 9: movies[index].goldenGlobeNominations = line; break;
			case 10: movies[index].space = line; count = -1; index++; break;
			default: break;
	    }
        count++;
	}
    hashFunction(movies, index);
	//display(movies, index);
    //cout <<  movies[5].name;
}



