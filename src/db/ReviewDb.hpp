#ifndef CRUD_REVIEWDB_HPP
#define CRUD_REVIEWDB_HPP

#include "dto/ReviewDto.hpp"
#include "dto/CreateReviewDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * ReviewDb client definitions.
 */
class ReviewDb : public oatpp::orm::DbClient
{
public:
    ReviewDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {
        oatpp::orm::SchemaMigration migration(executor);
        migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
        // TODO - Add more migrations here.
        migration.migrate(); // <-- run migrations. This guy will throw on error.

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("ReviewDb", "Migration - OK. Version=%lld.", version);
    }

    QUERY(createReview,
          "INSERT INTO Review VALUES "
          "(description, grade, userld, courseld, isUpdated, creationDate, updateDate, countLike, countDislike) VALUES "
          "(:review.description, :review.grade, :review.userld, :review.courseld, :review.isUpdated, :review.creationDate, :review.updateDate, :review.countLike, :review.countDislike);",
          PARAM(oatpp::Object<CreateReviewDto>, review))

    QUERY(updateReview,
          "UPDATE Review "
          "SET "
          " updateDate =:review.updateDate , "
          " countLike =:review.countLike , "
          " countDislike =:review.countDislike , "
          "WHERE "
          " id=:review.id;",
          PARAM(oatpp::Object<ReviewDto>, user))

    QUERY(getReviewById,
          "SELECT * FROM Review WHERE id=:id;",
          PARAM(oatpp::Int32, id))

    QUERY(getReviewsByCoursId,
          "SELECT * FROM Review WHERE courseId = :courseId;",
          PARAM(oatpp::UInt32, courseId))

    QUERY(deleteReviewById,
          "DELETE FROM Review WHERE id=:id;",
          PARAM(oatpp::Int32, id))

    QUERY(getReviews,
          "SELECT * FROM Review order by creationDate desc LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))


    QUERY(getReviewByUserId,
          "SELECT * FROM Review WHERE userId=:userId order by creationDate desc LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::String, userId),
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

    QUERY(getReviewByCourseId,
          "SELECT * FROM Review where courseId=:courseId order by creationDate desc LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::String, courseId),
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

    QUERY(banReview,
          "UPDATE Review "
          "SET "
          " isBanned =true , "
          "WHERE "
          " id=:reviewId;",
          PARAM(oatpp::Int32, reviewId))

    QUERY(unbanReview,
          "UPDATE Review "
          "SET "
          " isBanned =false , "
          "WHERE "
          " id=:reviewId;",
          PARAM(oatpp::Int32, reviewId))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif
