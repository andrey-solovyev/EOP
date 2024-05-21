#ifndef EOP_REVIEW_REVIEWDB_HPP
#define EOP_REVIEW_REVIEWDB_HPP

#include <dto/ReviewDto.hpp>
#include <dto/CreateReviewDto.hpp>
#include <oatpp-postgresql/orm.hpp>

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
          "INSERT INTO review.review   "
          "(description, grade, user_id, course_id ) VALUES "
          "(:review.description, :review.grade, :review.userId, :review.courseId ) returning <!!  id, description, grade, user_id as \"userId\", course_id as \"courseId\", CAST(creation_date AS text)   as \"creationDate\", CAST(update_date AS text)   as \"updateDate\" !!>;",
          PARAM(oatpp::Object<CreateReviewDto>, review))

    QUERY(updateReview,
          "UPDATE review.review "
          "SET "
          " description =:review.description, "
          " grade =:review.grade, "
          " update_date =:review.updateDate, "
          "WHERE "
          " id=:review.id;",
          PARAM(oatpp::Object<ReviewDto>, review))

    QUERY(getReviewById,
          "SELECT <!!  id, description, grade, user_id as \"userId\", course_id as \"courseId\", CAST(creation_date AS text)   as \"creationDate\", CAST(update_date AS text)   as \"updateDate\" !!> FROM review.review WHERE id=:id;",
          PARAM(oatpp::Int32, id))

    QUERY(getReviewsByCoursId,
          "SELECT <!!  id, description, grade, user_id as \"userId\", course_id as \"courseId\", CAST(creation_date AS text)   as \"creationDate\", CAST(update_date AS text)   as \"updateDate\" !!> FROM review.review WHERE courseId = :courseId;",
          PARAM(oatpp::UInt32, courseId))

    QUERY(deleteReviewById,
          "DELETE FROM Review WHERE id=:id;",
          PARAM(oatpp::Int32, id))

    QUERY(getReviews,
          "SELECT <!!  id, description, grade, user_id as \"userId\", course_id as \"courseId\", CAST(creation_date AS text)   as \"creationDate\", CAST(update_date AS text)   as \"updateDate\" !!> FROM review.review order by creation_date desc LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))


    QUERY(getReviewByUserId,
          "SELECT <!!  id, description, grade, user_id as \"userId\", course_id as \"courseId\", CAST(creation_date AS text)   as \"creationDate\", CAST(update_date AS text)   as \"updateDate\" !!> FROM review.review WHERE user_id=:userId order by creation_date desc LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::Int32, userId),
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

    QUERY(getReviewByCourseId,
          "SELECT <!!  id, description, grade, user_id as \"userId\", course_id as \"courseId\", CAST(creation_date AS text)   as \"creationDate\", CAST(update_date AS text)   as \"updateDate\" !!>  FROM review.review where course_id=:courseId order by creation_date desc LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::Int32, courseId),
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

 

    QUERY(banReview,
          "UPDATE review.review "
          "SET "
          " is_banned =true , "
          "WHERE "
          " id=:reviewId;",
          PARAM(oatpp::Int32, reviewId))

    QUERY(unbanReview,
          "UPDATE review.review "
          "SET "
          " is_banned =false , "
          "WHERE "
          " id=:reviewId;",
          PARAM(oatpp::Int32, reviewId))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif
