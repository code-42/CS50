/*
 create table for places
*/
DROP TABLE IF EXISTS places;

CREATE TABLE 'places' (
    'country_code' TEXT NOT NULL,
    'postal_code' TEXT NOT NULL,
    'place_name' TEXT NOT NULL,
    'admin_name1' TEXT NOT NULL,
    'admin_code1' TEXT NOT NULL,
    'admin_name2' TEXT NOT NULL,
    'admin_code2' TEXT NOT NULL,
    'admin_name3' TEXT NOT NULL,
    'admin_code3' TEXT NOT NULL,
    'latitude' TEXT NOT NULL,
    'longitude' TEXT NOT NULL,
    'accuracy' TEXT NOT NULL
    );