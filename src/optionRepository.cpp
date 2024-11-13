#include "include/optionRepository.h"
#include <iostream>

optionRepository::OptionRepository(const std::string& connStr) : conn(connStr) {}

void optionRepository::saveOption(const Option& opt, double price) {
    try {
        pqxx::work txn(conn);
        std::string sql = "INSERT INTO options (option_id, stock_price, strike_price, "
                          "time_to_expiration, risk_free_interest_rate, volatility, "
                          "type_of_option, price) VALUES (" +
                          txn.quote(opt.optionId) + ", " +
                          txn.quote(opt.stockPrice) + ", " +
                          txn.quote(opt.strikePrice) + ", " +
                          txn.quote(opt.timeToExpiration) + ", " +
                          txn.quote(opt.riskFreeInterestRate) + ", " +
                          txn.quote(opt.volatility) + ", " +
                          txn.quote(opt.typeOfOption) + ", " +
                          txn.quote(price) + ")";
        txn.exec(sql);
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "Database error: " << e.what() << std::endl;
    }
}