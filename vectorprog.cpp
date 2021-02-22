#include<iostream>
#include<vector>     //header for vector
#include<bits/stdc++.h>
using namespace std;

void show(vector <int> g)    //to print vector 
{ 
    vector <int> :: iterator it1;    //iterator it1 to traverse through the vector elements
    for(it1 = g.begin(); it1 != g.end(); ++it1) 
        cout << *it1; 
    cout << '\n'; 
} 

int main()
{
    vector<int> v;   //vector 1
    vector<int> v1;  //vector 2
    for(int i=1; i<=5; i++)
        v.push_back(i);    //insert 5 elements into vector 1
    for(auto i=v.begin(); i!=v.end(); i++)      //i iterates from the begining of vector to the end of vector
        cout <<*i <<" ";
        cout <<"\n";
    for(auto i=v.rbegin(); i!=v.rend(); i++)    //i iterates from the end of vector to the begining of vector
        cout <<*i <<" ";
        cout <<"\n";
    for(auto ir=v.cbegin(); ir!=v.cend(); ir++)
        cout <<*ir <<" ";
        cout <<"\n";
    for(auto ir=v.crbegin(); ir!=v.crend(); ir++)
        cout <<*ir <<" ";
        cout <<"\n";

    v1.assign(5,50);      //assign "50" 5 times into vector 2
    for(auto i=0; i<v1.size(); i++)
        cout <<v1[i];
    cout <<"\n";
    cout <<v1.at(2) <<"\n";    //points out the 2nd element
    cout <<v1.back() <<"\n";   //points out last element
    cout <<v1.front() <<"\n";  //points out first element
 
    cout <<v1.size() <<"\n";   
    cout <<v1.max_size() <<"\n";
    cout <<v1.capacity() <<"\n";
    v1.resize(4);               //vector size is reduced from 5 to 4
    cout <<v1.size() <<"\n";

    if(v1.empty()==true)
        cout <<"vector is empty" <<"\n";
    else
        cout <<"vector is not empty" <<"\n";

    v1.shrink_to_fit(); 
    for (auto it = v1.begin(); it != v1.end(); it++) 
        cout << *it;
        cout <<"\n";

    cout <<v1[2] <<"\n";    //points out the 2nd element
    int *p=v1.data();       //points out the first element
    cout <<*p <<"\n";

    v1.push_back(10);
    int n=v1.size();
    cout<< v1[n-1] <<"\n";
    show(v1);

    v1.pop_back();
    show(v1);
    
    v1.insert(v1.begin(),10);
    cout <<v1[0] <<'\n';

    v1.erase(v1.begin());
    cout <<v1[0] <<"\n";

    v1.emplace(v1.begin(),20);    
    cout <<v1[0] <<'\n';
    v1.emplace_back(20);
    show(v1);

    v.swap(v1);
    show(v);
    show(v1);

    v1.clear();
    cout <<v1.size();

    return 0;
}