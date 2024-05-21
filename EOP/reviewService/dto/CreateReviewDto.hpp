#ifndef EOP_REVIEW_CREATEREVIEWDTO_HPP
#define EOP_REVIEW_CREATEREVIEWDTO_HPP

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class CreateReviewDto : public oatpp::DTO
{
    DTO_INIT(CreateReviewDto, DTO)

    DTO_FIELD(String, description, "description");
    DTO_FIELD(Int32, grade, "grade");
    DTO_FIELD(Int32, userId, "userId");
    DTO_FIELD(Int32, courseId, "courseId");
};

#include OATPP_CODEGEN_END(DTO)

#endif
