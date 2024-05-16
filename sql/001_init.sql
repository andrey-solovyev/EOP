create table Review
(
    id           INTEGER PRIMARY KEY,
    description  varchar(1000) not null,
    grade        INTEGER       not null,
    user         INTEGER       not null,
    courseId     INTEGER       not null,
    isUpdated    boolean       not null default false,
    creationDate DATETIME      not null default CURRENT_TIMESTAMP,
    updateDate   DATETIME,
    isBanned     boolean                default false
);

create table ReviewMark
(
    id           INTEGER PRIMARY KEY AUTOINCREMENT,
    mark         INTEGER  NOT NULL, -- -1 dislike 1 like
    userId       INTEGER  NOT NULL,
    reviewId     INTEGER  NOT NULL,
    creationDate DATETIME not null default CURRENT_TIMESTAMP
);

create table ReviewBan
(
    id           INTEGER PRIMARY KEY AUTOINCREMENT,
    adminId      INTEGER       NOT NULL,
    reviewId     INTEGER       NOT NULL,
    description  varchar(1000) not null,
    creationDate DATETIME      not null default CURRENT_TIMESTAMP
);