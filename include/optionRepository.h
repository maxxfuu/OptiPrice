#ifndef OPTION_REPOSITORY_H 
#define OPTION_REPOSITORY_H 

#include <pqxx/pqxx> 
#include "option.h"

class OptionRepository {
    public: 
        OptionRepository(const std::string& connectionString); 
        void saveOption(const Option& opt, double price);  
    private: 
        pqxx::connection conn;  
};

#endif  