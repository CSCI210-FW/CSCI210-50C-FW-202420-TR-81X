-- SQLite
create table if not exists invoice (
    inv_number integer primary key,
    cus_code integer references customer(cus_code) not null,
    inv_date text not null default(date('now'))
);