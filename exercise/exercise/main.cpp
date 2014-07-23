/*
 *  Heapsort
 *  Tami Meredith, July 2014
 *  From Course Text
 */
#include <iostream>
#include <string>

#define debug 1

#define leftChild(node)    ((2*node)+1)
#define rightChild(node)   ((2*node)+2)
#define parent(node)       ((node-1)/2)
#define isLeaf(node,count) (leftChild(node) >= count)
#define newline()          cout<<"\n"

using namespace std;

template<class arrayType>
void display(arrayType anArray[], int n)
{
    for (int i = 0; i < n; i++)
        cout << anArray[i] << " ";
} // end display

template<class ItemType>
void heapRebuild(const int subTreeNodeIndex, ItemType items[], int itemCount)
{
    if (!isLeaf(subTreeNodeIndex, itemCount))
    {
        // Find larger child
        int leftChildIndex = leftChild(subTreeNodeIndex);   // A left child must exist
        int largerChildIndex = leftChildIndex;              // Make assumption about larger child
        int rightChildIndex = rightChild(subTreeNodeIndex); // A right child might not exist
        
        // Check to see whether a right child exists
        if (rightChildIndex < itemCount)
        {
            // A right child exists; check whether it is larger
            if (items[rightChildIndex] > items[largerChildIndex])
                largerChildIndex = rightChildIndex; // Asssumption was wrong
        }  // end if
        
        // If root value is smaller that the value in the larger child, swap values
        if (items[subTreeNodeIndex] < items[largerChildIndex])
        {
            swap(items[largerChildIndex], items[subTreeNodeIndex]);
            
            // Continue with the recursion at that child
            heapRebuild(largerChildIndex, items, itemCount);
        }  // end if
    }  // end if
}  // end heapRebuild

template <class ItemType>
void heapSort(ItemType anArray[], int n)
{
    // Build initial heap
    for (int index = n / 2; index >= 0; index--)
        heapRebuild<ItemType>(index, anArray, n);
    
#if debug
    display<ItemType>(anArray, n);
    cout << " Initial rebuild to form a heap" << endl;
#endif
    
    // Do the first swap
    swap (anArray[n-1], anArray[0]);
#if debug
    display<ItemType>(anArray, n);
    cout << " After swapping " << anArray[n-1]<< " and " << anArray[0] << endl;
#endif
    
    int heapSize = n - 1;  // Heap region size decreases by 1
    while (heapSize > 1)
    {
        heapRebuild<ItemType>(0, anArray, heapSize);
#if debug
        display<ItemType>(anArray, n);
        cout << " rebuild(0, anArray, " << heapSize << ")" << endl;
#endif
        heapSize--;
        swap (anArray[heapSize], anArray[0]);
#if debug
        display<ItemType>(anArray, n);
        cout << " After swapping " << anArray[0]<< " and " << anArray[heapSize] << endl;
#endif
    }  // end while
}  // end heapSort

int main()
{
    string a[6] = {"D", "B", "A", "C", "F", "E"};
    cout << "Original array: ";
    display<string>(a, 6);
    newline();
    heapSort<string>(a, 6);
    cout << "Sorted array: ";
    display<string>(a, 6);
    newline();
    
    int b[8] = {25, 30, 2, 20, 100, 80, 40, 60};
    cout << "Original array: ";
    display<int>(b, 8);
    newline();
    heapSort<int>(b, 8);
    cout << "Sorted array: "; 
    display<int>(b, 8);
    newline();
    
}  // end main