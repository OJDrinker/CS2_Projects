// File Name: Scheduler.h
//
// Author: Andrew Daly
// Date: 04/29/2020
// Assignment Number: 6
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko

// This is a header file which consists
// Scheduler class. Queue of pending
// processes is set as its private field 
// 3 public methods: add, next and empty

#include <queue>
#include "PendingProcess.h"

class Scheduler
{
private:
	queue<PendingProcess> queued;
public:
	void add(PendingProcess toDo);
	string next();
	bool empty();
};
