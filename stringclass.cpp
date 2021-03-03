#include<iostream> 
#include<string> // for string class 

using namespace std; 

int main() 
{ 
    // Declaring string 
    string str; 
    string str1 = "This is a pleasant day";
    string str2 = "Have a good day";
    string str3 = "How are you?";
    string::iterator it; 
    string::reverse_iterator it1;

    char ch[50]; 
  
    // Taking string input using getline() 
    cout << "enter the string : ";
    getline(cin,str); 
  
    // Displaying string 
    cout << "The initial string is : "; 
    cout << str << endl; 
  
    // Using push_back() to insert a character at the end
    str.push_back('s'); 
  
    // Displaying string 
    cout << "The string after push_back operation is : "; 
    cout << str << endl; 
  
    // Using pop_back() to delete a character from the end
    str.pop_back(); 
  
    // Displaying string 
    cout << "The string after pop_back operation is : "; 
    cout << str << endl; 

    str1.resize(13); 
  
    // Displaying string 
    cout << "The string after resize operation is : "; 
    cout << str1 << endl; 
  
    // Displaying capacity of string 
    cout << "The capacity of string is : "; 
    cout << str1.capacity() << endl; 
  
    //Displaying length of the string 
    cout<<"The length of the string is :" << str1.length() << endl; 
  
    // Decreasing the capacity of string using shrink_to_fit() 
    str1.shrink_to_fit(); 
  
    // Displaying string 
    cout << "The new capacity after shrinking is : "; 
    cout << str1.capacity() << endl; 

    for (it=str2.begin(); it!=str2.end(); it++) 
    cout << *it; 
    cout << endl;

    for (it1=str2.rbegin(); it1!=str2.rend(); it1++) 
    cout << *it1; 
    cout << endl;

    str2.copy(ch,15,0); 
  
    // Diplaying char array 
    cout << "The new copied character array is : "; 
    cout << ch << endl; 

    str2.swap(str3); 
  
    // Displaying strings after swapping 
    cout << "The 1st string after swapping is : "; 
    cout << str2 << endl; 
    cout << "The 2nd string after swapping is : "; 
    cout << str3 << endl; 
  
    return 0; 
  
} 