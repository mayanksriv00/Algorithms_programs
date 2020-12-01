#include<iostream>
#include<vector>
using namespace std;
void heapify_operation(vector<long long int>& array,long long int size,long long int index)
{
    long long int greatest=index;       //setting root as the largest value
    long long int left=2*index+1;       //left child
    long long int right=2*index+2;      //right child

    //checking if the left child is greater than the root value
    if(left<size && array[left]>array[greatest])
        greatest=left;
    
    //checking if the right child is greater than the root value
    if(right<size && array[right]>array[greatest])
        greatest=right;

    //Means greatest value is not root then swap
    if(greatest!=index)
    {
        swap(array[index],array[greatest]);         //swap elements
        heapify_operation(array,size,greatest);     //for sub-section of tree
    }
}
void display(vector<long long int>& array)
{
    for(long long int index=0;index<array.size();index++)
        cout<<array[index]<<" ";
    cout<< endl;
}
void heap_sort_operation(vector<long long int>& array,int size)
{
    for(long long int index=size/2-1;index>=0;index--)      //non leaf elements
        heapify_operation(array,size,index);
    for(long long int index=size-1;index>0;index--)         //remove elements one by one
    {
        swap(array[0],array[index]);
        heapify_operation(array,index,0);
    }
}
int main(){
    std::cout << "This is the Instertion sort algorithm implementation" << endl;
    //have to incorporate file and timer here
    long long int n;
    vector<long long int> abc;
    cout << "Enter the size" << endl;
    cin >> n;
    cout << "Enter the elements in an array" << endl;
    for (long long int i = 0; i < n; i++)
    {
        long long int x = 0;
        cin >> x;
        abc.push_back(x);
    }
    heap_sort_operation(abc,n);
    display(abc);
}