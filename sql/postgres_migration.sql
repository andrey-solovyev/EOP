create
    database review;

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

comment
    on column review.review.id is 'Идентификатор отзыва';
comment
    on column review.review.description is 'Текст отзыва';
comment
    on column review.review.grade is 'Оценка';
comment
    on column review.review.user_id is 'Логин комментатора';
comment
    on column review.review.is_updated is 'Отображать логин комментатора в публикации';
comment
    on column review.review.course_id is 'Идентификатор курса, к которому добавлен коммент';
comment
    on column review.review.creation_date is 'Дата создания';
comment
    on column review.review.update_date is 'Дата обновления';
comment
    on column review.review.is_banned is 'Заблокирован ли комментарий пользователя';

create table review.review_mark
(
    id            SERIAL PRIMARY KEY ,
    mark          INTEGER NOT NULL, -- -1 dislike 1 like
    user_id       INTEGER NOT NULL,
    review_id     INTEGER NOT NULL,
    creation_date TIMESTAMP    not null default CURRENT_TIMESTAMP
);

comment
    on column review.review_mark.id is 'Идентификатор комментария оценки';
comment
    on column review.review_mark.mark is 'Оценка';
comment
    on column review.review_mark.user_id is 'Идентификатор пользователя';
comment
    on column review.review_mark.review_id is 'Идентификатор комментария, к которому добавлено действие';
comment
    on column review.review_mark.creation_date is 'Дата создания';

create table review.review_ban
(
    id            SERIAL PRIMARY KEY  ,
    admin_id      INTEGER       NOT NULL,
    review_id     INTEGER       NOT NULL,
    description   varchar(1000) not null,
    creation_date TIMESTAMP          not null default CURRENT_TIMESTAMP
);

comment
    on column review.review_ban.id is 'Идентификатор комментария оценки';
comment
    on column review.review_ban.description is 'Описание причины';
comment
    on column review.review_ban.admin_id is 'Логин админа';
comment
    on column review.review_ban.review_id is 'Идентификатор комментария, к которому добавлено действие';
comment
    on column review.review_ban.creation_date is 'Дата создания';

-- права на таблицы

CREATE
    USER review_admin WITH PASSWORD 'admin';
GRANT CONNECT
    ON DATABASE review TO review_admin;
GRANT USAGE ON SCHEMA
    review TO review_admin;
GRANT SELECT, INSERT, UPDATE, DELETE ON review.review TO review_admin;
GRANT SELECT ON review.review_ban TO review_admin;
GRANT INSERT, UPDATE, DELETE ON review.review_mark TO review_admin;

-- Проверка прав
SELECT pg_catalog.has_table_privilege(
               'review_admin', 'review.review', 'SELECT')     AS "SELECT",
       pg_catalog.has_table_privilege(
               'review_admin', 'review.review', 'INSERT')     AS "INSERT",
       pg_catalog.has_table_privilege(
               'review_admin', 'review.review', 'UPDATE')     AS "UPDATE",
       pg_catalog.has_table_privilege(
               'review_admin', 'review.review', 'DELETE')     AS "DELETE",
       pg_catalog.has_table_privilege(
               'review_admin', 'review.review', 'TRUNCATE')   AS "TRUNCATE",
       pg_catalog.has_table_privilege(
               'review_admin', 'review.review', 'REFERENCES') AS "REFERENCES",
       pg_catalog.has_table_privilege(
               'review_admin', 'review.review', 'TRIGGER')    AS "TRIGGER";