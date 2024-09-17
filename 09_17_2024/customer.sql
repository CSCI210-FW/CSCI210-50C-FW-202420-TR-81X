-- SQLite
create table if not exists customer(
    cus_code integer primary key,
    cus_lname text not null,
    cus_fname text not null,
    cus_initial text,
    cus_areacode text default ('615'),
    cus_phone text not null,
    cus_balance real not null default(0)
);