#include <iostream> 
#include <stdexcept> 
#include <pqxx/pqxx> 
#include "include/userAuth.h"  

// Constructor Method - Immediately binding refernece to an object to prevent 
UserAuth::UserAuth(DatabaseConnection& dbConn) : dbConn(dbConn) {}; 
    
void UserAuth::auth() {
    std::string username; 
    std::string password; 

    std::cout << "Username: ";  
    std::getline(std::cin, username); 

    std::cout << "Password: ";  
    std::getline(std::cin, password); 

    // Attempt to login, Invoke UserAuth::login() func  
    if (!login(username, password)) {
        std::cout << "Login Failed. Invalid username or password";  
    } else {
        std::cout << "Login Successful"; 
    } 
};

bool UserAuth::login(const std::string& username, const std::string& password) {
    try {
        std::string query = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "';";
        auto result = dbConn.executeQuery(query);

        if (result.empty()) {
            return false;
        }

        return true; 
    } catch (const std::exception& e) {
        std::cerr << "Login error: " << e.what() << std::endl;
        return false;
    }
} 

void UserAuth::registerUser(const std::string&  username, const std::string& password) { 
    try {
        std::string query = "INSERT INTO users (username, password) VALUES ($1, $2)";
        dbConn.executeUpdate(query, username, password);
        std::cout << "User registered successfully: " << username << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Registration error: " << e.what() << std::endl;
    }
}; 

