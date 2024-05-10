
#ifndef CRUD_USERSERVICE_HPP
#define CRUD_USERSERVICE_HPP

#include "dto/CreateReviewDto.hpp"
#include "dto/StatusDto.hpp"
#include "dto/ReviewDto.hpp"
#include "db/ReviewDb.hpp"


#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class UserService {
private:
	typedef oatpp::web::protocol::http::Status Status;
private:
	OATPP_COMPONENT(std::shared_ptr<ReviewDb>, m_database); // Inject database component
public:

	oatpp::Object<ReviewDto> createReview(const oatpp::Object<CreateReviewDto>& dto);
	oatpp::Object<ReviewDto> updateReview(const oatpp::Object<ReviewDto>& dto);
	oatpp::Object<ReviewDto> getReviewById(const oatpp::Int32& id);
	oatpp::Object<ReviewDto> likeReview(const oatpp::Int32& id);
	oatpp::Object<ReviewDto> deslikeReview(const oatpp::Int32& id);

	oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> getReviews(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
	oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> getReviewsByUserId(const oatpp::String& userId, const oatpp::UInt32& offset, const oatpp::UInt32& limit);
	oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> getReviewsByCourseId(const oatpp::String& courseId, const oatpp::UInt32& offset, const oatpp::UInt32& limit);


};

#endif