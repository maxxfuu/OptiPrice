#ifndef USER_AUTH_H
#define USER_AUTH_H 

#include <string> 
#include "user.h" 
#include "databaseConnection.h" 

class UserAuth {
    public: 
        UserAuth(DatabaseConnection& dbConn); 
        bool login(const std::string& username, const std::string& password); 
        void registerUser(const User& user); 

    private: 
        DatabaseConnection& dbConn;
};

#endif 