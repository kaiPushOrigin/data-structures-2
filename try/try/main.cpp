#include<iostream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
class Patient
{
public:
    string name, notes, total;
    int priority;
};

void heapmax(int *, Patient pat);
int heapextractmax(int *, Patient pat);
void heapincreasekey(int *,int ,int, Patient pat );
void maxheapinsert(int *,Patient pat );
void maxheapify(int *,int, Patient pat );
int heapsize;

int main()
{
    string b[] = {"hello", "hi"};
    cout << b[0][0];
    int i = 1;
    int parent = (i-1)/2;
    cout << parent;
    Patient pat;
	string name;
	string priority;
	int patientsWaiting = 0;
    int size,n;
    cout<<"enter array size"<<endl;
    cin>>size;
    int *a;
    a=new int[size]; //array size
    heapsize=0;
    int option=1;
    while(option)
    {
        cout<<"insert an element - 1"<<endl;
        cout<<"extract max element -2"<<endl;
        cout<<"print the max element -3"<<endl;
        cin.ignore();
        cin>>option;
        string name;
        switch(option)
        {
            case 1:
                cout << "Name: ";
                cin >> name;
                pat.name = name;
                cout << pat.name;
                cin.ignore(80, '\n');
                cout << "\nPriority: ";
                cin >> pat.priority;
                cout << "\nNotes: ";
                cin >> pat.notes;
                patientsWaiting++;
				priority = to_string(pat.priority);
				pat.total = string(priority) +string(pat.name) + string(pat.notes);
				cout << pat.total;
                maxheapinsert(a,pat);
                break;
            case 2:
                cout<<heapextractmax(a, pat)<<endl;
                break;
            case 3:
                heapmax(a, pat);
                break;
        }
    }
    return 0;
}
void heapmax(int *a, Patient pat) //no object
{
    if(heapsize<1){
        cout<<"underflow"<<endl;
        exit(1);
    }
    cout << (a[0]) << endl;
    //cout << pat.priority;
    //cout << "hi" << endl;
    //pat.priority = a[0];
    //cout << pat.name;
    //if(pat.priority ==a[0])
    //{
    //    cout << "True";
    //    //cout << pat.priority << " " << pat.name;
    //}
}
int heapextractmax(int *a, Patient pat)  //no object
{
    if(heapsize<1){
        cout<<"underflow"<<endl;
        exit(1);
    }
    int max;
    max=a[0];
    a[0]=a[heapsize-1];
    heapsize=heapsize-1;
    maxheapify(a,0, pat);
    return max;
}
void heapincreasekey(int *a,int i,Patient pat)
{
    int parent,temp;
    if(a[i]>pat.priority)
    {
        cout<<"previous key is greater than this key"<<endl;
        return;
    }
    a[i]=pat.priority;
    while(i>0)
    {
        parent=(i-1)/2;
        if(a[i]>a[parent])
        {
            temp=a[i];
            a[i]=a[parent];
            a[parent]=temp;
        }
        i=parent;
    }
}
void maxheapinsert(int *a,Patient pat)
////a = array size
///key = number
{
    a[heapsize]=-1;
    heapsize=heapsize+1;
    cout << "Name = " << pat.name;

    heapincreasekey(a,heapsize-1,pat);
}
void maxheapify(int *a,int i, Patient pat)  //no object
{
    int left,right,largest,temp;
    left=2*i+1;
    right=2*i+2;
    if(left<heapsize && a[i]<a[left])
        largest=left;
    else
        largest=i;
    if(right<heapsize && a[right]>a[largest])
        largest=right;
    if(largest!=i)
    {
        temp=a[i];
        a[i]=a[largest];
        a[largest]=temp;
        maxheapify(a,largest, pat);
    }
}