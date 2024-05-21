#ifndef ReviewBanDto_hpp
#define ReviewBanDto_hpp

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class ReviewBanDto : public oatpp::DTO
{
    DTO_INIT(ReviewBanDto, DTO)

    DTO_FIELD(Int32, id, "id");
    DTO_FIELD(Int32, adminId, "adminId");
    DTO_FIELD(Int32, reviewId, "reviewId");
    DTO_FIELD(String, description, "description");
    DTO_FIELD(String, creationDate, "creationDate");
};

#include OATPP_CODEGEN_END(DTO)

#endif
