cmake_minimum_required(VERSION 2.8)
PROJECT(SENSOR_DRIVER_VIRTUAL)

include(FindPkgConfig)

#dependencies
find_package(PkgConfig REQUIRED)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE RELEASE)


set(DRIVER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sensor-drivers)
set(ACTUATOR_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/actuator-drivers)

set(sensor_driver_sources 
  ${DRIVER_SOURCE_DIR}/driver_common.c 
  ${DRIVER_SOURCE_DIR}/sensor1_virt1.c 
  ${DRIVER_SOURCE_DIR}/sensor2_virt2.c 
  ${DRIVER_SOURCE_DIR}/sensor3_virt3.c 
)

set(actuator_driver_sources
  ${ACTUATOR_SOURCE_DIR}/actuator1_virt_act1.c
)

add_definitions(-Wl,-Wall -O2 -fPIC -rdynamic) 

include_directories( 
  /usr/include
  /usr/local/include
  ${CMAKE_CURRENT_SOURCE_DIR}/sensor-drivers
)
link_directories(
  /usr/lib
  /usr/local/lib
	/usr/local/lib/pkgconfig
  #/usr/lib/arm-linux-gnueabihf/pkgconfig
)


add_library(sensors SHARED ${sensor_driver_sources})
add_library(actuators SHARED ${actuator_driver_sources})

target_link_libraries(sensors
)

set_target_properties( sensors
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/device-drivers
)

set_target_properties( actuators
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/device-drivers
)
add_custom_target(
  make-sensor-driver-dir ALL
  COMMAND mkdir -p ${CMAKE_SOURCE_DIR}/out/device-drivers
  COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/sensor_config.json ${CMAKE_SOURCE_DIR}/out/device-drivers/sensor_config.json
  COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/actuator_config.json ${CMAKE_SOURCE_DIR}/out/device-drivers/actuator_config.json
  COMMENT "make sensor driver directory"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
