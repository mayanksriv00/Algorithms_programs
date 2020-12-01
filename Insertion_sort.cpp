// Insertion sort
#include <iostream>
#include<vector>
using namespace std;
void insertion_sort(vector<long long int>& array)
{
    long long int insert_key, index2;
    for (long long int index1 = 1; index1 < array.size(); index1++)
    {
        insert_key = array[index1]; index2 = index1;
        while (index2 > 0 && array[index2 - 1] > insert_key)
        {
            array[index2] = array[index2 - 1];
            index2--;
        }
        array[index2] = insert_key;
    }
}
void display(vector<long long int>& array)
{
    cout << "Output is" << endl;
    for (long long int i = 0; i < array.size(); i++)
        cout << array[i] << " ";
    cout << endl;
}
int main()
{
    std::cout << "This is the Instertion sort algorithm implementation" << endl;
    //have to incorporate file and timer here
    int n;
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
    insertion_sort(abc);
    display(abc);
}
