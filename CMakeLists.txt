cmake_minimum_required(VERSION 3.1)

set(project_name eop_review)

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        EOP/reviewService/controller/common_interface/ReviewServiceMapper.cpp
        EOP/reviewService/app/ErrorHandler.cpp
        EOP/reviewService/app/init.cpp
        EOP/reviewService/service/ReviewService.cpp
        EOP/reviewService/service/ReviewMarkService.cpp
        EOP/reviewService/main.c
)


target_include_directories(
        ${project_name}-lib PUBLIC EOP/reviewService
        EOP/reviewService/controller/ReviewController.hpp
        EOP/reviewService/controller/ReviewMarkController.hpp

        EOP/reviewService/controller/common_interface/ReviewServiceMapper.hpp

        EOP/reviewService/db/ReviewDb.hpp
        EOP/reviewService/db/ReviewBanDb.hpp
        EOP/reviewService/db/ReviewMarkDb.hpp

        EOP/reviewService/dto/CreateReviewBanDto.hpp
        EOP/reviewService/dto/CreateReviewDto.hpp
        EOP/reviewService/dto/CreateReviewMarkDto.hpp
        EOP/reviewService/dto/ReviewBanDto.hpp
        EOP/reviewService/dto/ReviewDto.hpp
        EOP/reviewService/dto/ReviewMarkDto.hpp

        EOP/reviewService/service/ReviewService.hpp
        EOP/reviewService/service/ReviewMarkService.hpp


        EOP/reviewService/dto/ConfigDto.hpp
        EOP/reviewService/dto/PageDto.hpp
        EOP/reviewService/dto/StatusDto.hpp

        EOP/reviewService/app/AppComponent.hpp
        EOP/reviewService/app/DatabaseComponent.hpp

        EOP/reviewService/ErrorHandler.hpp
        EOP/reviewService/ServiceComponent.hpp
        EOP/reviewService/SwaggerComponent.hpp
        EOP/reviewService/app/init.hpp
        EOP/reviewService/app/init.h
)

## link libs

find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-swagger 1.3.0 REQUIRED)
find_package(oatpp-postgresql 1.3.0 REQUIRED)

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
        EOP/reviewService/main.c
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)