// File Name: assign1_aod9.cpp
//
// Author: Andrew Daly
// Date: 02/05/2020
// Assignment Number: 1
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko
//
// This program is to process restaurants database which is in a CSV file and to:
// 1) be sorted by name
// 2) be sorted by ranking
// 3) find a restaurant by name
// 4) find the best restauarant with a given prices

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>

using namespace std;

// Making a structure so it can hold three different data types
// that can be accessed anytime
// |Name|City|Ranking|Rating|Price Range|Reviews|

struct Restaurants
{
    string name,
           city,
           range;
    int ranking,
        reviews;
    double rating;
};

//Function Prototypes:
int readRestaurants(ifstream& in, Restaurants list[]);
void printRestaurants(Restaurants list[], int SIZE);
void sortRestaurantsByRanking(Restaurants list[], int SIZE);
void sortRestaurantsByName(Restaurants list[], int SIZE);
int binarySearchName(Restaurants list[], int SIZE, string name);
bool isInPriceRange(string priceRange, string targetPrice);
int findBestRestaurantWithPrice(Restaurants list[], int SIZE, string targetPrice);

// Max number of flights to be processed
const int MAXSIZE = 100;
// constant string to be used later in the program
const string priceRange = "$ $$ - $$$ $$$$";

//Begins Program
int main() {
    ifstream in;
    in.open("restaurants.csv");

    // to ignore first line of input file
    in.ignore(500,'\n');

    //Error message if input file failed to open
    if ( !in )
    {
        cout << endl << endl
             << " ***Program Terminated.*** " << endl << endl
             << "Input file failed to open." << endl;

             return 1;
    }

    // Initalizing
    Restaurants list[MAXSIZE];
    const int SIZE = readRestaurants(in, list);
    string name,
           targetPrice,
           isInPriceRange;
    int index = 0;
    
    int user_input = 0; // default numeric value for menu opinions

    // Program begins by asking for user's input
    do {

        cout << "Select the action:" << endl
             << "1) Show restaurants sorted by Name" << endl
             << "2) Show resturants sorted by Ranking" << endl
             << "3) Find a resturant by name" << endl
             << "4) Find the best restaurant with a price" << endl
             << "5) Exit the program" << endl;

        cin >> user_input;

        // Execute the block of code associated with the user's input
        switch (user_input)
        {
            case 1: sortRestaurantsByName(list, SIZE);
                    printRestaurants(list, SIZE);
                    cout << endl;
                    break;
            case 2: sortRestaurantsByRanking(list, SIZE);
                    printRestaurants(list, SIZE);
                    cout << endl;
                    break;
            case 3: cout << "Please enter a resturant name: " << endl;
                    cin.ignore();
                    getline(cin, name);
                    sortRestaurantsByName(list, SIZE);
                    index = binarySearchName(list, SIZE, name);
                    if(index == -1) {
                        cout << "Restaurants not found. Please try again." << endl;
                    }
                    else {
                    cout << left << setw(24) << "Name"
                         << setw(11) << "City"
                         << setw(8) << "Ranking"
                         << setw(8) << "Rating" 
                         << setw(12) << "Price Range"
                         << setw(8) << "Reviews" << endl;

                    cout << left << setw(24) << list[index].name
                         << setw(11) << list[index].city
                         << setw(8) << list[index].ranking
                         << setw(8) << list[index].rating 
                         << setw(12) << list[index].range
                         << setw(8) << list[index].reviews << endl;
                    }
                    break;
            case 4: cout << "Please enter a price ($, $$, $$$ or $$$$)." << endl;
                    cout << priceRange << endl;
                    cin >> targetPrice;
                    sortRestaurantsByRanking(list, SIZE);
                    index = findBestRestaurantWithPrice(list, SIZE, targetPrice);
                    if(index == -1) {
                        cout << "Invalid input. Please try again." << endl;
                    }
                    else {
                    cout << left << setw(24) << "Name"
                         << setw(11) << "City"
                         << setw(8) << "Ranking"
                         << setw(8) << "Rating" 
                         << setw(12) << "Price Range"
                         << setw(8) << "Reviews" << endl; 
                    
                    cout << left << setw(24) << list[index].name
                         << setw(11) << list[index].city
                         << setw(8) << list[index].ranking
                         << setw(8) << list[index].rating 
                         << setw(12) << list[index].range
                         << setw(8) << list[index].reviews << endl;
                    }
                    break;
            case 5: cout << "Exiting the program" << endl;
                    break;
            default:
                    cout << "Invalid input" << endl << endl;
        }
    }while( user_input !=5); 
    in.close();
    return 0;
}    

//Function Definitions:

//***********************************************************
// readRestauarants: read the .csv file with restaurants and 
//              return a size of an array.
// in - input file
// list - the array of restauarnts information
// returns: size of an array
//***********************************************************

int readRestaurants(ifstream& in, Restaurants list[]) {
Restaurants restaurants; // calling in Restaurants structure
string tempStr; // temporary placeholder
int size = 0; // numeric value for size of the array
while(getline(in,list[size].name,',') )
    {
        getline(in,list[size].city,',');
        getline(in,tempStr,',');
        list[size].ranking = stoi(tempStr);
        getline(in,tempStr,',');
        list[size].rating = stod(tempStr);
        getline(in,list[size].range, ',');
        getline(in, tempStr);
        list[size].reviews = stoi(tempStr);
        size++;
    }
    return size;
}

//***********************************************************
// printRestaurants: prints the array.
// list - the array of restaurants information
// SIZE - number of restaurants in the array
//***********************************************************

void printRestaurants(Restaurants list[], int SIZE) {
        cout << left << setw(24) << "Name"
             << setw(11) << "City"
             << setw(8) << "Ranking"
             << setw(8) << "Rating" 
             << setw(12) << "Price Range"
             << setw(8) << "Reviews" << endl;

    for(int i = 0; i < SIZE; i++)
    {
        cout << left << setw(24) << list[i].name
             << setw(11) << list[i].city
             << setw(8) << list[i].ranking
             << setw(8) << list[i].rating 
             << setw(12) << list[i].range
             << setw(8) << list[i].reviews << endl;
    }
}

//***********************************************************
// sortRestaurantsByRanking: sort restaurants ranking into ascending order
// list - the array of restaurants information
// SIZE - number of restaurants in the array
//***********************************************************

void sortRestaurantsByRanking(Restaurants list[], int SIZE) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < (SIZE-1); i++) {

            if(list[i].ranking > list[i+1].ranking) {
                swap(list[i].ranking, list[i+1].ranking);
                swap(list[i].reviews, list[i+1].reviews);
                swap(list[i].name, list[i+1].name);
                swap(list[i].city, list[i+1].city);
                swap(list[i].range, list[i+1].range);
                swap(list[i].rating, list[i+1].rating);
                swapped = true;
            }
        }
    } while (swapped);
}

//***********************************************************
// sortRestaurantsByName: sort restaurants name into ascending order
// list - the array of restaurants information
// SIZE - number of restaurants in the array
//***********************************************************

void sortRestaurantsByName(Restaurants list[], int SIZE) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < (SIZE-1); i++) {
            if(strcmp(list[i].name.c_str(), list[i+1].name.c_str()) > 0) {
                swap(list[i].ranking, list[i+1].ranking);
                swap(list[i].reviews, list[i+1].reviews);
                swap(list[i].name, list[i+1].name);
                swap(list[i].city, list[i+1].city);
                swap(list[i].range, list[i+1].range);
                swap(list[i].rating, list[i+1].rating);   
                swapped = true;
            }
        }
    } while (swapped);
}

//***********************************************************
// binarySearchName: search restaurants name with given user input
// SIZE - number of restaurants in the array
// name - user input
// return - an index if found, or -1 if not found
//***********************************************************

int binarySearchName(Restaurants list[], int SIZE, string name) {
    int first = 0,
        last = SIZE - 1,
        middle,
        position = -1;
    bool found = false;

    while (first <= last && !found) {
        middle = (first + last) / 2;

        if (list[middle].name == name) {
            found = true;
            position = middle;
        }   else if (name < list[middle].name) {
            last = middle -1;
        }   else {
            first = middle + 1;
        }
    }
    return position;
}

//***********************************************************
// isInPriceRange: determines if user input can be found inside of
//                 a initalized string
// priceRange - initalized string
// targetPrice - user input
// return - either true or false
//***********************************************************

bool isInPriceRange(string priceRange, string targetPrice) {
    if(priceRange.compare(0, 1, targetPrice) == 0)
    {
        return true;
    }
    else if(priceRange.compare(11, 4, targetPrice) == 0)
    {
        return true;
    }
    else if(priceRange.compare(2, 8, "$$ - $$$") == 0)
    {
        if(targetPrice.compare("$$") == 0 || (targetPrice.compare("$$$") == 0))
        return true;
    }
    
    return false;
}   


//***********************************************************
// findBestRestaurantWithPrice: determines best resturant with
//                              user input of price
// list - the array of restaurants information
// SIZE - number of restaurants in the array
// targetPrice - user input
// return - an index if found, or -1 if not found
//***********************************************************

int findBestRestaurantWithPrice(Restaurants list[], int SIZE, string targetPrice) {
    int position = -1;
    bool found = false;
    if (isInPriceRange(priceRange, targetPrice) == 1){
        if (targetPrice == "$$" || targetPrice == "$$$")
            targetPrice = "$$ - $$$";

        for (int i=0; i < SIZE && !found; i++)
        {
            if (list[i].range == targetPrice)
            {
                found = true;
                position = i;
            }
        }   
    return position;
    }
    else
    {
        return position;
    }
    
}