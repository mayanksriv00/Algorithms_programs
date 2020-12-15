#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include <chrono> 
using namespace std::chrono; 
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
int main(int argc,char* argv[])
{
    //Handeling input and time
    fstream file_dec;
    long long int total_time=0;
    if(argc!=2)
        perror("Please enter the required format <filename in cpp> <input filename>");
    std::cout << "This is the quick sort algorithm implementation" << endl;
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
            sort_operation(abc,0,abc.size()-1);     
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