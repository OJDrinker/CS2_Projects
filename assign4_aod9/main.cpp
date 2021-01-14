// File Name: main.cpp
//
// Author: Andrew Daly
// Date: 04/08/2020
// Assignment Number: 4
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko
//
// The User class

/*This main function reads data from a file, and uses those data
to set the usernames and passwords in the password manager class array.
This program lets users enter their username, old password and new
password. This program outputs three new encrypted passwords
to the file "userDatabase.txt */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "user.h"
using namespace std;

vector<User> loadUserDatabase(istream& in);

vector<User> userDatabase(string userName, unsigned long long passwordHash);

void saveUserDatabase(ofstream& of, vector <User> userDatabase);

int main()
{
    int SIZE;

    ifstream in;
    in.open("userDatabase.txt"); // Open file

    if (!in)// Exit with an error massage if the file doesn't exist
        cout << "ERROR - File failed to open. make sure that "
        << "the input file and this file are in the"
        << "same directory" << endl;

    vector<User> userDatabase = loadUserDatabase(in);

    SIZE = userDatabase.size();

    in.close(); // Close file

    string testName; // Store username that user enters
    string oldPassword; // Store old password that user enters
    string newPassword; // Store new password that user enters

    // Ask user to enter their userName, old password and new password
    cout << "Please enter your username: ";
    cin >> testName;
    cout << "Please enter your old password: ";
    cin >> oldPassword;
    cout << "Please enter your new password: ";
    cin >> newPassword;

    int ping = 0; // ping to see if userName is valid
    for (int i = 0; i < SIZE; i++)
    {
        if(testName != userDatabase[i].getUsername())
            ping++;
    }

    if (ping == SIZE) //Test if userName is valid
    {
        cout << "User with the given name does not exist, password not changed." << endl;
    }

    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            // If user enters a valid username
            if (testName == userDatabase[i].getUsername())
            { // Test if old password is correct
                if (!userDatabase[i].authenticate(oldPassword))
                    cout << "Old password is incorrect, password not changed" << endl;
                else
                {
                    if (!userDatabase[i].setNewPassword(newPassword))
                        cout << "New Password does not meet criteria, password not changed" << endl;
                    else
                    {
                        userDatabase[i].setNewPassword(newPassword);
                        cout << "Password has been changed for user: "
                            << userDatabase[i].getUsername() << endl;
                    }
                }
                break;
            }
        }
    }

    ofstream of;
    of.open("userDatabase.txt"); // Open file

    saveUserDatabase(of, userDatabase);

    of.close(); // Close file

    return 0;
}

//***********************************************************
// loadUserDatabase: load a file
// in - the file used to be loaded
// found_SIZE - number of found restaurants
// return: vector of userDatabase
//***********************************************************

vector<User> loadUserDatabase(istream& in) {
    string userName;
    unsigned long long passwordHash;
    vector<User> userDatabase;

    while (in >> userName >> passwordHash)
        userDatabase.push_back(User(userName, passwordHash));

    return userDatabase;

}

//***********************************************************
// saveUserDatabase: update the file with user's new password
// of - the file to be updated
// userDatabase - vector array of usernames and passwords
// return: vector of userDatabase
//***********************************************************

void saveUserDatabase(ofstream& of, vector <User> userDatabase) {
    for (int i = 0; i < userDatabase.size(); i++)
        of << userDatabase[i].getUsername() << " "
        << userDatabase[i].getPasswordHash() << endl;
}