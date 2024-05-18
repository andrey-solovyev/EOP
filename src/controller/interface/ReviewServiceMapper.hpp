#ifndef REVIEW_SERVICE_HPP
#define REVIEW_SERVICE_HPP

#include <iostream>

#include "CreateReviewInt.h"
#include "db/ReviewBanDb.hpp"
#include "db/ReviewDb.hpp"
#include "service/ReviewService.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class ReviewServiceMapper {
private:
public:
	OATPP_COMPONENT(std::shared_ptr<ReviewService> , m_reviewService); // Inject service component

	// oatpp::Object<CreateReviewDto> mapDtoToCreateReview(CreateReviewInt* create_review);
	// void mapDtoToReview(const oatpp::Object<ReviewDto>& dto, Review* review);



	void createReview(CreateReviewInt* dto, Review* review);

	void updateReview(Review* dto, Review* resultDto);
	void getReviewById(int id, Review* resultDto);
	void getLikes(int id, Review* resultDto);
	void getDislikes(int id, Review* resultDto);

	void getReviews(int offset, int limit, PageCDto* pageDto);
	void getReviewByUserId(char* userId, int offset, int limit, PageCDto* pageDto);
	void getReviewByCourseId(char* courseId, int offset, int limit, PageCDto* pageDto);


	void getBanReviewById(int id, ReviewBanCDto* reviewBanDto);
	void banReview(CreateReviewBanCDto* dto, ReviewBanCDto* resultReviewBan);
	void getBanReviews(int id, ReviewBanCDto* resultReviewBanDto);
	void unbanReview(int reviewMarkid, int adminId, int reviewId, Review* resultDto);
};

#endif