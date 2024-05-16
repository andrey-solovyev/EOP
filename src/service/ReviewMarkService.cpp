#include "ReviewMarkService.hpp"


oatpp::Object<ReviewMarkDto> ReviewMarkService::createMarkReview(const oatpp::Object<CreateReviewMarkDto>& dto) {

    auto dbResult = m_database->createReview(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto id = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getReviewMarkById((v_int32)id);

}

oatpp::Object<ReviewMarkDto> ReviewMarkService::getReviewMarkById(const oatpp::Int32& id) {

    auto dbResult = m_database->getReviewMarkById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Feedback not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewMarkDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}

oatpp::Vector<oatpp::Object<ReviewMarkDto>> ReviewMarkService::getReviewMarksByReviewId(const oatpp::Int32& reviewId)
{

    auto dbResult = m_database->getReviewMarkByRevievId(reviewId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ReviewMarkDto>>>();
    return items;
};

oatpp::Object<StatusDto> ReviewMarkService::deleteMarkReview(const oatpp::Int32& id)
{
    auto dbResult = m_database->getReviewMarkById(id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    m_database->deleteReviewMarkById(id);
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Review mark was successfully deleted";
    return status;
}

