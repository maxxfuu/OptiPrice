#include "optionPricer.h"
#include <iostream> 
#include <cmath>

bool connectToDatabase() {
    try {
        std::string connectionString = "dbname=mydatabase user=maxfu password=Maxfu1889 host=127.0.0.1 port=5432"; 
        pqxx::connection conn(connectionString);  // Initalize the connection,  pass the string

        if (conn.is_open()) { // Check if PostgreSQL can establish a connection to the database
            std::cout << "Connection to database successfully: " << conn.dbname() << std::endl; 
            return true;  
        } else {
            std::cerr << "Failed to connect to database" << std::endl; 
            return false; 
        } 
    } catch (const std::exception &e) {
        std::cerr << "Connection Error: " << e.what() << std::endl;
        return false;  
    } 

}

// Helper functions to calculate d1 and d2
double calculateD1(const Option &opt) {
    return (log(opt.stockPrice / opt.strikePrice) + (opt.riskFreeInterestRate + 0.5 * opt.volatility * opt.volatility) * opt.timeToExpiration) 
           / (opt.volatility * sqrt(opt.timeToExpiration));
}

double calculateD2(double d1, const Option &opt) {
    return d1 - opt.volatility * sqrt(opt.timeToExpiration);
}

// Cumulative distribution function for the standard normal distribution
double normalCDF(double x) {
    return 0.5 * std::erfc(-x * M_SQRT1_2); // M_SQRT1_2 is 1/sqrt(2)
}

// Calculate the call option price
double calculateCallPrice(const Option &opt) {
    double d1 = calculateD1(opt);
    double d2 = calculateD2(d1, opt);
    double callPrice = opt.stockPrice * normalCDF(d1) - opt.strikePrice * exp(-opt.riskFreeInterestRate * opt.timeToExpiration) * normalCDF(d2);
    return callPrice;
}

// Calculate the put option price
double calculatePutPrice(const Option &opt) {
    double d1 = calculateD1(opt);
    double d2 = calculateD2(d1, opt);
    double putPrice = opt.strikePrice * exp(-opt.riskFreeInterestRate * opt.timeToExpiration) * normalCDF(-d2) - opt.stockPrice * normalCDF(-d1);
    return putPrice;
}
