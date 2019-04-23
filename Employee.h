//Employee.h

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

static int next_id;

class Employee {
public:
	//constructors
	Employee(std::string _name, std::string _email);
	Employee(const std::string& fileName);

    /**
    prints employee data
    */
	void print() const;

    /**
    writes employee data to a file named after their ID
    */
	virtual void write_data() const;

    /**
    pure virtual function, will be used in derived classes to print wage/salary information
    */
	virtual void print_pay() const = 0;

    /**
    pure virtual function, will be used in derived classes to update employee file with new data
    */
	virtual void save() const = 0;

    
private:
    std::string name;
    std::string email;
    int id;
}