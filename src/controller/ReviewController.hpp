#ifndef ReviewController_hpp
#define ReviewController_hpp

#include "service/UserService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"


#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class ReviewController : public oatpp::web::server::api::ApiController {
public:
    ReviewController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {}
private:
    ReviewService m_reviewService; // Create user service.
public:
    static std::shared_ptr<ReviewController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ) {
        return std::make_shared<ReviewController>(objectMapper);
    }

    ENDPOINT_INFO(createReview) {
        info->summary = "Create new Review";

        info->addConsumes<Object<ReviewDto>>("application/json");

        info->addResponse<Object<ReviewDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "users", createReview,
        BODY_DTO(Object<CreateReviewDto>, reviewDto))
    {
        return createDtoResponse(Status::CODE_200);
    }

    ENDPOINT_INFO(getReviewById) {
        info->summary = "Get feedback by id";

        info->addResponse<Object<ReviewDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["reviewId"].description = "Review Identifier";
    }
    ENDPOINT("GET", "review/{reviewId}", getReviewById,
        PATH(Int32, reviewId))
    {
        return createDtoResponse(Status::CODE_200, m_reviewService.getReviewById(reviewId));
    }


    ENDPOINT_INFO(getReviews) {
        info->summary = "get all paged review";

        info->addResponse<oatpp::Object<ReviewDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "review/offset/{offset}/limit/{limit}", getReviews,
        PATH(UInt32, offset),
        PATH(UInt32, limit))
    {
        return createDtoResponse(Status::CODE_200, m_reviewService.getReviews(offset, limit));
    }


    ENDPOINT_INFO(getReviewByUserId) {
        info->summary = "get all paged review by user id";

        info->addResponse<oatpp::Object<ReviewDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "review/user/{userId}/offset/{offset}/limit/{limit}", getReviewByUserId,
        PATH(String, userId),
        PATH(UInt32, offset),
        PATH(UInt32, limit))
    {
        return createDtoResponse(Status::CODE_200, m_reviewService.getReviewByUserId(userId, offset, limit));
    }


    ENDPOINT_INFO(getReviewByCourseId) {
        info->summary = "get all paged review by course id";

        info->addResponse<oatpp::Object<ReviewDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "review/courses/{courseId}/offset/{offset}/limit/{limit}", getReviewByCourseId,
        PATH(String, courseId),
        PATH(UInt32, offset),
        PATH(UInt32, limit))
    {
        return createDtoResponse(Status::CODE_200, m_reviewService.getReviewByCourseId(courseId, offset, limit));
    }
    

    ENDPOINT_INFO(likeReview) {
        info->summary = "Update likes in Review by id";

        info->addConsumes<Object<ReviewDto>>("application/json");

        info->addResponse<Object<ReviewDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["reviewId"].description = "Feedback identifier";
    }
    ENDPOINT("PUT", "review/{reviewId}/like", likeReview,
        PATH(Int32, reviewId))
    {
        return createDtoResponse(Status::CODE_200, m_reviewService.likeReview(reviewId));
    }