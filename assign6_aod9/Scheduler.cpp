// File Name: scheduler.cpp
//
// Author: Andrew Daly
// Date: 04/29/2020
// Assignment Number: 6
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko

#include "Scheduler.h"

// Functions that will be called in
// SchedulerMain.cpp.

// Function Definitions:


//***********************************************************
// add:   Add the given pending process to the queue
// toDo - the current pending process
//***********************************************************

void Scheduler::add(PendingProcess toDo)
{
	queued.push(toDo);
}

//***********************************************************
// next:    remove a process from the top of the queue and
//		    reduce time remaining by a sec
// returns: the name of the process scheduled to run
//***********************************************************

string Scheduler::next()
{
	PendingProcess obj = queued.front();
	queued.pop();

	if (obj.timeRemaining > 1)
	{
		obj.timeRemaining--;
		queued.push(obj);
	}
	return obj.name;
}

//***********************************************************
// empty:   check if the queue is empty or not
// returns: return flase if the queue is empty, else, true.
//***********************************************************

bool Scheduler::empty()
{
	if (queued.empty()) 
		return false;
	else 
		return true;
}