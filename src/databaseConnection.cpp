#include "include/databaseConnection.h"  
#include <iostream>

bool DatabaseConnection::connectToDatabase() {
    try {
            conn = new pqxx::connection(connectionString);  
        if (conn->is_open()) {
            std::cout << "Connected to database: " << conn->dbname() << std::endl; 
            return true; 
        } else {
            std::cerr <<  "Failed to connect to database: " << conn->dbname() << std::endl; 
            return false; 
        }   
    } catch (const std::exception  &e) { 
        std::cerr << "Connection Error: " << e.what() << std::endl; 
        return false; 
    } 
}  

void DatabaseConnection::disconnectToDatabase() {
    if (conn) {
        delete conn;  
        conn = nullptr;  
        std::cout << "Disconnected from database." << std::endl;
    }
} 

void DatabaseConnection::saveUserInformation(const std::string& username, const std::string& password) {
    if (!conn || !conn->is_open()) {
        std::cerr << "Database connection is not open. Cannot save user information." << std::endl;
        return;
    }
    try {
        pqxx::work txn(*conn);  // Start a transaction using the existing connection
        // Execute parameterized SQL to safely insert data
        txn.exec_params(
            "INSERT INTO users (username, password) VALUES ($1, $2)",
            username, password  // Replace $1 and $2 with username and password
        );

        txn.commit();  // Commit the transaction to save changes
        std::cout << "User information saved successfully for: " << username << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error saving user information: " << e.what() << std::endl;
    }
}

