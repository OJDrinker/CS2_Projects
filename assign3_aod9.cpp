// File Name: assign3_aod9.cpp
//
// Author: Andrew Daly
// Date: 03/05/2020
// Assignment Number: 3
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko
//
// This program is to implement and test the five functions that use pointers and dynamic memory allocation.
// The functions are:
// 1) rightCircularShift
// 2) sort2withSum
// 3) resize
// 4) concatenate
// 5) subArray (in which it will use duplicateArray function from the lecture sides for Unit 3)

#include <iostream>

using namespace std;

//Function Prototypes:
void printArray(int *arr, int SIZE);
void doubleSpace();
void rightCircularShift(int *arr, int SIZE);
int sort2withSum(int *, int *);
int* resize(int *arr, int SIZE);
int* concatenate(int* arr3, int* arr4, int SIZE3, int SIZE4);
int* subArray(int *arr, int start, int length);
int *duplicateArray (int *arr, int SIZE);

//Begins Program
int main () {

    // Each function will have its own test case and expected result
    // Please adjust them as needed and ensure expected result is correct as well

    // Test Case for rightCircularShift
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int SIZE1 = *(&arr1 + 1) - arr1;

    // Expected result
    int expectedArr1[] = {8, 1, 2, 3, 4, 5, 6, 7};

    cout << "Testing rightCircularShift: " << endl
         << "Test data array:            "; printArray(arr1, SIZE1); cout << endl
         << "Expected result:            "; printArray(expectedArr1, SIZE1); cout << endl
         << "Actual result:              ";
    
    rightCircularShift(arr1, SIZE1);
    printArray(arr1, SIZE1);

    doubleSpace();

    // Test Case for sort2withSum
    int a = 8,
        b = 5;
    
    // Expected result (that if a > b)
    int c = a + b;

    cout << "Testing sort2withSum        " << endl;
    cout << "Test data:                  " << "a: " << a << " b: " << b << endl;
    cout << "Expected result:            " << c << " a: " << a << " b: " << b << endl;
    cout << "Actual result:              ";
    
    int z = sort2withSum(&a, &b);
    cout << z <<" a: " << a << " b: " << b;

    doubleSpace();

    // Test Case for resize
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int SIZE2 = *(&arr2 + 1) - arr2;

    // Expected Result
    int expectedArr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    cout << "Testing resize              " << endl
         << "Test data:                  "; printArray(arr2, SIZE2); cout << endl
         << "Expected result:            "; printArray(expectedArr2, SIZE2 * 2); cout << endl
         << "Actual result:              ";
    
    int *num1 = resize(arr2, SIZE2);
    printArray(num1, SIZE2 * 2); // The resize function creates a new array twice the size of the argument array, 
                                 //hence SIZE is doubled.
    // Releasing memory
    delete [] num1;

    doubleSpace();

    // Test Case for concatenate
    int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int SIZE3 = *(&arr3 + 1) - arr3;

    int arr4[] = {11, 22, 33, 44, 55};
    int SIZE4 = *(&arr4 + 1) - arr4;

    // Expected Result
    int expectedArr3plus4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 11, 22, 33, 44, 55};

    cout << "Testing concatenate         " << endl
         << "Test data:                  "; printArray(arr3, SIZE3); cout << "and "; printArray(arr4, SIZE4); cout << endl
         << "Expected result:            "; printArray(expectedArr3plus4, SIZE3 + SIZE4); cout << endl
         << "Actual result:              ";

    int *num2 = concatenate(arr3, arr4, SIZE3, SIZE4);
    printArray(num2, SIZE3 + SIZE4); // The concatenate function creates a new array by combining the argument arrays, 
                                     //hence both of its SIZE are added.
    // Releasing memory
    delete [] num2;

    doubleSpace();

    // Test Case for subArray
    int start  = 5,
        length = 4;
    int arr5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int SIZE5 = *(&arr5 + 1) - arr5;

    // Expected result
    int expectedArr5[] = {6, 7, 8, 9};

    cout << "Testing subArray            " << endl
         << "Test data:                  "; printArray(arr5, SIZE5); cout << " start: " << start << " length: " << length << endl
         << "Expected result:            "; printArray(expectedArr5, length); cout << endl
         << "Actual result:              ";

    int *num3 = subArray(arr5, start, length);
    printArray(num3, length); // Prints the array starting at the index[start] and its SIZE is the length

    // Releasing memory
    delete [] num3;

    doubleSpace();

    return 0;
}
//Function Definitions:

//***********************************************************
// printArray: prints the array.
// *arr - pointing to the 0th element of the array used
// SIZE - number of elements in the array
//***********************************************************
void printArray(int *arr, int SIZE) {
    for(int i = 0; i < SIZE; i++)
        cout << arr[i] << " ";   
}
//***********************************************************
// doubleSpace: creates double space in the output.
//***********************************************************
void doubleSpace() {
    cout << endl << endl;
}
//***********************************************************
// rightCircularShift: shifts the array to the right.
// *arr - pointing to the 0th element of the array used
// SIZE - number of elements in the array
//***********************************************************
void rightCircularShift(int *arr, int SIZE) {
    int last = arr[SIZE - 1];
    int* ptr = arr;
    for( int i = SIZE - 1; i > 0; --i) {
         *(ptr + i) = *(ptr + i - 1);
    }
    *ptr = last;
}
//***********************************************************
// sort2withSum: using pointers which changes the values of
//               the variables passed into it
// *x: pointing to the address of the parameter
// *y: pointing to the address of the parameter
// returns: sum of those parameters
//***********************************************************
int sort2withSum(int *x, int *y){
    if (*x > *y) {
        int temp = *x;
        *x = *y;
        *y = temp;
    }
    return *x + *y;
}
//***********************************************************
// resize: creates a new array twice the size, copying the
//         argument array and filling the rest with -1
// *arr - pointing to the 0th element of the array used
// SIZE - number of elements in the array
// returns: array that is doubled in size, filled with first
//          array's elements and the rest with -1
//***********************************************************
int *resize(int* arr, int SIZE) {
    int* resize;
    resize = new int[SIZE * 2];

    for (int i = 0; i < SIZE ; i++)
        resize[i]=arr[i];

    for (int i = SIZE; i < SIZE * 2; i++)
        resize[i] = -1;

return resize;
}
//***********************************************************
// concatenate: merges two arrays into one
// *arr3 - pointing to the 0th element of the array used
// *arr4 - pointing to the 0th element of the array used
// SIZE3 - number of elements in the array
// SIZE4 - number of elements in the array
// returns: merged array
//***********************************************************
int *concatenate(int *arr3, int *arr4, int SIZE3, int SIZE4) {
    int* concatenate;
    concatenate = new int[SIZE3 + SIZE4];

    int i = 0, j = 0, k = 0;

    while(i < SIZE3 && j < SIZE4) {
        // If and else statments to sort elements
        if (arr3[i] < arr4[j])
            concatenate[k++] = arr3[i++];
        else
            concatenate[k++] = arr4[j++];
    }
    // Adding elements to new array
    while (i < SIZE3)
        concatenate[k++] = arr3[i++];
    while (j < SIZE4)
        concatenate[k++] = arr4[j++];
return concatenate;
}
//***********************************************************
// duplicateArray: copying an array
// *arr - pointing to the 0th element of the array used
// SIZE - number of elements in the array
// returns: a new array that copied an array
//***********************************************************
int *duplicateArray (int *arr, int SIZE) {
    int *newArray;
    if (SIZE <= 0)      // SIZE must be positive
        return NULL;    // NULL is 0, an invalid address

    newArray = new int[SIZE];   // allocate new array

    for (int index = 0; index < SIZE; index++)
        newArray[index] = arr[index];   // copy to new array

    return newArray;
}
//***********************************************************
// subArray: creates a new array that is a copy of the elements
//           from the orig. array starting at 'start' and has
//           SIZE of length
// *array - pointing to the 0th element of the array used
// start - index of the array
// length - numbers of elements to be printed
// returns: a cut up array which starts at 'start' and is
//          'length' long
//***********************************************************
int *subArray (int *array, int start, int length) {
    int *result = duplicateArray(array+start, length);
    return result;
}