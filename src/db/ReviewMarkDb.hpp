#ifndef CRUD_REVIEWMARKDB_HPP
#define CRUD_REVIEWMARKDB_HPP

#include "dto/CreateReviewMarkDto.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * ReviewMarkDb client definitions.
 */
class ReviewMarkDb : public oatpp::orm::DbClient
{
public:
    ReviewMarkDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {
        oatpp::orm::SchemaMigration migration(executor);

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("ReviewMarkDb", "Migration - OK. Version=%lld.", version);
    }

    QUERY(createReview,
          "INSERT INTO review_mark VALUES "
          "(user_id, review_id, mark) VALUES "
          "(:review.userId, :review.reviewId, :review.mark);",
          PARAM(oatpp::Object<CreateReviewMarkDto>, review))

    QUERY(deleteReviewMarkById,
          "DELETE FROM review_mark WHERE id=:id;",
          PARAM(oatpp::Int32, id))

    QUERY(getReviewMarkById,
              "SELECT * FROM review_mark WHERE id=:id;",
              PARAM(oatpp::Int32, id))

    QUERY(getReviewMarkByRevievId,
          "SELECT * FROM review_mark WHERE review_id = :reviewId;",
          PARAM(oatpp::Int32, reviewId))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif