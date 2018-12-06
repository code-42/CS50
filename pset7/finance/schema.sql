/*
users table provided with assignment
*/
DROP TABLE IF EXISTS users;
CREATE TABLE IF NOT EXISTS 'users' (
  'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  'username' TEXT NOT NULL, 'hash' TEXT NOT NULL,
  'cash' NUMERIC NOT NULL DEFAULT 10000.00 );
CREATE UNIQUE INDEX 'username' ON "users" ("username");

/*
 create table for transactions
*/
DROP TABLE IF EXISTS trades;
CREATE TABLE IF NOT EXISTS 'trades' (
    'trades_id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    'user_id' TEXT NOT NULL,
    'shares' INTEGER NOT NULL,
    'symbol' TEXT NOT NULL,
    'company_name' TEXT NOT NULL,
    'price' REAL NOT NULL,
    'timestamp' DATETIME NOT NULL);

/*
create table for cash deposits and withdrawals
*/
DROP TABLE IF EXISTS cashInOut;
CREATE TABLE IF NOT EXISTS 'cashInOut' (
    'inout_id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    'user_id' TEXT NOT NULL,
    'amount'  NUMERIC NOT NULL,
    'timestamp' DATETIME NOT NULL);


/*
 create view for portfolio
 select symbol, shares, sum(shares * price) from trades group by symbol;
*/
DROP VIEW IF EXISTS portfolio;
CREATE VIEW IF NOT EXISTS portfolio AS
SELECT user_id, symbol, company_name, sum(shares), sum(shares * price)
FROM trades
GROUP BY symbol;

