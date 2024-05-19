
create schema review;

create table review.review
(
    id            SERIAL PRIMARY KEY,
    description   varchar(1000) not null,
    grade         INTEGER       not null,
    user_id       INTEGER       not null,
    course_id     INTEGER       not null,
    is_updated    boolean       not null default false,
    creation_date TIMESTAMP          not null default CURRENT_TIMESTAMP,
    update_date   TIMESTAMP,
    is_banned     boolean                default false
);

create table review.review_mark
(
    id            SERIAL PRIMARY KEY  ,
    mark          INTEGER NOT NULL, -- -1 dislike 1 like
    user_id       INTEGER NOT NULL,
    review_id     INTEGER NOT NULL,
    creation_date TIMESTAMP    not null default CURRENT_TIMESTAMP
);

create table review.review_ban
(
    id            SERIAL PRIMARY KEY  ,
    admin_id      INTEGER       NOT NULL,
    review_id     INTEGER       NOT NULL,
    description   varchar(1000) not null,
    creation_date TIMESTAMP          not null default CURRENT_TIMESTAMP
);