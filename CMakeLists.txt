cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico-fc)

# Initialize the SDK
pico_sdk_init()

add_subdirectory(${CMAKE_SOURCE_DIR}/pico-servo)

set(sources
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/src/receiver.h
    ${CMAKE_SOURCE_DIR}/src/receiver.c
)

if (${IMU_BNO055})
    set(sources ${sources} ${CMAKE_SOURCE_DIR}/src/imu_bno055.c)
endif()

if (${BAR_BMP388})
    set(sources ${sources} ${CMAKE_SOURCE_DIR}/src/bar_bmp388.c)
endif()

add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE include pico-servo/include)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_pwm hardware_i2c hardware_spi pico-servo)

