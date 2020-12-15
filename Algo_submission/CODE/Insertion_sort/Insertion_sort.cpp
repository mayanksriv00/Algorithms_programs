// Insertion sort
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include <chrono> 
using namespace std::chrono; 
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
int main(int argc,char* argv[])
{
    //Handeling input and time
    fstream file_dec;
    long long int total_time=0;
    if(argc!=2)
        perror("Please enter the required format <filename in cpp> <input filename>");
    std::cout << "This is the Instertion sort algorithm implementation" << endl;
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
            insertion_sort(abc);      
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
