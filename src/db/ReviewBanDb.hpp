#ifndef CRUD_REVIEWBANDB_HPP
#define CRUD_REVIEWBANDB_HPP

#include "dto/CreateReviewBanDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * ReviewBanDb client definitions.
 */
class ReviewBanDb : public oatpp::orm::DbClient
{
public:
    ReviewBanDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {
        oatpp::orm::SchemaMigration migration(executor);

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("ReviewBanDb", "Migration - OK. Version=%lld.", version);
    }

    QUERY(createReviewBan,
          "INSERT INTO ReviewBan VALUES "
          "(adminId, reviewId, description) VALUES "
          "(:review.adminId, :review.reviewId, :review.description);",
          PARAM(oatpp::Object<CreateReviewBanDto>, review))

    QUERY(deleteReviewBanById,
          "DELETE FROM ReviewBan WHERE id=:id;",
          PARAM(oatpp::Int32, id))

    QUERY(getReviewBanById,
              "SELECT * FROM ReviewBan WHERE id=:id;",
              PARAM(oatpp::Int32, id))

    QUERY(getReviewBanByRevievId,
          "SELECT * FROM ReviewBan WHERE reviewId = :reviewId;",
          PARAM(oatpp::Int32, reviewId))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif