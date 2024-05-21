#include <init.h>
#include <init.hpp>

void run(int argc, const char* argv[]) {
    oatpp::base::Environment::init();
    auto args = oatpp::base::CommandLineArguments(argc, argv);
    AppComponent appComponent(args);
    ServiceComponent serviceComponent;
    SwaggerComponent swaggerComponent;
    DatabaseComponent databaseComponent;

    /* create ApiControllers and add endpoints to router */

    auto router = serviceComponent.httpRouter.getObject();
    oatpp::web::server::api::Endpoints docEndpoints;

    docEndpoints.append(router->addController(ReviewController::createShared())->getEndpoints());
    docEndpoints.append(router->addController(ReviewMarkController::createShared())->getEndpoints());

    router->addController(oatpp::swagger::Controller::createShared(docEndpoints));

    /* create server */

    oatpp::network::Server server(serviceComponent.serverConnectionProvider.getObject(),
        serviceComponent.serverConnectionHandler.getObject());

    OATPP_LOGD("Server", "Running on port %s...", serviceComponent.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());

    server.run();

    oatpp::base::Environment::destroy();
}