#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.8...3.18)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(B1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

add_subdirectory(DataDict)
#add_subdirectory(TrackingLib)

find_package(ROOT REQUIRED)
message(STATUS "ROOT LIB : ${ROOT_LIBRARIES}")
message(STATUS "ROOT INC : ${ROOT_INCLUDE_DIR}")

find_package(TrackingLib REQUIRED)
include_directories(${TrackingLib_INCLUDE_DIR})
include_directories(${TrackingLib_INCLUDE_DIR}/Eve/inc)
message(STATUS "TrackingLIB : ${TrackingLib_LIBRARIES}")

include_directories(${ROOT_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/DataDict/inc)
#include_directories(/home/rsehgal/Box_v2/DataDict/inc)
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/DataDict)


#ROOT_GENERATE_DICTIONARY(G__Data include/Data.h  LINKDEF include/DictLinkDef.h)
#add_library(Data SHARED src/Data.cpp  G__Data.cxx)
#target_link_libraries(Data ${ROOT_LIBRARIES})
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${CMAKE_SOURCE_DIR}/src/*.cc ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${CMAKE_SOURCE_DIR}/include/*.hh ${CMAKE_SOURCE_DIR}/include/*.h)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(main main.cc ${sources} ${headers})
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES})

add_executable(Test_POCA_Vis test/Test_POCA_Vis.cpp)
target_link_libraries(Test_POCA_Vis ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES} Geom Eve)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(EXAMPLEB1_SCRIPTS
  box.in
  #main.out
  init_vis.mac
  run1.mac
  run2.mac
  vis.mac
  )

foreach(_script ${EXAMPLEB1_SCRIPTS})
  configure_file(
    ${CMAKE_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


