#include<iostream>
#include<vector>
using namespace std;

void swap_elements(long long int* elem1,long long int* elem2)
{
    int temp=*elem1;
    *elem1=*elem2;
    *elem2=temp;
}
long long int partition(vector<long long int>& array,int start,int end)
{
    long long int var_pivot=array[end];       //taking default pivot as the last element
    long long int index=(start-1);
    for(int index1=start;index1<=end-1;index1++)
    {
        if(array[index1]<var_pivot)
        {
            index++;
            swap_elements(&array[index],&array[index1]);
        }
    }
    swap_elements(&array[index+1],&array[end]);
    return (index+1);
}
void sort_operation(vector<long long int>& array,int start,int end)
{
    if(start<end)
    {
        long long int index=partition(array,start,end);
        sort_operation(array,start,index-1);
        sort_operation(array,index+1,end);
    }
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
    sort_operation(abc,0,abc.size()-1);
    display(abc);
}