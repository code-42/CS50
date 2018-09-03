/*
 create table for transactions
*/
DROP TABLE IF EXISTS trades;
CREATE TABLE 'trades' (
    'user_id' TEXT NOT NULL,
    'shares' INTEGER NOT NULL,
    'symbol' TEXT NOT NULL,
    'company_name' TEXT NOT NULL,
    'price' REAL NOT NULL,
    'timestamp' DATETIME PRIMARY KEY NOT NULL);


/*
 create table for portfolio
 select symbol, shares, sum(shares * price) from trades group by symbol;
*/
DROP VIEW IF EXISTS portfolio;
CREATE VIEW IF NOT EXISTS portfolio AS
SELECT user_id, symbol, company_name, shares, sum(shares * price)
FROM trades
GROUP BY symbol;

/*
 create table for portfolio
*/

CREATE TABLE 'portfolio' (
    'user_id' TEXT NOT NULL,
    'shares' INTEGER NOT NULL,
    'symbol' TEXT NOT NULL,
    'current_price' REAL NOT NULL,
    'timestamp' DATETIME PRIMARY KEY NOT NULL);

