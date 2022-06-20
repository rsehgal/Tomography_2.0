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
find_package(ROOT REQUIRED)
message(STATUS "ROOT LIB : ${ROOT_LIBRARIES}")
message(STATUS "ROOT INC : ${ROOT_INCLUDE_DIR}")

find_package(TrackingLib REQUIRED)
include_directories(${TrackingLib_INCLUDE_DIR})
include_directories(${TrackingLib_INCLUDE_DIR}/Eve/inc)
message(STATUS "TrackingLIB : ${TrackingLib_LIBRARIES}")

include_directories(${ROOT_INCLUDE_DIR})
#ROOT_GENERATE_DICTIONARY(G__MuonTrack include/MuonTrack.h  LINKDEF include/DictLinkDef.h)
#add_library(MuonTrack SHARED src/MuonTrack.cpp  G__MuonTrack.cxx)
#target_link_libraries(MuonTrack ${ROOT_LIBRARIES})
#
add_subdirectory(DataDict)
#add_subdirectory(TrackingLib)
link_directories(DataDict)

include_directories(${CMAKE_SOURCE_DIR}/DataDict/inc)
#include_directories(/home/rsehgal/Box_v2/DataDict/inc)
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/DataDict)


#ROOT_GENERATE_DICTIONARY(G__MuonTrack include/MuonTrack.h  LINKDEF include/DictLinkDef.h)
#add_library(MuonTrack SHARED src/MuonTrack.cpp  G__MuonTrack.cxx)
#target_link_libraries(MuonTrack ${ROOT_LIBRARIES})
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

add_executable(Test_POCA_Vis_Recons test/Test_POCA_Vis_Recons.cpp)
target_link_libraries(Test_POCA_Vis_Recons ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES} Geom Eve)

add_executable(Test_Acceptance test/Test_Acceptance.cpp)
target_link_libraries(Test_Acceptance ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES} Geom Eve)

add_executable(Test_DataObject test/Test_DataObject.cpp)
target_link_libraries(Test_DataObject ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES})

add_executable(Test_IncomingOutgoing test/Test_IncomingOutgoing.cpp)
target_link_libraries(Test_IncomingOutgoing ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES})

add_executable(Test_IncomingOutgoing2 test/Test_IncomingOutgoing2.cpp)
target_link_libraries(Test_IncomingOutgoing2 ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES})

add_executable(Test_IncomingOutgoing_v test/Test_IncomingOutgoing_v.cpp ${sources})
target_link_libraries(Test_IncomingOutgoing_v ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES})
add_executable(Test_POCA_Vis_v test/Test_POCA_Vis_v.cpp ${sources} )
target_link_libraries(Test_POCA_Vis_v ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES} Geom Eve)

add_executable(Test_TrueFalsePositive test/Test_TrueFalsePositive.cpp ${sources} )
target_link_libraries(Test_TrueFalsePositive ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES} Geom Eve)



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

include(MacroUtilities)
set(VECGEOM_BACKENDS scalar vc)
enum_option(BACKEND DOC "Vector backend API to be used"
  TYPE STRING
  VALUES ${VECGEOM_BACKENDS}
  CASE_INSENSITIVE)

# Case adjustment because pass to VecCore components is
if(BACKEND STREQUAL "scalar")
  set(BACKEND "Scalar")
elseif(BACKEND STREQUAL "vc")
  set(BACKEND "Vc")
endif()

if("${BACKEND}" MATCHES "Vc")
  set(VecCore_COMPONENTS ${VecCore_COMPONENTS} ${BACKEND})
  add_definitions(-DVECCORE_ENABLE_VC)
endif()


find_package(VecCore REQUIRED)
set(VecCore_VERSION "0.8.0")
message(STATUS ${VecCore_INCLUDE_DIR})
message(STATUS ${VecCore_LIBRARIES})
include_directories(${VecCore_INCLUDE_DIR})
find_package(Vc REQUIRED)
#message(STATUS ${Vc_INCLUDE_DIR})
#message(STATUS ${Vc_LIBRARIES})

find_package(VecGeom REQUIRED)
message(STATUS ${VecGeom_INCLUDE_DIRS})
message(STATUS ${VecGeom_LIBRARIES})
include_directories(${VecGeom_INCLUDE_DIRS})
include_directories(/home/rsehgal/BackBoneSoftwares/VecGeom/include)

include_directories(${Vc_INCLUDE_DIR})

option(USE_FLOAT "Use single precision : float" OFF)

if(USE_FLOAT)
add_definitions(-DVECGEOM_FLOAT_PRECISION)
endif(USE_FLOAT)




set(VECGEOM_ISAS empty)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "(i686|x86_64)")
  set(VECGEOM_ISAS sse2 sse3 ssse3 sse4.1 sse4.2 avx avx2 native empty)
endif()

enum_option(VECGEOM_VECTOR DOC "Vector instruction set to be used"
  TYPE STRING
  VALUES ${VECGEOM_ISAS}
  CASE_INSENSITIVE)


# - ISA-specific flags
string(TOLOWER ${VECGEOM_VECTOR} _arch_lo)
string(TOUPPER ${VECGEOM_VECTOR} _arch_up)

if(${_arch_lo} MATCHES native)
  if(Intel OR IntelLLVM)
    set(VECGEOM_COMPILATION_FLAGS "${VECGEOM_COMPILATION_FLAGS} -march=native")
  elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(powerpc|ppc)64le")
    set(VECGEOM_COMPILATION_FLAGS "${VECGEOM_COMPILATION_FLAGS} -mcpu=${_arch_lo} -mtune=${_arch_lo}")
  else()
    set(VECGEOM_COMPILATION_FLAGS "${VECGEOM_COMPILATION_FLAGS} -march=${_arch_lo}")
  endif()
elseif(NOT ${_arch_lo} MATCHES empty)
  set(VECGEOM_COMPILATION_FLAGS "${VECGEOM_COMPILATION_FLAGS} -m${_arch_lo}")
endif()
message(STATUS "Compiling for ${_arch_up} SIMD architecture")

message(STATUS "Additional Compilation flags : "${VECGEOM_COMPILATION_FLAGS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${_build_type}} ${VECGEOM_COMPILATION_FLAGS}")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${_build_type}} ${VECGEOM_CXX_FLAGS} ${VECGEOM_COMPILATION_FLAGS}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

