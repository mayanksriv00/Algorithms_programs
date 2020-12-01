// Insertion sort
#include <iostream>
#include<vector>
using namespace std;
void merge(vector<long long int>& array, long long int start,long long int mid,long long int end)
{
    long long int size1 = mid - start + 1;
    long long int size2 = end - mid;
    vector<long long int> first_half(size1);
    vector<long long int> second_half(size2);

    //Since merge sort take extra memory
    for (long long int index = 0; index < size1; index++)
    {
        first_half[index] = array[start + index];
    }
    for (long long int index = 0; index < size2; index++)
    {
        second_half[index] = array[mid + index + 1];
    }
    //merging data to the original array
    long long int index_first_Array = 0, index_second_array = 0, index_original_array = start;
    while (index_first_Array < size1 && index_second_array < size2)
    {
        if (first_half[index_first_Array] <= second_half[index_second_array])
        {
            array[index_original_array] = first_half[index_first_Array];
            index_first_Array++;
        }
        else
        {
            array[index_original_array] = second_half[index_second_array];
            index_second_array++;
        }
        index_original_array++;
    }
    //have to copy the remaining elements if the size of two array are not same
    while (index_first_Array < size1)
    {
        array[index_original_array] = first_half[index_first_Array];
        index_original_array++;
        index_first_Array++;
    }
    while (index_second_array < size2)
    {
        array[index_original_array] = second_half[index_second_array];
        index_original_array++;
        index_second_array++;
    }
}
void merge_sort(vector<long long int>& array,long long int start,long long int end)
{
    if (start >= end)
        return;
    long long int mid = start + (end - start) / 2;
    merge_sort(array, start, mid);
    merge_sort(array, mid + 1, end);
    merge(array, start, mid, end);
    
}
void display(vector<long long int>& array)
{
    cout << "Output is" << endl;
    for (int i = 0; i < array.size(); i++)
        cout << array[i] << " ";
    cout<<endl;
}
int main()
{
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
    merge_sort(abc,0,abc.size()-1);
    display(abc);
}