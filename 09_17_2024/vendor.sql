-- SQLite
create table if not exists vendor(
    v_code int primary key,
    v_name text not null,
    v_areacode text default('615'),
    v_phone text not null,
    v_state text not null,
    v_order int check(v_order in (0, 1))
);