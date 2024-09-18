create table if not exists product(
    p_code text,
    p_descript text not null unique,
    p_indate text not null,
    p_qoh int not null default(0),
    p_min int not null default(0),
    p_price real not null default(0),
    p_discount real default(0),
    v_code int,
    primary key (p_code),
    foreign key (v_code) references vendor(v_code)
);