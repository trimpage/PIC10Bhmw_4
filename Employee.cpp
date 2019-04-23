//Employee.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Employee {
public:
    Employee(std::string _name, std::string _email) : name(_name), email(_email) {}
    Employee(const std::string& fileName) {
        //create file object and open it
        std::ifstream inputFile;
        inputFile.open(fileName);

        //if file is unable to be opened, let user know, otherwise continue to parse data
        if (inputFile.fail()){
            std::cout << "File was unable to be opened.\n";
        }
        else {
            //line variable to be read
            std::string line;
            
            //grab line string while not at end of file
            while (!inputFile.eof()) {
                getline(inputFile, line);
            }

            //create and use stream to parse line data, store first string as employee type
            std::stringstream ss(line);
            std::string employeeType;
            ss >> employeeType >> name >> email >> id;
        }
    }

    /**
    prints employee data
    */
    void print() const {
        std::cout << name << '\t' << id << '\t' << email << '\n';
    }

    /**
    writes employee data to a file named after their ID
    */
    virtual void write_data() const {
        //construct file name using employee id
        std::string fileName = "employee";
        fileName += std::to_string(id);
        fileName += ".txt";

        //create file and output employee data to it
        std::ofstream outputFile;
        outputFile.open(fileName);
        outputFile << name << '\t' << email << 't' << id << '\n';
    }

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
    static int next_id;
}