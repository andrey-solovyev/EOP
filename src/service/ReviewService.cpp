#include "ReviewService.hpp"

oatpp::Object<ReviewDto> ReviewService::createReview(const oatpp::Object<CreateReviewDto>& dto) {

	auto dbResult = m_database->createReview(dto);
	OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto id = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

	return getReviewById((v_int32)id);

}

oatpp::Object<ReviewDto> ReviewService::updateReview(const oatpp::Object<ReviewDto>& dto) {

    auto dbResult = m_database->updateReview(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return FeedbackService::getReviewById(dto->id);

}

oatpp::Object<ReviewDto> ReviewService::getReviewById(const oatpp::Int32& id) {

    auto dbResult = m_database->getReviewById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Feedback not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}

oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> ReviewService::getReviews(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getReviews(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewDto>>>();

    auto page = PageDto<oatpp::Object<ReviewDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;

}



oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> ReviewService::getReviewByUserId(const oatpp::String& userId, const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getReviewByUserId(userId, offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewDto>>>();

    auto page = PageDto<oatpp::Object<ReviewDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;

}

oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> ReviewService::getReviewByCourseId(const oatpp::String& courseId, const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getReviewByCourseId(courseId, offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewDto>>>();

    auto page = PageDto<oatpp::Object<ReviewDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;

}


oatpp::Object<ReviewDto> ReviewService::likeReview(const oatpp::Int32& id) {

    auto dbResult = m_database->getReviewById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Feedback not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}

oatpp::Object<ReviewDto> ReviewService::deslikeReview(const oatpp::Int32& id) {

    auto dbResult = m_database->getReviewById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Feedback not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}