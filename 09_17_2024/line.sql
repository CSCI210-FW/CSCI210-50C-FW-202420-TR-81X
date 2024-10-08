create table if not exists line(
    inv_number integer references invoice(inv_number),
    line_number integer,
    p_code text not null references product(p_code),
    line_units int not null default(1),
    line_price real,
    primary key (inv_number, line_number)
)