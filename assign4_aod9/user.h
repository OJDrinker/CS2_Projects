// File Name: user.h
//
// Author: Andrew Daly
// Date: 04/08/2020
// Assignment Number: 4
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko
//
// The User class
// This class manages a single password for a given username
// Class declaration (specification) in a separate file

#include <string>
#include <vector>

using namespace std;

class User
{
private:
	string userName;
	unsigned long long hash(string);
	unsigned long long passwordHash;
	bool meetsCriteria(string);
public:
	User (string userName, unsigned long long passwordHash) : userName(userName), passwordHash(passwordHash) {}
	void setUsername(string);
	string getUsername() const;
	void setPasswordHash(unsigned long long);
	unsigned long long getPasswordHash() const;
	bool setNewPassword(string);
	bool authenticate(string);
};