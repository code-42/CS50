/*
 create table for transactions
 */

CREATE TABLE 'trades' (
    'user_id' TEXT NOT NULL,
    'shares' INTEGER NOT NULL,
    'symbol' TEXT NOT NULL,
    'price' REAL NOT NULL,
    'timestamp' DATETIME PRIMARY KEY NOT NULL);



