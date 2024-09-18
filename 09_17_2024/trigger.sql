create trigger if not exists line_price_trg
after
insert on line begin
update line
set line_price = (
        select price
        from product
        where p_code = new.p_code
    )
where p_code = new.p_code