//Heap sort
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include <chrono> 
using namespace std::chrono; 
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
int main(int argc,char* argv[]){
   
     //Handeling input and time
    fstream file_dec;
    long long int total_time=0;
    if(argc!=2)
        perror("Please enter the required format <filename in cpp> <input filename>");
    std::cout << "This is the Heap sort algorithm implementation" << endl;
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
            heap_sort_operation(abc,abc.size());     
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