#ifndef CreateReviewMarkDto_hpp
#define CreateReviewMarkDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class CreateReviewMarkDto : public oatpp::DTO {

    DTO_INIT(CreateReviewMarkDto, DTO)

    DTO_FIELD(Int32, userId, "userId");
    DTO_FIELD(Int32, reviewId, "reviewId");
    DTO_FIELD(Int32, mark, "mark");

};

#include OATPP_CODEGEN_END(DTO)

#endif