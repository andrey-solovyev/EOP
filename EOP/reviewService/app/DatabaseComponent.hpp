#ifndef EOP_REVIEW_DATABASECOMPONENT_HPP
#define EOP_REVIEW_DATABASECOMPONENT_HPP

#include <db/ReviewBanDb.hpp>
#include <db/ReviewDb.hpp>
#include <db/ReviewMarkDb.hpp>
#include <dto/ConfigDto.hpp>

class DatabaseComponent {
public:

	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::postgresql::Connection>>, dbConnectionProvider)([] {

		/* Create database-specific ConnectionProvider */
		OATPP_COMPONENT(oatpp::Object<ConfigDto>, config); // Get config component

		/* Create database-specific ConnectionProvider */
		auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(config->dbConnectionString);

		/* Create database-specific ConnectionPool */
		return oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
			10 /* max-connections */,
			std::chrono::seconds(5) /* connection TTL */);

		}());

	/**
	   * Create database client
	   */
	OATPP_CREATE_COMPONENT(std::shared_ptr<ReviewBanDb>, reviewBanDb)([] {

		/* Get database ConnectionProvider component */
		OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::postgresql::Connection>>, connectionProvider);

		/* Create database-specific Executor */
		auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionProvider);

		/* Create MyClient database client */
		return std::make_shared<ReviewBanDb>(executor);

		}());


	/**
	 * Create database client
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<ReviewDb>, reviewDb)([] {

		/* Get database ConnectionProvider component */
		OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::postgresql::Connection>>, connectionProvider);

		/* Create database-specific Executor */
		auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionProvider);

		/* Create MyClient database client */
		return std::make_shared<ReviewDb>(executor);

		}());

	/**
		* Create database client
		*/
	OATPP_CREATE_COMPONENT(std::shared_ptr<ReviewMarkDb>, reviewMarkDb)([] {

		/* Get database ConnectionProvider component */
		OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::postgresql::Connection>>, connectionProvider);

		/* Create database-specific Executor */
		auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionProvider);

		/* Create MyClient database client */
		return std::make_shared<ReviewMarkDb>(executor);

		}());
};

#endif //EOP_REVIEW_DATABASECOMPONENT_HPP

