cmake_minimum_required(VERSION 3.1)
project(crud)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
add_library(crud-lib SHARED
        "src/controller/ReviewController.hpp"

        "src/db/ReviewDb.hpp"

        "src/dto/CreateReviewDto.hpp"
        "src/dto/PageDto.hpp"
        "src/dto/ReviewDto.hpp"
        "src/dto/StatusDto.hpp"

        "src/service/ReviewService.hpp"
        "src/service/ReviewService.cpp"

        "src/AppComponent.hpp"
        "src/App.cpp"
        "src/ErrorHandler.cpp"
        "src/db/ReviewMarkDb.hpp"
        "src/service/ReviewMarkService.hpp"
        "src/service/ReviewMarkService.cpp"
        "src/dto/ReviewMarkDto.hpp"
        "src/controller/ReviewMarkController.hpp"
        "src/dto/CreateReviewBanDto.hpp"
        "src/dto/ReviewBanDto.hpp"
        "src/db/ReviewBanDb.hpp"

)

## include directories

target_include_directories(crud-lib PUBLIC src)


## link libs

find_package(oatpp)
find_package(oatpp-swagger)
find_package(oatpp-postgresql)


target_link_libraries(crud-lib
        # Oat++
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-postgresql
)

# If CMake can't find SQLite3:
#
# 1. Make sure that you've built oatpp-sqlite with -DOATPP_SQLITE_AMALGAMATION=ON flag
# 2. If you are not willing to use SQLite amalgamation then uncomment the following lines:
#
#find_package(SQLite3 REQUIRED)
#
#target_link_libraries(crud-lib
#        PUBLIC SQLite::SQLite3
#)

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if (CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(crud-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif ()

## add executables

add_executable(crud-exe src/App.cpp "src/ErrorHandler.cpp"
        src/dto/ReviewMarkDto.hpp)
target_link_libraries(crud-exe crud-lib)

##add_executable(crud-test)
##target_link_libraries(crud-test crud-lib)

enable_testing()
add_test(project-tests crud-test)
