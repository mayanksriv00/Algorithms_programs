#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;
int main(int argc,char* argv[])
{
    fstream file_dec;
    if(argc!=2)
        perror("Please enter the required format <filename in cpp> <input filename>");
    file_dec.open(argv[1],ios::in);
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
            cout<<endl<<i<<" "<<abc.size() <<endl;
            for(int i=0;i<abc.size();i++)
                cout<<i<<"::"<<abc[i]<<" ";
            abc.clear();
            i++;
        }
    }
    file_dec.close();
    return 0;
}