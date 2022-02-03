cmake_minimum_required (VERSION 2.6)

project (RootDict)


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/inc)


ROOT_GENERATE_DICTIONARY(G__ABData inc/A.h inc/B.h  inc/Data.h LINKDEF inc/DictLinkDef.h)
add_library(ABData SHARED src/A.cpp src/B.cpp src/Data.cpp G__ABData.cxx)
target_link_libraries(ABData ${ROOT_LIBRARIES})

add_executable(RootDict RootDict.cpp)
target_link_libraries(RootDict ABData)

add_executable(ReadTree ReadTree.cpp)
target_link_libraries(ReadTree ABData)

add_executable(WriteDict WriteDict.cpp)
target_link_libraries(WriteDict ABData)

add_executable(ReadObject ReadObject.cpp)
target_link_libraries(ReadObject ABData)

add_executable(WriteDictWithVector WriteDictWithVector.cpp)
target_link_libraries(WriteDictWithVector ABData)

add_executable(ReadDictWithVector ReadDictWithVector.cpp)
target_link_libraries(ReadDictWithVector ABData)

