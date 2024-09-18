create trigger if not exists line_price_trg
after
insert on line begin for each row
update line
set line_price = (
        select p_price
        from product
        where p_code = new.p_code
    )
where p_code = new.p_code