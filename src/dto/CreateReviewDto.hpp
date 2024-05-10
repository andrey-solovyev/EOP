#ifndef CreateReviewDto_hpp
#define CreateReviewDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(Role, v_int32,
    VALUE(GUEST, 0, "ROLE_GUEST"),
    VALUE(ADMIN, 1, "ROLE_ADMIN")
)

class CreateReviewDto : public oatpp::DTO {

    DTO_INIT(CreateReviewDto, DTO)

    DTO_FIELD(String, description, "description");
    DTO_FIELD(String, grade, "grade");
    DTO_FIELD(Int32, userId, "userId");
    DTO_FIELD(Int32, courseId, "courseId");
};

#include OATPP_CODEGEN_END(DTO)

#endif