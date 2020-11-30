// Insertion sort
#include <iostream>
#include<vector>
using namespace std;
vector<int> insertion_sort(vector<int>& array)
{
    int insert_key, index2;
    for (int index1 = 1; index1 < array.size(); index1++)
    {
        insert_key = array[index1]; index2 = index1;
        while (index2 > 0 && array[index2 - 1] > insert_key)
        {
            array[index2] = array[index2 - 1];
            index2--;
        }
        array[index2] = insert_key;
    }
    return array;
}
void display(vector<int>& array)
{
    cout << "Output is" << endl;
    for (int i = 0; i < array.size(); i++)
        cout << array[i] << " ";
}
int main()
{
    std::cout << "This is the Instertion sort algorithm implementation" << endl;
    //have to incorporate file and timer here
    int n;
    vector<int> abc;
    cout << "Enter the size" << endl;
    cin >> n;
    cout << "Enter the elements in an array" << endl;
    for (int i = 0; i < n; i++)
    {
        int x = 0;
        cin >> x;
        abc.push_back(x);
    }
    insertion_sort(abc);
    display(abc);
}
