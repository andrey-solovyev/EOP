#ifndef CreateReviewBanDto_hpp
#define CreateReviewBanDto_hpp

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class CreateReviewBanDto : public oatpp::DTO {

    DTO_INIT(CreateReviewBanDto, DTO)

    DTO_FIELD(Int32, adminId, "adminId");
    DTO_FIELD(Int32, reviewId, "reviewId");
    DTO_FIELD(String, description, "description");

};

#include OATPP_CODEGEN_END(DTO)

#endif