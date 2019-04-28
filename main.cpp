//main.cpp

#include "Company.h"
#include<iostream>
#include<string>

/**
next id function that loops through files to find next id for employee
@return: integer index of next id
*/
int find_next_id();

/**
run events function to prompt user for input and proceed accordingly
*/
void run_events();

int main() {
	run_events();
	std::cin.get();
	
	return 0;
}

