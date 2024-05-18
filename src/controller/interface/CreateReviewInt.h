#ifndef CREATE_REVIEW_С_H
#define CREATE_REVIEW_С_H

#ifdef __cplusplus
extern "C" {
#endif

struct CreateReviewInt
{
    char* description;
    int grade;
    int userId;
    int courseId;
};

struct Review
{
    int id;
    char* description;
    int grade;
    int userId;
    int courseId;
    char* creationDate;
    char* updateDate;
};

struct PageCDto
{
    unsigned int offset;
    unsigned int limit;
    unsigned int count;
    void* items;
};

struct CreateReviewBanCDto
{
    int adminId;
    int reviewId;
    char* description;
};

struct ReviewBanCDto
{
    int id;
    int adminId;
    int reviewId;
    char* description;
    char* creationDate;
};

void createReview(struct CreateReviewInt* dto,struct Review* review);

void updateReview(struct Review* dto, struct Review*);
void getReviewById(int id, struct Review*);
void getLikes(int id, struct Review*);
void getDislikes(int id, struct Review*);

void getReviews(int offset, int limit, struct PageCDto*);
void getReviewByUserId(char* userId, int offset, int limit, struct PageCDto*);
void getReviewByCourseId(char* courseId, int offset, int limit, struct PageCDto*);


void getBanReviewById(int id, struct ReviewBanCDto*);
void banReview(struct CreateReviewBanCDto* dto, struct ReviewBanCDto*);
void getBanReviews(int id, struct ReviewBanCDto*);
void unbanReview(int reviewMarkid, int adminId, int reviewId, struct Review*);

#ifdef __cplusplus
}
#endif

#endif
