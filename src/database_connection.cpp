#include "database_connection.h"  
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

