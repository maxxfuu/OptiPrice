#pragma once 
#include <pqxx/pqxx> 

class DatabaseConnection {
    
    public:
        bool connectToDatabase(); 
        void disconnectToDatabase();
        void saveUserInformation(const std::string& username, const std::string& password);  

    private:     
        pqxx::connection *conn; 
        std::string connectionString = "dbname=mydatabase user=maxfu password=Maxfu1889 host=127.0.0.1 port=5432";
 
}; 
