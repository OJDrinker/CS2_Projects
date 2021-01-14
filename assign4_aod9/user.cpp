// File Name: user.cpp
//
// Author: Andrew Daly
// Date: 04/08/2020
// Assignment Number: 4
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko
//
// The User class
// Member function definitions (implementation) in a separate file

#include <string>
#include <iostream>
#include <sstream>
#include "user.h"

using namespace std;

//***********************************************************
// hash: This private function takes a password(a string)
//       and returns the encrypted form of the password
// s - password
// return - encrypted password
//***********************************************************
unsigned long long User::hash(string s)
{
    unsigned long long h = 0;
    for (int i = 0; i < s.size(); i++) {
        h = s[i] + (h << 6) + (h << 16) - h;
    }
    return h;
}


//***********************************************************
// meetsCriteria: This private function takes a string (a password)
//                and returns true if it meets the criteria.*
// s - password
// return - either true or false based on criteria being met
//***********************************************************
bool User::meetsCriteria(string s)
{
    bool upper_ping = 0, lower_ping = 0, digit_ping = 0;
    if (s.length() < 8)
        return false;
    else
        for (int index = 0; index < s.length(); index++)
        {
            if (isupper(s[index]))
                upper_ping = 1;
            if (islower(s[index]))
                lower_ping = 1;
            if (isdigit(s[index]))
                digit_ping = 1;
        }
    if (upper_ping && lower_ping && digit_ping)
        return true;
    else
        return false;
}


//***********************************************************
// setUsername: A setter function: this member function takes
//              a string and stores it in the proper menber variable.
// name - string
//***********************************************************
void User::setUsername(string name)
{
    userName = name;
}

//***********************************************************
// getUsername: A getter function: this member function returns
//              the value of the proper member variable.
// return - userName
//***********************************************************
string User::getUsername() const
{
    return userName;
}

//***********************************************************
// setPasswordHash: A setter function: this member function takes a 
//                  unsigned long long int pw(encrypted password) 
//                  and stores it in the proper member variable.
// s - encrypted password
//***********************************************************
void User::setPasswordHash(unsigned long long pw)
{
    passwordHash = pw;
}

//***********************************************************
// getPasswordHash: A getter function: this member function returns the
//                  value of the encrypted password stored in the proper
//                  member variable.
// s - encrypted password
// return - encrypted password
//***********************************************************
unsigned long long User::getPasswordHash() const
{
    return passwordHash;
}

//***********************************************************
// setNewPassword: This member function takes a string (a proposed,
//                 unencrypted, password).If it meets the criterria
//                 in meetsCriteria, it encrypts the password
//                 and stores it in the member variable and
//                 returns true. Otherwise returns false.
// s - encrypted password
// return - either true or flase
//***********************************************************
bool User::setNewPassword(string s)
{
    if (meetsCriteria(s))
    {
        passwordHash = hash(s);
        return true;
    }
    else
        return false;
}

//***********************************************************
// authenticate: This member function takes a string(a password)
//               and returns true if, once encrypted, it matches
//               the encrypted string stored in the member variable.
//               Else returns false.
// s - encrypted password
// return - either true or flase
//***********************************************************
bool User::authenticate(string s)
{
    if (hash(s) == passwordHash)
        return true;
    else
        return false;
}