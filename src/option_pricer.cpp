#include "option_pricer.h"
#include <cmath>

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
