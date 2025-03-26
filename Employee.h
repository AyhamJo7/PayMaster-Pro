#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <fstream>

/**
 * @class Employee
 * @brief Represents an employee in the payroll system
 */
class Employee {
private:
    int code;
    std::string name;
    std::string address;
    std::string phone;
    int day, month, year; // Joining date
    std::string designation;
    char grade;
    bool houseAllowance;
    bool conveyanceAllowance;
    float loan;
    float basicSalary;

public:
    // Constructors
    Employee();
    Employee(int code, const std::string& name, const std::string& address, 
             const std::string& phone, int day, int month, int year, 
             const std::string& designation, char grade, bool houseAllowance, 
             bool conveyanceAllowance, float loan, float basicSalary);

    // Getters
    int getCode() const;
    std::string getName() const;
    std::string getAddress() const;
    std::string getPhone() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    std::string getDesignation() const;
    char getGrade() const;
    bool getHouseAllowance() const;
    bool getConveyanceAllowance() const;
    float getLoan() const;
    float getBasicSalary() const;

    // Setters
    void setCode(int code);
    void setName(const std::string& name);
    void setAddress(const std::string& address);
    void setPhone(const std::string& phone);
    void setJoiningDate(int day, int month, int year);
    void setDesignation(const std::string& designation);
    void setGrade(char grade);
    void setHouseAllowance(bool houseAllowance);
    void setConveyanceAllowance(bool conveyanceAllowance);
    void setLoan(float loan);
    void setBasicSalary(float basicSalary);

    // Methods
    std::string getJoiningDateString() const;
    float calculateHRA() const;
    float calculateCA() const;
    float calculateDA() const;
    float calculatePF() const;
    float calculateLoanDeduction() const;
    float calculateTotalAllowance() const;
    float calculateTotalDeduction() const;
    float calculateNetSalary() const;
    void display() const;
    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);
};

#endif // EMPLOYEE_H
