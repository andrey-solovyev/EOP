#include <reviewService/service//ReviewService.hpp>

oatpp::Object<ReviewDto> ReviewService::createReview(const oatpp::Object<CreateReviewDto>& dto)
{
    auto dbResult = m_database->createReview(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewDto>>>();

    return result[0];
}

oatpp::Object<ReviewDto> ReviewService::updateReview(const oatpp::Object<ReviewDto>& dto)
{
    auto dbResult = m_database->updateReview(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return ReviewService::getReviewById(dto->id);
}

oatpp::Object<ReviewDto> ReviewService::getReviewById(const oatpp::Int32& id)
{
    auto dbResult = m_database->getReviewById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Feedback not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<ReviewBanDto> ReviewService::getBanReviewById(const oatpp::Int32& id)
{
    auto dbResult = m_database_ban->getReviewBanById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Feedback not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewBanDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}


oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> ReviewService::getReviews(
    const oatpp::UInt32& offset, const oatpp::UInt32& limit)
{
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10)
    {
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


oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> ReviewService::getReviewByUserId(
    const oatpp::Int32& userId, const oatpp::UInt32& offset, const oatpp::UInt32& limit)
{
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10)
    {
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

oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> ReviewService::getReviewByCourseId(
    const oatpp::Int32& courseId, const oatpp::UInt32& offset, const oatpp::UInt32& limit)
{
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10)
    {
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


oatpp::Object<ReviewDto> ReviewService::getLikes(const oatpp::Int32& id)
{
    auto dbResult = m_database->getReviewById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Feedback not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<ReviewDto> ReviewService::getDislikes(const oatpp::Int32& id)
{
    auto dbResult = m_database->getReviewById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Feedback not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<ReviewBanDto> ReviewService::banReview(const oatpp::Object<CreateReviewBanDto>& dto)
{
    m_database->banReview(dto->reviewId);
    auto dbResult = m_database_ban->createReviewBan(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewBanDto>>>();

    return result[0];
}


oatpp::Vector<oatpp::Object<ReviewBanDto>> ReviewService::getBanReviews(const oatpp::Int32& reviewId)
{
    auto dbResult = m_database_ban->getReviewBanByRevievId(reviewId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewBanDto>>>();
    return items;
};


oatpp::Object<ReviewDto> ReviewService::unbanReview(const oatpp::Int32& reviewMarkId, const oatpp::Int32& adminId,
                                                       const oatpp::Int32& reviewId)
{
    m_database->unbanReview(reviewId);
    auto dbResult = m_database_ban->deleteReviewBanById(reviewMarkId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return getReviewById(reviewId);
}
