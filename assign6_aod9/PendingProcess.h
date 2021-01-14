// File Name: PendingProcess.h
//
// Author: Andrew Daly
// Date: 04/29/2020
// Assignment Number: 6
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko


// This is a header file which consists
// a PendingProcess struct so it can
// hold two different data types
// and a public constructor with an
// initaizlier list.


#include <string>

using namespace std;

struct PendingProcess
{
public:
	string name;
	int timeRemaining;

	PendingProcess(string name, int timeRemaining) : 
		name(name), timeRemaining(timeRemaining) {}
};
