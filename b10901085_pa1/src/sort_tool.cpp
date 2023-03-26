// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int tmp,j;
    for(int i=1;i<data.size();i++){
        j = i-1;
        tmp = data[j+1];
        while(j>=0 && tmp<data[j]){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = tmp;
    }
    return;
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low<high){
        int middle = Partition(data,low,high);
        QuickSortSubVector(data,low,middle-1);
        QuickSortSubVector(data,middle+1,high);
    }
    return;
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int pivot  = data[high];
    int tmp;
    int i = low-1;
    for (int j = i+1;j<high;j++){
        if (data[j]<=pivot)
        {
            tmp = data[j];
            data[j] = data[++i];
            data[i] = tmp;
        }
    }
    tmp = data[++i];
    data[i] = data[high];
    data[high] = tmp;
    return i;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low<high){
        int mid = (low+high)/2;
        MergeSortSubVector(data,low,mid);
        MergeSortSubVector(data,mid+1,high);
        Merge(data,low,mid,mid+1,high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
	vector<int> lsub(data.begin()+low,data.begin()+middle1+1);
	vector<int> rsub(data.begin()+middle2,data.begin()+high+1);
	int fi = low;    
	int li = 0;
    int ri = 0;
    for(int i = low;i<=high;i++){
        if(li==lsub.size()) data[i] = rsub[ri++];
        else if(ri==rsub.size()) data[i] = lsub[li++];
        else data[i] = rsub[ri]<lsub[li]? rsub[ri++] : lsub[li++];
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int largesti = root;
    if(root*2+1<heapSize){
        if(data[largesti]<data[root*2+1]) largesti = root*2+1;
    }
    
    if(root*2+2<heapSize){
        if(data[largesti]<data[root*2+2]) largesti = root*2+2;
    }


    if(largesti != root){
        int tmp;
        tmp = data[root];
        data[root] = data[largesti];
        data[largesti] = tmp;
        MaxHeapify(data,largesti);    
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = heapSize/2; i >= 0; i--)
    {
        MaxHeapify(data,i);
    }
    
}
