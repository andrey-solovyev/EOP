
#ifndef EOP_REVIEW_REVIEWSERVICE_HPP
#define EOP_REVIEW_REVIEWSERVICE_HPP

#include <db/ReviewBanDb.hpp>
#include <dto/CreateReviewDto.hpp>
#include <dto/ReviewDto.hpp>
#include <dto/PageDto.hpp>
#include <db/ReviewDb.hpp>
#include <dto/CreateReviewBanDto.hpp>
#include <dto/ReviewBanDto.hpp>


#include <oatpp/web/protocol/http/Http.hpp>
#include <oatpp/core/macro/component.hpp>

class ReviewService {
private:
	typedef oatpp::web::protocol::http::Status Status;
	OATPP_COMPONENT(std::shared_ptr<ReviewDb>, m_database); // Inject database component
	OATPP_COMPONENT(std::shared_ptr<ReviewBanDb>, m_database_ban);
public:

	oatpp::Object<ReviewDto> createReview(const oatpp::Object<CreateReviewDto>& dto);
	oatpp::Object<ReviewDto> updateReview(const oatpp::Object<ReviewDto>& dto);
	oatpp::Object<ReviewDto> getReviewById(const oatpp::Int32& id);
	oatpp::Object<ReviewDto> getLikes(const oatpp::Int32& id);
	oatpp::Object<ReviewDto> getDislikes(const oatpp::Int32& id);

	oatpp::Object<ReviewBanDto> ReviewService::getBanReviewById(const oatpp::Int32& id);
	oatpp::Object<ReviewBanDto> banReview(const oatpp::Object<CreateReviewBanDto>& dto);
	oatpp::Vector<oatpp::Object<ReviewBanDto>> getBanReviews(const oatpp::Int32& id);
	oatpp::Object<ReviewDto> unbanReview(const oatpp::Int32& reviewMarkid, const oatpp::Int32& adminId, const oatpp::Int32& reviewId);


	oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> getReviews(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
	oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> getReviewByUserId(const oatpp::Int32& userId, const oatpp::UInt32& offset, const oatpp::UInt32& limit);
	oatpp::Object<PageDto<oatpp::Object<ReviewDto>>> getReviewByCourseId(const oatpp::Int32& courseId, const oatpp::UInt32& offset, const oatpp::UInt32& limit);
};

#endif