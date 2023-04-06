cmake_minimum_required(VERSION 3.18)

project(spider)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#file(GLOB SRC "src/*.cpp" "src/PCA/I2CPeripheral_local.cpp" "src/PCA/PCA9685.cpp")
file(GLOB SRC "src/*.cpp" "src/PCA/I2CPeripheral.cpp" "src/PCA/PCA9685.cpp")
include_directories("include/")

add_executable(spider ${SRC})
target_link_libraries(spider i2c)