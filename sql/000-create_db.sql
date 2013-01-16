
create database db_evias with encoding = 'utf-8' ;
create table user_obj (
    id_user     integer     not null primary key,
    firstname   text        not null,
    lastname    text        not null,
    email       text,
    date_created    timestamp   not null default now(),
    date_updated    timestamp
);
