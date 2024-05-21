#ifndef ReviewDto_hpp
#define ReviewDto_hpp

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class ReviewDto : public oatpp::DTO {

    DTO_INIT(ReviewDto, DTO)

    DTO_FIELD(Int32, id, "id");
    DTO_FIELD(String, description, "description");
    DTO_FIELD(Int32, grade, "grade");
    DTO_FIELD(Int32, userId, "userId");
    DTO_FIELD(Int32, courseId, "courseId");
    DTO_FIELD(String, creationDate, "creationDate");
    DTO_FIELD(String, updateDate, "updateDate");
};

#include OATPP_CODEGEN_END(DTO)

#endif