/* update line
 set line_number = 1
 where inv_number = 1 */
update line
set line_price = (
        select p_price
        from product
        where product.p_code = line.p_code
    )
where line_price is null