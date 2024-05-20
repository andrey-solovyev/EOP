 
cmake_minimum_required(VERSION 3.1)

set(project_name eop_review)

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        EOP_reviewService/controller/common_interface/CreateReviewInt.c
        EOP_reviewService/controller/common_interface/ReviewServiceMapper.cpp
)

target_include_directories(
        EOP_reviewService/controller/ReviewController.hpp
        EOP_reviewService/controller/ReviewMarkController.hpp

        EOP_reviewService/controller/common_interface/CreateReviewInt.h
        EOP_reviewService/controller/common_interface/ReviewServiceMapper.hpp

        EOP_reviewService/db/ReviewDb.hpp
        EOP_reviewService/db/ReviewBanDb.hpp
        EOP_reviewService/db/ReviewMarkDb.hpp

        EOP_reviewService/dto/CreateReviewBanDto.hpp
        EOP_reviewService/dto/CreateReviewDto.hpp
        EOP_reviewService/dto/CreateReviewMarkDto.hpp
        EOP_reviewService/dto/ReviewBanDto.hpp
        EOP_reviewService/dto/ReviewDto.hpp
        EOP_reviewService/dto/ReviewMarkDto.hpp

        EOP_reviewService/service/ReviewService.hpp
        EOP_reviewService/service/ReviewService.cpp
        EOP_reviewService/service/ReviewMarkService.hpp
        EOP_reviewService/service/ReviewMarkService.cpp

        EOP_reviewService/dto/ConfigDto.hpp
        EOP_reviewService/dto/PageDto.hpp
        EOP_reviewService/dto/StatusDto.hpp

        EOP_reviewService/AppComponent.hpp
        EOP_reviewService/DatabaseComponent.hpp
        EOP_reviewService/ErrorHandler.cpp
        EOP_reviewService/ErrorHandler.hpp
        EOP_reviewService/ServiceComponent.hpp
        EOP_reviewService/SwaggerComponent.hpp
)

target_include_directories(${project_name}-lib PUBLIC EOP_reviewService)

## link libs

find_package(oatpp              1.3.0 REQUIRED)
find_package(oatpp-swagger      1.3.0 REQUIRED)
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
        EOP_reviewService/main.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

 
