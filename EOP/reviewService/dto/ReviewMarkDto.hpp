#ifndef EOP_REVIEW_REVIEWMARKDTO_HPP
#define EOP_REVIEW_REVIEWMARKDTO_HPP

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)


class ReviewMarkDto : public oatpp::DTO {

    DTO_INIT(ReviewMarkDto, DTO)

    DTO_FIELD(Int32, id, "id");
    DTO_FIELD(Int32, userId, "userId");
    DTO_FIELD(Int32, reviewId, "reviewId");
    DTO_FIELD(Int32, mark, "mark");
    DTO_FIELD(String, creationDate, "creationDate");


};

#include OATPP_CODEGEN_END(DTO)

#endif