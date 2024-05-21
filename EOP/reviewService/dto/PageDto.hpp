#ifndef EOP_REVIEW_PAGEDTO_HPP
#define EOP_REVIEW_PAGEDTO_HPP

#include "ReviewDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

template<class T>
class PageDto : public oatpp::DTO {

    DTO_INIT(PageDto, DTO)

    DTO_FIELD(UInt32, offset);
    DTO_FIELD(UInt32, limit);
    DTO_FIELD(UInt32, count);
    DTO_FIELD(Vector<T>, items);

};


class ReviewPageDto : public PageDto<oatpp::Object<ReviewDto>> {

    DTO_INIT(ReviewPageDto, PageDto<oatpp::Object<ReviewDto>>)

};

#include OATPP_CODEGEN_END(DTO)

#endif //EOP_REVIEW_PAGEDTO_HPP