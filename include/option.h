#ifndef OPTION_H
#define OPTION_H 

#include <string> 

struct Option { 
    // A collection of data types to represent option
    std::string optionId; 
    double stockPrice; 
    double strikePrice; 
    double timeToExpiration; 
    double riskFreeInterestRate; 
    double volatility; 
    std::string typeOfOption; 
   
        Option(const std::string& id, double price, double strike, double expiration, double risk, double vol, std::string type)
         : optionId(id),stockPrice(price), strikePrice(strike), timeToExpiration(expiration), riskFreeInterestRate(risk), volatility(vol), typeOfOption(type) {}

}; 

#endif 