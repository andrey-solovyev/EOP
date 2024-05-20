#include "ReviewServiceMapper.hpp"
#include "CreateReviewInt.h"


oatpp::Object<CreateReviewDto> ReviewServiceMapper::mapDtoToCreateReview(const CreateReviewInt* create_review)
{
    oatpp::Object<CreateReviewDto> createReviewDto;

    createReviewDto->description = (create_review->description);
    createReviewDto->grade = (create_review->grade);
    createReviewDto->userId = (create_review->userId);
    createReviewDto->courseId = (create_review->courseId);

    return createReviewDto;
}

oatpp::Object<ReviewDto> ReviewServiceMapper::mapDtoToReview(const Review* review)
{
    oatpp::Object<ReviewDto> createReviewDto;

    createReviewDto->id = review->id;
    createReviewDto->description = (review->description);
    createReviewDto->grade = (review->grade);
    createReviewDto->userId = (review->userId);
    createReviewDto->courseId = (review->courseId);
    createReviewDto->creationDate = review->creationDate;
    createReviewDto->updateDate = review->updateDate;

    return createReviewDto;
}


void ReviewServiceMapper::mapDtoToReview(const oatpp::Object<ReviewDto>& dto, Review* review)
{
    review->id = dto->id;
    review->description = (char*)dto->description->c_str();
    review->grade = (int)dto->grade;
    review->userId = (int)dto->userId;
    review->courseId = (int)dto->courseId;
    review->creationDate = (char*)dto->creationDate->c_str();
    review->updateDate = (char*)dto->updateDate->c_str();
}

oatpp::Object<CreateReviewBanDto> ReviewServiceMapper::mapToReviewBanOatpp(const CreateReviewBanCDto* dto)
{
    oatpp::Object<CreateReviewBanDto> createReviewBanDto;
    createReviewBanDto->adminId = (dto->adminId);
    createReviewBanDto->reviewId = (dto->reviewId);
    createReviewBanDto->description = (dto->description);
    return createReviewBanDto;
}

oatpp::Object<ReviewBanDto> ReviewServiceMapper::mapToOatpp(const ReviewBanCDto* dto)
{
    oatpp::Object<ReviewBanDto> reviewBanDto;

    reviewBanDto->id = (dto->id);
    reviewBanDto->adminId = (dto->adminId);
    reviewBanDto->reviewId = (dto->reviewId);
    reviewBanDto->description = (dto->description);
    return reviewBanDto;
};


void ReviewServiceMapper::createReview(CreateReviewInt* dto, Review* resultReview)
{
    auto reviewOatpp = mapDtoToCreateReview(dto);
    auto resultRerviewOatpp = m_reviewService->createReview(reviewOatpp);
    mapDtoToReview(resultRerviewOatpp, resultReview);
};

void ReviewServiceMapper::updateReview(Review* dto, Review* resultDto)
{
    auto reviewOatpp = mapDtoToReview(dto);
    auto resultRerviewOatpp = m_reviewService->updateReview(reviewOatpp);
    mapDtoToReview(resultRerviewOatpp, resultDto);
};

void ReviewServiceMapper::getReviewById(const int id, Review* resultDto)
{
    const oatpp::Int32& int_as_oatpp_int = static_cast<const oatpp::Int32&>(id);
    auto resultRerviewOatpp = m_reviewService->getReviewById(int_as_oatpp_int);
    mapDtoToReview(resultRerviewOatpp, resultDto);
};

void ReviewServiceMapper::getLikes(const int id, Review* resultDto)
{
    const oatpp::Int32& int_as_oatpp_int = static_cast<const oatpp::Int32&>(id);
    auto resultRerviewOatpp = m_reviewService->getLikes(int_as_oatpp_int);
    mapDtoToReview(resultRerviewOatpp, resultDto);
};

void ReviewServiceMapper::getDislikes(const int id, Review* resultDto)
{
    const oatpp::Int32& int_as_oatpp_int = static_cast<const oatpp::Int32&>(id);
    auto resultRerviewOatpp = m_reviewService->getDislikes(int_as_oatpp_int);
    mapDtoToReview(resultRerviewOatpp, resultDto);
};

void ReviewServiceMapper::getReviews(const int offset, const int limit, PageCDto* pageDto)
{
    const oatpp::UInt32& offsetParse = static_cast<const oatpp::UInt32&>(offset);
    const oatpp::UInt32& limitParse = static_cast<const oatpp::UInt32&>(limit);
    auto resultRerviewOatpp = m_reviewService->getReviews(offsetParse, limitParse);
}

void ReviewServiceMapper::getReviewByUserId(int userId, int offset, int limit, PageCDto* pageDto)
{
    const oatpp::UInt32& offsetParse = static_cast<const oatpp::UInt32&>(offset);
    const oatpp::UInt32& limitParse = static_cast<const oatpp::UInt32&>(limit);
    auto resultRerviewOatpp = m_reviewService->getReviewByUserId(userId, offsetParse, limitParse);
}

void ReviewServiceMapper::getReviewByCourseId(int courseId, const int offset, const int limit,
                                              PageCDto* pageDto)
{
    const oatpp::UInt32& offsetParse = static_cast<const oatpp::UInt32&>(offset);
    const oatpp::UInt32& limitParse = static_cast<const oatpp::UInt32&>(limit);
    auto resultRerviewOatpp = m_reviewService->getReviewByCourseId(courseId, offsetParse, limitParse);
}

void ReviewServiceMapper::getBanReviewById(const int id, ReviewBanCDto* reviewBanDto)
{
    const oatpp::Int32& banReviewId = static_cast<const oatpp::Int32&>(id);
    auto reviewBan = m_reviewService->getBanReviewById(banReviewId);
};

void ReviewServiceMapper::banReview(CreateReviewBanCDto* dto, ReviewBanCDto* resultReviewBan)
{
    auto crateReviewBanDto = mapToReviewBanOatpp(dto);
    auto reviewBanDto = m_reviewService->banReview(crateReviewBanDto);
}

void ReviewServiceMapper::getBanReviews(const int id, ReviewBanCDto* resultReviewBanDto)
{
    const oatpp::Int32& banReviewIds = static_cast<const oatpp::Int32&>(id);
    auto reviewBans = m_reviewService->getBanReviews(banReviewIds);
    // ReviewBanCDto* reviewBansArray = new ReviewBanCDto[reviewBans->max_size()];
    // for (int i = 0; i < reviewBans->max_size(); i++)
    // {
    //     oatpp::Object<ReviewBanCDto> reviewBanDto = reviewBans[i];
    //     reviewBansArray[i].id = reviewBanDto->id;
    //     reviewBansArray[i].adminId = reviewBanDto->adminId;
    //     reviewBansArray[i].reviewId = reviewBanDto->reviewId;
    //     reviewBansArray[i].description = reviewBanDto->description;
    //     reviewBansArray[i].creationDate = reviewBanDto->creationDate;
    // }
    // resultReviewBanDto = reviewBansArray;
}

void ReviewServiceMapper::unbanReview(const int reviewMarkid, const int adminId, const int reviewId, Review* resultDto)
{
    const oatpp::Int32& reviewMarkidParse = static_cast<const oatpp::Int32&>(reviewMarkid);
    const oatpp::Int32& adminIdParse = static_cast<const oatpp::Int32&>(adminId);
    const oatpp::Int32& reviewIdParce = static_cast<const oatpp::Int32&>(reviewId);
    auto review = m_reviewService->unbanReview(reviewMarkidParse, adminIdParse, reviewIdParce);
    mapDtoToReview(review, resultDto);
}
