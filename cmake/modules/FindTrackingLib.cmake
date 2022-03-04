# - Finds Vc installation ( the wrapper library to SIMD intrinsics )
# This module sets up Vc information 
# It defines:
# TrackingLib_FOUND          If the ROOT is found
# TrackingLib_INCLUDE_DIR    PATH to the include directory
# TrackingLib_LIBRARIES      Most common libraries
# TrackingLib_LIBRARY_DIR    PATH to the library directory 

# look if an environment variable TrackingLib_ROOT exists
set(TrackingLib_ROOT $ENV{TrackingLib_ROOT})

find_library(TrackingLib_LIBRARIES libTrackingLib.so PATHS ${TrackingLib_ROOT}/lib)
if (TrackingLib_LIBRARIES) 
   file(GLOB TrackingLib_LIBRARIES ${TrackingLib_LIBRARIES} ${TrackingLib_ROOT}/lib/*.so)
   set(TrackingLib_FOUND TRUE)	
   #string(REPLACE "/lib/libVc.a" "" TrackingLib_ROOT  ${TrackingLib_LIBRARIES})
   set(TrackingLib_INCLUDE_DIR ${TrackingLib_ROOT}/inc ${TrackingLib_ROOT}/inc/CoordinateGenerator/inc ${TrackingLib_ROOT}/inc/CRY/inc ${TrackingLib_ROOT}/inc/processor/inc ${TrackingLib_ROOT}/inc/CRY_Manual_Interface/inc ${TrackingLib_ROOT}/inc/visualizer/inc)
   set(TrackingLib_LIBRARY_DIR ${TrackingLib_ROOT}/lib)
   message(STATUS "Found TrackingLib library in ${TrackingLib_LIBRARIES}")		
else()
   message(STATUS "TrackingLib library not found; try to set a TrackingLib_ROOT environment variable to the base installation path or add -DTrackingLib_ROOT= to the cmake command")	
endif()

