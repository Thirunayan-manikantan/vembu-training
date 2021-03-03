#include <iostream>
using namespace std;

// class Rectangle {
//   public:
//     // Variables required for area calculation
//     int length;
//     int breadth;

//     // Constructor to initialize variables
//     Rectangle(int len, int brth) : length(len), breadth(brth) {}

//     // Function to calculate area
//     int getArea()
//     {
//       return length * breadth;
//     }
// };

// int main() 
// {
//   // Create object of Rectangle class
//   Rectangle rect(2, 12);

//   // Call getArea() function
//   cout << "Area = " << rect.getArea();

//   return 0;
// }

class Rectangle 
{
   //data hiding 
   private:

    // Variables required for area calculation
    int length;
    int breadth;

   public:

    // Setter function for length
    void setLength(int len) 
    {
        if(len >= 0)
            length = len;
    }

    // Setter function for breadth
    void setBreadth(int brth) 
    {
        if(brth >= 0)
            breadth = brth;
    }

    // Getter function for length
    int getLength() 
    {
        return length;
    }

    // Getter function for breadth
    int getBreadth() 
    {
        return breadth;
    }

    // Function to calculate area
    int getArea() 
    {
        return length * breadth;
    }
};

int main() 
{
    // Create object of Rectangle class
    Rectangle rect;

    // Initialize length using Setter function
    rect.setLength(10);

    // Initialize breadth using Setter function
    rect.setBreadth(12);

    // Access length using Getter function
    cout << "Length = " << rect.getLength() << endl;

    // Access breadth using Getter function
    cout << "Breadth = " << rect.getBreadth() << endl;

    // Call getArea() function
    cout << "Area = " << rect.getArea();

    return 0;
}