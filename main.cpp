/**
 * PayMaster Pro - Modern Payroll Management System
 * Copyright (c) 2025 Mhd Ayham Joumran
 * 
 * A modern C++ implementation of a payroll management system
 * with improved code structure, error handling, and user experience.
 */

#include "Employee.h"
#include "EmployeeManager.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>
#include <limits>

// Function prototypes
void addNewEmployee(EmployeeManager& manager);
void displayEmployee(EmployeeManager& manager);
void modifyEmployee(EmployeeManager& manager);
void deleteEmployee(EmployeeManager& manager);
void displayMainMenu();
void displayEditMenu(EmployeeManager& manager);

int main() {
    // Display welcome message
    clearScreen();
    displayTitle("WELCOME TO PAYMASTER PRO", 10);
    displayTitle("A Modern Payroll Management System", 12);
    displayTitle("Copyright (c) 2025 Mhd Ayham Joumran", 14);
    displayTitle("Press any key to continue...", 16);
    std::cin.get();
    
    // Create employee manager
    EmployeeManager manager;
    
    // Display main menu
    displayMainMenu();
    
    return 0;
}

void displayMainMenu() {
    EmployeeManager manager;
    char choice;
    
    while (true) {
        clearScreen();
        drawBox(10, 5, 71, 21, 218);
        drawBox(11, 6, 70, 20, 219);
        drawBox(25, 7, 57, 9, 218);
        
        displayTitle("PAYMASTER PRO", 8);
        
        gotoxy(30, 11);
        std::cout << "1: NEW EMPLOYEE";
        gotoxy(30, 12);
        std::cout << "2: DISPLAY EMPLOYEE";
        gotoxy(30, 13);
        std::cout << "3: LIST OF EMPLOYEES";
        gotoxy(30, 14);
        std::cout << "4: SALARY SLIP";
        gotoxy(30, 15);
        std::cout << "5: EDIT";
        gotoxy(30, 16);
        std::cout << "0: QUIT";
        gotoxy(30, 18);
        std::cout << "ENTER YOUR CHOICE: ";
        
        choice = getCharInput("", "012345");
        
        if (choice == '0') {
            break;
        }
        
        switch (choice) {
            case '1':
                addNewEmployee(manager);
                break;
            case '2':
                displayEmployee(manager);
                break;
            case '3':
                manager.displayAllEmployees();
                break;
            case '4':
                manager.generateSalaryReport();
                break;
            case '5':
                displayEditMenu(manager);
                break;
        }
    }
    
    clearScreen();
    displayTitle("Thank you for using PayMaster Pro!", 10);
    displayTitle("Goodbye!", 12);
    std::cin.get();
}

void displayEditMenu(EmployeeManager& manager) {
    char choice;
    
    while (true) {
        clearScreen();
        drawBox(10, 5, 71, 21, 218);
        drawBox(11, 6, 70, 20, 219);
        drawBox(28, 8, 49, 10, 218);
        
        displayTitle("EDIT MENU", 9);
        
        gotoxy(30, 13);
        std::cout << "1: DELETE RECORD";
        gotoxy(30, 14);
        std::cout << "2: MODIFY RECORD";
        gotoxy(30, 15);
        std::cout << "0: EXIT";
        gotoxy(30, 17);
        std::cout << "ENTER YOUR CHOICE: ";
        
        choice = getCharInput("", "012");
        
        if (choice == '0') {
            break;
        }
        
        switch (choice) {
            case '1':
                deleteEmployee(manager);
                break;
            case '2':
                modifyEmployee(manager);
                break;
        }
    }
}

void addNewEmployee(EmployeeManager& manager) {
    clearScreen();
    displayTitle("ADD NEW EMPLOYEE", 2);
    displayTitle("~~~~~~~~~~~~~~~~", 3);
    
    int code = manager.getLastEmployeeCode() + 1;
    
    gotoxy(5, 5);
    std::cout << "Employee Code # " << code;
    
    std::string name = getStringInput("Enter employee name: ", 1, 25);
    if (name == "0") return;
    
    std::string address = getStringInput("Enter employee address: ", 1, 30);
    if (address == "0") return;
    
    std::string phone = getStringInput("Enter employee phone number (or press Enter for none): ", 0, 10);
    if (phone == "0") return;
    if (phone.empty()) phone = "-";
    
    int day = getIntInput("Enter day of joining: ", 1, 31);
    int month = getIntInput("Enter month of joining: ", 1, 12);
    int year = getIntInput("Enter year of joining: ", 1900, 2100);
    
    std::string designation = getStringInput("Enter employee designation: ", 1, 15);
    if (designation == "0") return;
    
    char grade = getCharInput("Enter employee grade (A/B/C/D/E): ", "ABCDE");
    if (grade == '0') return;
    
    bool houseAllowance = false;
    bool conveyanceAllowance = false;
    float basicSalary = 0.0f;
    
    if (grade != 'E') {
        houseAllowance = getYesNoInput("Allocate house allowance?");
        conveyanceAllowance = getYesNoInput("Allocate conveyance allowance?");
        basicSalary = getFloatInput("Enter basic salary: ", 0.0f, 50000.0f);
    }
    
    float loan = getFloatInput("Enter loan amount (if any): ", 0.0f, 50000.0f);
    
    if (!getYesNoInput("Do you want to save this employee?")) {
        return;
    }
    
    Employee emp(code, name, address, phone, day, month, year, designation, 
                 grade, houseAllowance, conveyanceAllowance, loan, basicSalary);
    
    manager.addEmployee(emp);
}

void displayEmployee(EmployeeManager& manager) {
    clearScreen();
    displayTitle("DISPLAY EMPLOYEE", 2);
    displayTitle("~~~~~~~~~~~~~~~~", 3);
    
    int code = getIntInput("Enter employee code: ", 1, 9999);
    if (code == 0) return;
    
    if (!manager.employeeExists(code)) {
        displayStatusMessage("Employee not found!");
        waitForKeyPress();
        return;
    }
    
    clearScreen();
    displayTitle("EMPLOYEE DETAILS", 2);
    displayTitle("~~~~~~~~~~~~~~~~", 3);
    
    Employee emp = manager.getEmployeeByCode(code);
    emp.display();
    
    waitForKeyPress();
}

void modifyEmployee(EmployeeManager& manager) {
    clearScreen();
    displayTitle("MODIFY EMPLOYEE", 2);
    displayTitle("~~~~~~~~~~~~~~~", 3);
    
    int code = getIntInput("Enter employee code: ", 1, 9999);
    if (code == 0) return;
    
    if (!manager.employeeExists(code)) {
        displayStatusMessage("Employee not found!");
        waitForKeyPress();
        return;
    }
    
    Employee emp = manager.getEmployeeByCode(code);
    
    clearScreen();
    displayTitle("MODIFY EMPLOYEE", 2);
    displayTitle("~~~~~~~~~~~~~~~", 3);
    
    emp.display();
    
    if (!getYesNoInput("Do you want to modify this employee?")) {
        return;
    }
    
    clearScreen();
    displayTitle("MODIFY EMPLOYEE", 2);
    displayTitle("~~~~~~~~~~~~~~~", 3);
    
    gotoxy(5, 5);
    std::cout << "Employee Code # " << code;
    
    std::string name = getStringInput("Enter new name (or press Enter for no change): ", 0, 25);
    if (name == "0") return;
    if (!name.empty()) emp.setName(name);
    
    std::string address = getStringInput("Enter new address (or press Enter for no change): ", 0, 30);
    if (address == "0") return;
    if (!address.empty()) emp.setAddress(address);
    
    std::string phone = getStringInput("Enter new phone (or press Enter for no change): ", 0, 10);
    if (phone == "0") return;
    if (!phone.empty()) emp.setPhone(phone);
    
    std::string designation = getStringInput("Enter new designation (or press Enter for no change): ", 0, 15);
    if (designation == "0") return;
    if (!designation.empty()) emp.setDesignation(designation);
    
    char grade = getCharInput("Enter new grade (A/B/C/D/E) or press Enter for no change: ", "ABCDE\r");
    if (grade == '0') return;
    if (grade != '\r') emp.setGrade(grade);
    
    if (emp.getGrade() != 'E') {
        char houseChoice = getCharInput("Allocate house allowance? (Y/N) or press Enter for no change: ", "YN\r");
        if (houseChoice == '0') return;
        if (houseChoice != '\r') emp.setHouseAllowance(houseChoice == 'Y');
        
        char convChoice = getCharInput("Allocate conveyance allowance? (Y/N) or press Enter for no change: ", "YN\r");
        if (convChoice == '0') return;
        if (convChoice != '\r') emp.setConveyanceAllowance(convChoice == 'Y');
        
        std::string basicStr = getStringInput("Enter new basic salary (or press Enter for no change): ", 0, 10);
        if (basicStr == "0") return;
        if (!basicStr.empty()) emp.setBasicSalary(std::stof(basicStr));
    }
    
    std::string loanStr = getStringInput("Enter new loan amount (or press Enter for no change): ", 0, 10);
    if (loanStr == "0") return;
    if (!loanStr.empty()) emp.setLoan(std::stof(loanStr));
    
    if (!getYesNoInput("Do you want to save these changes?")) {
        return;
    }
    
    manager.modifyEmployee(emp);
}

void deleteEmployee(EmployeeManager& manager) {
    clearScreen();
    displayTitle("DELETE EMPLOYEE", 2);
    displayTitle("~~~~~~~~~~~~~~~", 3);
    
    int code = getIntInput("Enter employee code: ", 1, 9999);
    if (code == 0) return;
    
    if (!manager.employeeExists(code)) {
        displayStatusMessage("Employee not found!");
        waitForKeyPress();
        return;
    }
    
    clearScreen();
    displayTitle("DELETE EMPLOYEE", 2);
    displayTitle("~~~~~~~~~~~~~~~", 3);
    
    Employee emp = manager.getEmployeeByCode(code);
    emp.display();
    
    if (!getYesNoInput("Do you want to delete this employee?")) {
        return;
    }
    
    manager.deleteEmployee(code);
}
