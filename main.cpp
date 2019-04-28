//main.cpp

#include "Company.h"
#include<iostream>
#include<string>

int main() {
	Company company = Company();
	company.print_directory();
	company.do_hours();
	
	std::cin.get();
	
	return 0;
}