// Merge sort
#include <iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include <chrono>

using namespace std::chrono; 
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
int main(int argc,char* argv[])
{
    //Handeling input and time
    fstream file_dec;
    long long int total_time=0;
    if(argc!=2)
        perror("Please enter the required format <filename in cpp> <input filename>");
    std::cout << "This is the merge sort algorithm implementation" << endl;
    file_dec.open(argv[1],ios::in);
    ofstream output_file_sort;
    output_file_sort.open("Results_sorted.txt",ios::out|ios::app);

    if(file_dec.is_open())
    {
        string text;
        int i=0;
        while (getline(file_dec,text))
        {
            stringstream ss(text);
            string mid;
            vector<long long int> abc;
            while(getline(ss,mid,' '))
            {  
                abc.push_back(stoll(mid,nullptr,10));
            }
            cout<<endl<<"Result: ";
            auto start = high_resolution_clock::now(); 
            merge_sort(abc,0,abc.size()-1);     
            auto stop = high_resolution_clock::now(); 
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time taken by function: "<< duration.count() << " microseconds" << endl; 
            cout<<"----------------------------------"<<endl;
            total_time+=duration.count();
            if(total_time>=7200000000)
            {
                cout<<"Taking more than 2 hrs time"<<endl;
                break;
            }
            //display(abc);         //This function will display data on screen
            //Storing sorted output in each file
            output_file_sort<<"Result=";
            for(long long int index=0;index<abc.size();index++)
                output_file_sort<<abc[index]<<" ";
            output_file_sort<<endl;
            
            abc.clear();
            i++;
        }
        output_file_sort<<"-------------------------------------------------------------------------"<<endl;
    }    
    //Storing rumtime for each instance result in a file
    ofstream output_file;
    output_file.open("Results_time.txt",ios::out|ios::app);
    output_file<<argv[1]<<" "<<total_time<<endl;

    output_file_sort.close();;
    output_file.close();
    file_dec.close();
    return 0;
}