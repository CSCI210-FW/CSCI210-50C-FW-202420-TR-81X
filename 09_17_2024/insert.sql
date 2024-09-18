/* insert into customer
 values(
 NULL,
 'Ireland',
 'Jessica',
 'G',
 '912',
 '842-3382',
 0
 ) */
/* insert into customer (
 cus_fname,
 cus_lname,
 cus_initial,
 cus_areacode,
 cus_phone
 )
 values ('Samantha', 'Kingery', 'D', '443', '309-1368') */
/* insert into customer (
 cus_fname,
 cus_lname,
 cus_initial,
 cus_areacode,
 cus_phone
 )
 values ('Daniel', 'McGee', 'L', '724', '737-5229'),
 ('Susan', 'Staley', 'V', '253', '755-5203'); */
/* insert into vendor(v_name, v_areacode, v_phone, v_state, v_order)
 values (
 "Alpha Supplies",
 '212',
 '555-0101',
 'NY',
 true
 ),
 (
 "Beta Technologies",
 '415',
 '555-0202',
 'CA',
 0
 ),
 (
 "Gamma Solutions",
 '305',
 '555-0303',
 'FL',
 1
 ),
 (
 "Delta Services",
 '512',
 '555-0404',
 'TX',
 1
 ),
 (
 "Epsilon Inc.",
 '617',
 '555-0505',
 'MA',
 0
 ),
 (
 "Zeta Innovations",
 '702',
 '555-0606',
 'NV',
 1
 ),
 (
 "Eta Enterprises",
 '212',
 '555-0707',
 'NY',
 0
 ),
 (
 "Theta Tech",
 '303',
 '555-0808',
 'CO',
 1
 ),
 (
 "Iota Industries",
 '206',
 '555-0909',
 'WA',
 0
 ),
 (
 "Kappa Solutions",
 '404',
 '555-1001',
 'GA',
 1
 ) */
insert into product (
        p_code,
        p_descript,
        p_indate,
        p_qoh,
        p_min,
        p_price,
        v_code
    )
values (
        'A1B2C3',
        'Wireless Mouse',
        '2024-09-01',
        25,
        10,
        29.99,
        8
    ),
    (
        'D4E5F6',
        'Bluetooth Headphones',
        '2024-09-03',
        15,
        8,
        99.99,
        9
    ),
    (
        'G7H8I9',
        'USB-C Charging Cable',
        '2024-09-05',
        40,
        15,
        12.99,
        7
    ),
    (
        'J0K1L2',
        '4K Monitor',
        '2024-09-07',
        10,
        5,
        399.99,
        9
    ),
    (
        'M3N4O5',
        'Ergonomic Chair',
        '2024-09-09',
        8,
        6,
        149.99,
        8
    ),
    (
        'P6Q7R8',
        'Mechanical Keyboard',
        '2024-09-11',
        20,
        12,
        89.99,
        7
    ),
    (
        'S9T0U1',
        'External Hard Drive',
        '2024-09-13',
        12,
        7,
        119.99,
        8
    ),
    (
        'V2W3X4',
        'Gaming Headset',
        '2024-09-15',
        18,
        10,
        79.99,
        9
    ),
    (
        'Y5Z6A7',
        'Desk Lamp',
        '2024-09-17',
        30,
        9,
        34.99,
        7
    ),
    (
        'B8C9D0',
        'Laptop Stand',
        '2024-09-19',
        22,
        8,
        24.99,
        6
    )