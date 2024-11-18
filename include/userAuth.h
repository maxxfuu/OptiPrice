#ifndef USER_AUTH_H
#define USER_AUTH_H 

#include <string> 
#include "user.h"  
#include "databaseConnection.h" 

class UserAuth {
    public:
        // Constructor method that takes an instance of an object of DatabaseConnection class called dbConn 
        UserAuth(DatabaseConnection& dbConn); 
        void auth(); 
        bool login(const std::string& username, const std::string& password); 
        void UserAuth::registerUser(const std::string&  username, const std::string& password); 

    private: 
        DatabaseConnection& dbConn;
};

#endif 