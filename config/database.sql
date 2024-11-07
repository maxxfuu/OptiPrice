CREATE DATABASE mydatabase; 
    \c mydatabase 

CREATE TABLE IF NOT EXISTS users (
    user_id SERIAL PRIMARY KEY, 
    username TEXT UNIQUE NOT NULL, 
    password TEXT NOT NULL 
); 

CREATE TABLE IF NOT EXISTS options (
    option_id SERIAL PRIMARY KEY,
    user_id INT REFERENCES users(user_id), -- Link each option to a user, cascade delete
    option_type VARCHAR(4) NOT NULL,                         -- Type of option: "call" or "put" cannot go over 4 characters 
    stock_price DOUBLE PRECISION NOT NULL,
    strike_price DOUBLE PRECISION NOT NULL,
    time_to_expiration DOUBLE PRECISION NOT NULL,
    risk_free_interest_rate DOUBLE PRECISION NOT NULL,
    volatility DOUBLE PRECISION NOT NULL,
    price DOUBLE PRECISION NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP            -- Optional: timestamp of prediction creation
);