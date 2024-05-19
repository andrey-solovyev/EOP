#ifndef ReviewMarkController_hpp
#define ReviewMarkController_hpp

#include "service/ReviewMarkService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * ReviewMarkController REST controller.
 */
class ReviewMarkController : public oatpp::web::server::api::ApiController
{
public:
    ReviewMarkController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {
    }

private:
    ReviewMarkService m_reviewService; // Create user service.
public:
    static std::shared_ptr<ReviewMarkController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
        // Inject objectMapper component here as default parameter
    )
    {
        return std::make_shared<ReviewMarkController>(objectMapper);
    }

    ENDPOINT_INFO(createReviewMark)
    {
        info->summary = "Create new Review Mark";

        info->addConsumes<Object<CreateReviewMarkDto>>("application/json");

        info->addResponse<Object<ReviewMarkDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }

    ENDPOINT("POST", "/reviewMark", createReviewMark,
             BODY_DTO(Object<CreateReviewMarkDto>, reviewDto))
    {
        return createDtoResponse(Status::CODE_200, m_reviewService.createMarkReview(reviewDto));
    }

    ENDPOINT_INFO(getReviewMarkById)
    {
        info->summary = "Get review mark by id";

        info->addResponse<Object<ReviewMarkDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["reviewMarkId"].description = "Review Mark Identifier";
    }

    ENDPOINT("GET", "reviewMark/{reviewMarkId}", getReviewMarkById,
             PATH(Int32, reviewMarkId))
    {
        return createDtoResponse(Status::CODE_200, m_reviewService.getReviewMarkById(reviewMarkId));
    }


    ENDPOINT_INFO(getReviewMarsByReview)
    {
        info->summary = "get all review marks by review";

        info->addResponse<oatpp::Vector<oatpp::Object<ReviewMarkDto>>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }

    ENDPOINT("GET", "review/reviewMark/{reviewId}", getReviewMarsByReview,
             PATH(Int32, reviewId))
    {
        return createDtoResponse(Status::CODE_200, m_reviewService.getReviewMarksByReviewId(reviewId));
    }


    ENDPOINT_INFO(deleteReviewMark)
    {
        info->summary = "get all paged review by user id";

        info->addResponse<oatpp::Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }

    ENDPOINT("DELETE", "reviewMark/{reviewMarkId}", deleteReviewMark,
             PATH(Int32, reviewMarkId))
    {
        return createDtoResponse(Status::CODE_200, m_reviewService.deleteMarkReview(reviewMarkId));
    }
};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif
