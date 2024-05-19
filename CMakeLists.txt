 
cmake_minimum_required(VERSION 3.1)

set(project_name eop_review)

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib

    src/controller/ReviewController.hpp
    src/controller/ReviewMarkController.hpp

    src/db/ReviewDb.hpp
    src/db/ReviewBanDb.hpp
    src/db/ReviewMarkDb.hpp

    src/dto/CreateReviewBanDto.hpp
    src/dto/CreateReviewDto.hpp
    src/dto/CreateReviewMarkDto.hpp
    src/dto/ReviewBanDto.hpp
    src/dto/ReviewDto.hpp
    src/dto/ReviewMarkDto.hpp

    src/service/ReviewService.hpp
    src/service/ReviewService.cpp
    src/service/ReviewMarkService.hpp
    src/service/ReviewMarkService.cpp

    src/dto/ConfigDto.hpp
    src/dto/PageDto.hpp
    src/dto/StatusDto.hpp

    src/AppComponent.hpp
    src/DatabaseComponent.hpp
    src/ErrorHandler.cpp
    src/ErrorHandler.hpp
    src/ServiceComponent.hpp
    src/SwaggerComponent.hpp
)

target_include_directories(${project_name}-lib PUBLIC src)

## link libs

find_package(oatpp              1.3.0 REQUIRED)
find_package(oatpp-swagger      )
find_package(oatpp-postgresql   1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-postgresql
)

add_definitions(
        # Path to swagger-ui resources #
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        # Path to config file #
        -DCONFIG_PATH="${CMAKE_CURRENT_LIST_DIR}/resources/config.json"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

#################################################################
## add executables

add_executable(${project_name}-exe
        src/App.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

 
