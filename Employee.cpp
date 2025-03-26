#include "Employee.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>

// Constructors
Employee::Employee() 
    : code(0), day(0), month(0), year(0), grade('E'), 
      houseAllowance(false), conveyanceAllowance(false), 
      loan(0.0f), basicSalary(0.0f) {}

Employee::Employee(int code, const std::string& name, const std::string& address, 
                   const std::string& phone, int day, int month, int year, 
                   const std::string& designation, char grade, bool houseAllowance, 
                   bool conveyanceAllowance, float loan, float basicSalary)
    : code(code), name(name), address(address), phone(phone), 
      day(day), month(month), year(year), designation(designation), 
      grade(grade), houseAllowance(houseAllowance), 
      conveyanceAllowance(conveyanceAllowance), loan(loan), 
      basicSalary(basicSalary) {}

// Getters
int Employee::getCode() const { return code; }
std::string Employee::getName() const { return name; }
std::string Employee::getAddress() const { return address; }
std::string Employee::getPhone() const { return phone; }
int Employee::getDay() const { return day; }
int Employee::getMonth() const { return month; }
int Employee::getYear() const { return year; }
std::string Employee::getDesignation() const { return designation; }
char Employee::getGrade() const { return grade; }
bool Employee::getHouseAllowance() const { return houseAllowance; }
bool Employee::getConveyanceAllowance() const { return conveyanceAllowance; }
float Employee::getLoan() const { return loan; }
float Employee::getBasicSalary() const { return basicSalary; }

// Setters
void Employee::setCode(int code) { this->code = code; }
void Employee::setName(const std::string& name) { this->name = name; }
void Employee::setAddress(const std::string& address) { this->address = address; }
void Employee::setPhone(const std::string& phone) { this->phone = phone; }
void Employee::setJoiningDate(int day, int month, int year) { 
    this->day = day; 
    this->month = month; 
    this->year = year; 
}
void Employee::setDesignation(const std::string& designation) { this->designation = designation; }
void Employee::setGrade(char grade) { this->grade = grade; }
void Employee::setHouseAllowance(bool houseAllowance) { this->houseAllowance = houseAllowance; }
void Employee::setConveyanceAllowance(bool conveyanceAllowance) { this->conveyanceAllowance = conveyanceAllowance; }
void Employee::setLoan(float loan) { this->loan = loan; }
void Employee::setBasicSalary(float basicSalary) { this->basicSalary = basicSalary; }

// Methods
std::string Employee::getJoiningDateString() const {
    return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
}

float Employee::calculateHRA() const {
    return houseAllowance ? (0.05f * basicSalary) : 0.0f;
}

float Employee::calculateCA() const {
    return conveyanceAllowance ? (0.02f * basicSalary) : 0.0f;
}

float Employee::calculateDA() const {
    return 0.05f * basicSalary;
}

float Employee::calculatePF() const {
    return 0.02f * basicSalary;
}

float Employee::calculateLoanDeduction() const {
    return 0.15f * loan;
}

float Employee::calculateTotalAllowance() const {
    if (grade == 'E') {
        return 0.0f; // For grade E, allowances are calculated differently
    }
    return calculateHRA() + calculateCA() + calculateDA();
}

float Employee::calculateTotalDeduction() const {
    if (grade == 'E') {
        return calculateLoanDeduction();
    }
    return calculatePF() + calculateLoanDeduction();
}

float Employee::calculateNetSalary() const {
    if (grade == 'E') {
        return basicSalary - calculateLoanDeduction();
    }
    return basicSalary + calculateTotalAllowance() - calculateTotalDeduction();
}

void Employee::display() const {
    gotoxy(5, 5);
    std::cout << "Employee Code # " << code;
    gotoxy(5, 6);
    std::cout << "~~~~~~~~~~~~~";
    gotoxy(5, 7);
    std::cout << "Name         : " << name;
    gotoxy(5, 8);
    std::cout << "Address      : " << address;
    gotoxy(5, 9);
    std::cout << "Phone no.    : " << phone;
    gotoxy(5, 11);
    std::cout << "JOINING DATE";
    gotoxy(5, 12);
    std::cout << "~~~~~~~~~~~~";
    gotoxy(5, 13);
    std::cout << "Day   : " << day;
    gotoxy(5, 14);
    std::cout << "Month : " << month;
    gotoxy(5, 15);
    std::cout << "Year  : " << year;
    gotoxy(5, 17);
    std::cout << "Designation  : " << designation;
    gotoxy(5, 18);
    std::cout << "Grade        : " << grade;
    
    if (grade != 'E') {
        gotoxy(5, 19);
        std::cout << "House (y/n)    : " << (houseAllowance ? 'Y' : 'N');
        gotoxy(5, 20);
        std::cout << "Conveyance (y/n) : " << (conveyanceAllowance ? 'Y' : 'N');
        gotoxy(5, 22);
        std::cout << "Basic Salary   : " << basicSalary;
    }
    
    gotoxy(5, 21);
    std::cout << "Loan           : " << loan;
}

void Employee::saveToFile(std::ofstream& file) const {
    file.write(reinterpret_cast<const char*>(&code), sizeof(code));
    
    size_t nameLength = name.length();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(name.c_str(), nameLength);
    
    size_t addressLength = address.length();
    file.write(reinterpret_cast<const char*>(&addressLength), sizeof(addressLength));
    file.write(address.c_str(), addressLength);
    
    size_t phoneLength = phone.length();
    file.write(reinterpret_cast<const char*>(&phoneLength), sizeof(phoneLength));
    file.write(phone.c_str(), phoneLength);
    
    file.write(reinterpret_cast<const char*>(&day), sizeof(day));
    file.write(reinterpret_cast<const char*>(&month), sizeof(month));
    file.write(reinterpret_cast<const char*>(&year), sizeof(year));
    
    size_t designationLength = designation.length();
    file.write(reinterpret_cast<const char*>(&designationLength), sizeof(designationLength));
    file.write(designation.c_str(), designationLength);
    
    file.write(reinterpret_cast<const char*>(&grade), sizeof(grade));
    file.write(reinterpret_cast<const char*>(&houseAllowance), sizeof(houseAllowance));
    file.write(reinterpret_cast<const char*>(&conveyanceAllowance), sizeof(conveyanceAllowance));
    file.write(reinterpret_cast<const char*>(&loan), sizeof(loan));
    file.write(reinterpret_cast<const char*>(&basicSalary), sizeof(basicSalary));
}

void Employee::loadFromFile(std::ifstream& file) {
    file.read(reinterpret_cast<char*>(&code), sizeof(code));
    
    size_t nameLength;
    file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    char* nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = nameBuffer;
    delete[] nameBuffer;
    
    size_t addressLength;
    file.read(reinterpret_cast<char*>(&addressLength), sizeof(addressLength));
    char* addressBuffer = new char[addressLength + 1];
    file.read(addressBuffer, addressLength);
    addressBuffer[addressLength] = '\0';
    address = addressBuffer;
    delete[] addressBuffer;
    
    size_t phoneLength;
    file.read(reinterpret_cast<char*>(&phoneLength), sizeof(phoneLength));
    char* phoneBuffer = new char[phoneLength + 1];
    file.read(phoneBuffer, phoneLength);
    phoneBuffer[phoneLength] = '\0';
    phone = phoneBuffer;
    delete[] phoneBuffer;
    
    file.read(reinterpret_cast<char*>(&day), sizeof(day));
    file.read(reinterpret_cast<char*>(&month), sizeof(month));
    file.read(reinterpret_cast<char*>(&year), sizeof(year));
    
    size_t designationLength;
    file.read(reinterpret_cast<char*>(&designationLength), sizeof(designationLength));
    char* designationBuffer = new char[designationLength + 1];
    file.read(designationBuffer, designationLength);
    designationBuffer[designationLength] = '\0';
    designation = designationBuffer;
    delete[] designationBuffer;
    
    file.read(reinterpret_cast<char*>(&grade), sizeof(grade));
    file.read(reinterpret_cast<char*>(&houseAllowance), sizeof(houseAllowance));
    file.read(reinterpret_cast<char*>(&conveyanceAllowance), sizeof(conveyanceAllowance));
    file.read(reinterpret_cast<char*>(&loan), sizeof(loan));
    file.read(reinterpret_cast<char*>(&basicSalary), sizeof(basicSalary));
}
