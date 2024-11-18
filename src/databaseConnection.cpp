#include "include/databaseConnection.h" 
#include "user.h" 
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

void DatabaseConnection::saveUserInformation(const User& user) {
    if (!conn || !conn->is_open()) {
        std::cerr << "Database connection is not open. Cannot save user information." << std::endl;
        return;
    }
    try {
        pqxx::work txn(*conn);  // Start a transaction using the existing connection
        // Execute parameterized SQL to safely insert data
        txn.exec_params(
            "INSERT INTO users (username, password) VALUES ($1, $2)",
            user.username, user.password // Replace $1 and $2 with username and password
        );

        txn.commit();  // Commit the transaction to save changes
        std::cout << "User information saved successfully for: " << user.username << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error saving user information: " << e.what() << std::endl;
    }
}

std::vector<std::map<std::string, std::string>> DatabaseConnection::executeQuery(const std::string& query) {
    if (!conn || !conn->is_open()) {
        throw std::runtime_error("Database connection is not open.");
    }

    try {
        pqxx::work txn(*conn);  // Start a transaction

        pqxx::result result = txn.exec(query);  // Execute the query

        // Convert the result into a vector of maps for easier handling
        std::vector<std::map<std::string, std::string>> rows;
        for (const auto& row : result) {
            std::map<std::string, std::string> rowData;
            for (const auto& field : row) {
                rowData[field.name()] = field.c_str();  // Store field name and value
            }
            rows.push_back(rowData);
        }

        return rows;  // Return the processed result
    } catch (const std::exception& e) {
        std::cerr << "Query execution error: " << e.what() << std::endl;
        throw;
    }    
}; 

void DatabaseConnection::executeUpdate(const std::string& query, const std::string& username, const std::string& password) {
    
};