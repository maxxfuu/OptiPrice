#ifndef OPTION_PRICER
#define OPTION_PRICER 

#include <string> 
#include <pqxx/pqxx>  

struct Option{
    
    std::string optionId; 
    
    double stockPrice;           
    double strikePrice;         
    double timeToExpiration;     
    double riskFreeInterestRate;
    double volatility;           
    std::string typeOfOption;    
    
};

bool connectToDatabase() {}; 

double calculateCallPrice(const Option &opt); 
double calculatePutPrice(const Option &opt); 

double calculateD1(const Option &opt); 
double calculateD2(double d1, double volatility, double timeToExpiration); 

#endif

/*
Volatility:                         How much the price of the security is expected to change during the option's life 
Price of the underlying asset:      The current price of the stock or other asset 
Strike price:                       The price at which the option can be exercised 
Time to expiration:                 How long until the option expires 
Risk-free interest rate:            The interest rate earned on cash with no risk 
Type of option:                     Whether the option is a call or put 
*/