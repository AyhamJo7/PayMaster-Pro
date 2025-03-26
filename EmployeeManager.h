#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include "Employee.h"
#include <vector>
#include <string>

/**
 * @class EmployeeManager
 * @brief Manages employee records
 */
class EmployeeManager {
private:
    const std::string DATA_FILE = "employees.dat";
    std::vector<Employee> employees;
    
    // Load all employees from file
    void loadEmployees();
    
    // Save all employees to file
    void saveEmployees();
    
public:
    // Constructor
    EmployeeManager();
    
    // Add new employee
    void addEmployee(const Employee& emp);
    
    // Modify employee
    void modifyEmployee(const Employee& emp);
    
    // Delete employee
    void deleteEmployee(int code);
    
    // Get employee by code
    Employee getEmployeeByCode(int code);
    
    // Check if employee exists
    bool employeeExists(int code);
    
    // Get all employees
    const std::vector<Employee>& getAllEmployees() const;
    
    // Get last employee code
    int getLastEmployeeCode() const;
    
    // Display all employees
    void displayAllEmployees() const;
    
    // Generate salary report
    void generateSalaryReport() const;
};

#endif // EMPLOYEE_MANAGER_H
