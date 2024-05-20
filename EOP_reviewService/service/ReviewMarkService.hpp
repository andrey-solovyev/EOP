#ifndef CRUD_REVIEWMARKSERVICE_HPP
#define CRUD_REVIEWMARKSERVICE_HPP

#include <dto/CreateReviewMarkDto.hpp>

#include "db/ReviewMarkDb.hpp"
#include "dto/ReviewMarkDto.hpp"
#include "dto/StatusDto.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class ReviewMarkService {
private:
    typedef oatpp::web::protocol::http::Status Status;
    OATPP_COMPONENT(std::shared_ptr<ReviewMarkDb>, m_database); // Inject database component
public:

    oatpp::Object<ReviewMarkDto> createMarkReview(const oatpp::Object<CreateReviewMarkDto>& dto);
    oatpp::Object<ReviewMarkDto> getReviewMarkById(const oatpp::Int32& id);
    oatpp::Object<StatusDto> deleteMarkReview(const oatpp::Int32& id);

    oatpp::Vector<oatpp::Object<ReviewMarkDto>> getReviewMarksByReviewId(const oatpp::Int32& reviewId);

};

#endif