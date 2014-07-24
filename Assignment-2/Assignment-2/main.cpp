// Author: Kashif Kashif
// A# : A00369617
// Assignment - 2: Heap Based Priority Queue
// Note: max heap code studied from http://www1.planet-source-code.com/vb/scripts/ShowCode.asp?txtCodeId=12327&lngWId=3

#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
class Patient
{
public:
	string name, notes, priority, total, patientNumber;
};

void MaxHeapInsert(string *, Patient pat);                    // Inserts in the heap
void HeapIncreaseKey(string *, int, Patient pat );            // Checks the largest priority
void HeapExtractMax(string *, Patient pat);                   // Extracts the record with largest priority
void MaxHeapify(string *, int, Patient pat );                 // Resets the heap after extraction
int heapsize;                                                 // Heap size

int main()
{
	Patient pat;                                              // Create class object
	int patientsWaiting = 0;
	int patientNumber = 0;                                    // Acts as unique number for differentiating priorities
	string *a;
	a = new string[100];                                      // Array size
	heapsize = 0;
	string delimiter = ",";                                   // Used while concatenating all the records
	char response;
	do
	{
		cout << "Patients waiting: " << patientsWaiting << ". Action(a,t,q)? ";
		cin >>response;
		if(response == 'a')
		{
			cout << "Name: ";
			cin.ignore(80, '\n');
			getline(cin, pat.name);
			cout << "Priority: ";
			cin >> pat.priority;
			cout << "Notes: ";
			cin.ignore(80, '\n');
			getline(cin, pat.notes);
			cout << "\n";
			patientsWaiting++;                                // Increment total patients
			patientNumber++;                                  // Increment patient number for each entry
            
			//convert integer into string
			pat.patientNumber = to_string(patientNumber);
            
			//concatenate string
			//pat.total has all records of the patient separated by comma
			//pat.total = priority,patientNumber,name,notes
			pat.total = string(pat.priority) +string(delimiter) + string(pat.patientNumber)
            + string(delimiter) + string(pat.name) + string(delimiter)
            +string(pat.notes);
			MaxHeapInsert(a,pat);                            // Insert the values in heap
		}
		else if(response == 't')
		{
			HeapExtractMax(a, pat);                          // Extract the record with highest priority
			patientsWaiting--;                               // Decrement total patients
		}
		else if(response == 'q')
		{
			cout << "Shutting down." << endl;
			return 0;
		}
	}while(response != 'q');
}

void MaxHeapInsert(string *a, Patient pat)
// a = array
// Inserts the entry into heap by calling HeapIncreaseKey
{
	a[heapsize] = -1;                                        // Set the initial value in heap
	heapsize = heapsize + 1;                                 // Increase heapsize for every entry
	HeapIncreaseKey(a, heapsize - 1 ,pat);
}

void HeapIncreaseKey(string *a, int i, Patient pat)
// i = heapsize - 1
// Checks if the priorities are the same
// Heap is created
{
	int parent;
	string temp;
	if(a[i][0] > pat.total[0])                               // Compare the first character of array with the priority i.e.(pat.total[0])
	{
		cout << "previous key is greater than this key" << endl;
		return;
	}
	a[i] = pat.total;                                        // index i = patient records
	while(i > 0)
	{
		parent = (i - 1) / 2;
		if(a[i] > a[parent] && a[i][1] != a[parent][1])      // Check the patient number i.e. the second character if the priorities are equal
		{
			temp = a[i];
			a[i] = a[parent];
			a[parent] = temp;
		}
		i = parent;
	}
}

void HeapExtractMax(string *a, Patient pat)
// Extracts the record with the highest priority
{
	if(heapsize < 1)
	{
		cout<<"underflow"<<endl;
		exit(1);
	}
	string max;                                              // Create a string to dispaly the extracted record
	max = a[0];
	a[0] = a[heapsize - 1];
	heapsize = heapsize-1;                                   // Decrease the heapsize after extraction
	MaxHeapify(a,0, pat);                                    // Reset the heap
	istringstream ss(max);                                   // Create a stream to display the comma separated values
	string token;
	string name;
	string priority;
	string notes;
	int counter = 1;
	while(getline(ss, token, ','))
	{
		if(counter == 1)
		{
			priority = token;
		}
		else if(counter == 2)
		{
			//do nothing                                     // Avoid dispalying the patient number
		}
		else if(counter == 3)
		{
			name = token;
		}
		else if(counter ==4)
		{
			notes = token;
			counter = 0;
		}
		counter = counter + 1;
	}
	cout << "TREATING->"<<name << " (" << priority << ") for "<< notes << "\n\n";
}

void MaxHeapify(string *a, int i, Patient pat)
// i = 0
// Resets the heap
{
	int left, right, largest;
	string temp;
	left = (2 * i) + 1;
	right = (2 * i) + 2;
	if(left < heapsize && a[i] <a [left])
		largest = left;
	else
		largest = i;
	if(right < heapsize && a[right] > a[largest])
		largest=right;
	if(largest != i)
	{
		temp = a[i];
		a[i] = a[largest];
		a[largest] = temp;
		MaxHeapify(a,largest, pat);
	}
}
