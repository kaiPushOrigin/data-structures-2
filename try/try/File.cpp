

/*
#include<iostream>

using namespace std;
class Patient
{
public:
    string name, notes;
    int priority;
};

int heapmax(int *);
int heapextractmax(int *);
void heapincreasekey(int *,int ,int );
void maxheapinsert(int *,int );
void maxheapify(int *,int );
int heapsize;
int main()
{
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
        cin>>option;
        switch(option)
        {
            case 1:
                cout<<"enter element"<<endl;
                cin>>n;
                maxheapinsert(a,n);
                break;
            case 2:
                cout<<heapextractmax(a)<<endl;
                break;
            case 3:
                cout<<heapmax(a)<<endl;
                break;
        }
    }
    return 0;
}
int heapmax(int *a)
{
    if(heapsize<1){
        cout<<"underflow"<<endl;
        exit(1);
    }
    return(a[0]);
}
int heapextractmax(int *a)
{
    if(heapsize<1){
        cout<<"underflow"<<endl;
        exit(1);
    }
    int max;
    max=a[0];
    a[0]=a[heapsize-1];
    heapsize=heapsize-1;
    maxheapify(a,0);
    return max;
}
void heapincreasekey(int *a,int i,int key)
{
    int parent,temp;
    if(a[i]>key)
    {
        cout<<"previous key is greater than this key"<<endl;
        return;
    }
    a[i]=key;
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
void maxheapinsert(int *a,int key)
//a = array size
//key = number
{
    a[heapsize]=-1;
    heapsize=heapsize+1;
    heapincreasekey(a,heapsize-1,key);
}
void maxheapify(int *a,int i)
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
        maxheapify(a,largest);
    }
}*/