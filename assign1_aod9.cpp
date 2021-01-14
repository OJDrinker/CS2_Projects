// File Name: assign1_aod9.cpp
//
// Author: Andrew Daly
// Date: 02/05/2020
// Assignment Number: 1
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko
//
// This program is to process flight database which is in a CSV file and to:
// 1) display the database in a readable format
// 2) show flights that depart from a given city
// 3) find the flight with the best distance to price ratio

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Making a structure so it can hold two different data types
// that can be accessed anytime
// |departure|arrival|price|distance|

struct Flights
{
    string departure,
           arrival;
    double price,
           distance;
};

//Function Prototypes:
int readFlights(ifstream& in, Flights list[]);
void printFlights(Flights list[], int SIZE);
void printFlightsFrom(Flights list[], int SIZE, string departureCity);
double findHighestDistanceToPriceRatio(Flights list[], int SIZE, int &flightIndex);

// Max number of flights to be processed
const int MAXSIZE = 100;

//Begins Program
int main() {
    ifstream in;
    in.open("flights.csv");

    //Error message if input file failed to open
    if ( !in )
    {
        cout << endl << endl
             << " ***Program Terminated.*** " << endl << endl
             << "Input file failed to open." << endl;

             return 1;
    }

    // Initalizing
    Flights list[MAXSIZE];
    const int SIZE = readFlights(in, list); // constant numeric value for size of the array
    string departureCity; // setting the user's input as string for opinion 2
    int flightIndex = 0; // numeric value for an index in the array, will being passed as reference
    int user_input = 0; // default numeric value for menu opinions

    // Program begins by asking for user's input
    do {

        cout << "Select the action:" << endl
             << "1) Display all flights" << endl
             << "2) Show the flights that depart from a given city" << endl
             << "3) Find a flight with the best distance to price ratio" << endl
             << "4) Exit the program" << endl;

        cin >> user_input;

        // Execute the block of code associated with the user's input
        switch (user_input)
        {
            case 1: printFlights(list, SIZE);
                    cout << endl;
                    break;
            case 2: cout << "Please enter the city of departure " << endl;
                    cin.ignore();
                    getline(cin, departureCity);
                    printFlightsFrom(list, SIZE, departureCity);
                    break;
            case 3: cout << "The best distance to price ratio is "
                         << fixed << setprecision(2) << findHighestDistanceToPriceRatio(list, SIZE, flightIndex)
                         << setprecision(0) << " km/$" << endl
                         << left << setw(17) << list[flightIndex].departure
                         << setw(13) << list[flightIndex].arrival
                         << setw(5) << list[flightIndex].price
                         << list[flightIndex].distance << endl << endl;
                    break;
            case 4: cout << "Exiting the program" << endl;
                    break;
            default:
                    cout << "Invalid input" << endl << endl;
        }
    }while( user_input !=4); 
    in.close();
    return 0;
}

//Function Definitions:

//***********************************************************
// readFlights: read the .csv file with flights and 
//              return a size of an array.
// in - input file
// list - the array of flights information
// returns: size of an array
//***********************************************************

int readFlights(ifstream& in, Flights list[]){
    Flights flight; // calling in Flights structure
    string tempStr; // temporary placeholder
    int size = 0; // numeric value for size of the array
    while(getline(in,list[size].departure,',') )
    {
        getline(in,list[size].arrival,',');
        getline(in,tempStr,',');
        list[size].price = stoi(tempStr);
        getline(in,tempStr);
        list[size].distance = stoi(tempStr);
        size++;
    }
    return size;
}

//***********************************************************
// printFlights: prints the array.
// list - the array of flights information
// SIZE - number of flights in the array
//***********************************************************

void printFlights(Flights list[], int SIZE){
    for(int i=0; i < SIZE; i++)
    {
        cout << left << setw(17) << list[i].departure
             << setw(13) << list[i].arrival
             << setw(5) << list[i].price
             << list[i].distance << endl;
    }
}

//***********************************************************
// printFlightsFrom: prints flights from the given city
// list - the array of flights information
// SIZE - number of flights in the array
// departureCity - user's input of city to fly from
//***********************************************************

void printFlightsFrom(Flights list[], int SIZE, string departureCity){
    int y = 0; // numeric value for y which will trigger a message if
               // it equals to SIZE, meaning the search failed
    for(int x=0; x < SIZE; x++){
        if(departureCity == list[x].departure){
            cout << left << setw(17) << list[x].departure 
                 << setw(13) << list[x].arrival
                 << setw(5) << list[x].price 
                 << list[x].distance << endl;
        }
        else{
            y++;
            if(y == SIZE){
            cout << "Flight(s) not found, please press 2 and try again" << endl;
            }
        
        }
    }
    cout << endl;
}

//***********************************************************
// findHighestDistanceToPriceRatio: finds the highest distance
//                                  to price ratio.
// list - the array of flights information
// SIZE - number of flights in the array
// flightIndex - an index of the array being passed by reference
// returns: highest distance to price ratio
//***********************************************************

double findHighestDistanceToPriceRatio(Flights list[], int SIZE, int &flightIndex){
    double ratio; // rational value for highest distance to price of a flight
    ratio = (list[flightIndex].distance / list[flightIndex].price);
    for(int y=0; y < SIZE; y++)
    {
        if((list[y].distance / list[y].price) > ratio ){
            ratio = (list[y].distance / list[y].price);
            flightIndex = y;
        }
    }
    return ratio;
 }