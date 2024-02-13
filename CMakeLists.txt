cmake_minimum_required(VERSION 2.8)
project(MST)

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

option(ICNSE_CYLINDRICAL_SHIELD "Enabling CYLINDRICAL shape shielding layers, Default is Cuboidal" OFF)
if(ICNSE_CYLINDRICAL_SHIELD)
add_definitions(-DICNSE_CYLINDRICAL_SHIELD)
endif(ICNSE_CYLINDRICAL_SHIELD)

option(ICNSE_ENABLE_OPTICAL_PHYSICS "Enabling OPTICAL Physics, Default is OFF " OFF)
if(ICNSE_ENABLE_OPTICAL_PHYSICS)
add_definitions(-DICNSE_ENABLE_OPTICAL_PHYSICS)
endif(ICNSE_ENABLE_OPTICAL_PHYSICS)

option(ICNSE_INSPECT_SOURCE "Inspect Particle source, default is OFF " OFF)
if(ICNSE_INSPECT_SOURCE)
add_definitions(-DICNSE_INSPECT_SOURCE)
endif(ICNSE_INSPECT_SOURCE)

option(ICNSE_FILL_COLOUR "Assign default color to detector components, default is OFF " OFF)
if(ICNSE_FILL_COLOUR)
add_definitions(-DICNSE_FILL_COLOUR)
endif(ICNSE_FILL_COLOUR)

option(AVOID_DUPLICATE_COUNT "Avoid duplicate count of a particle in sensitive volume, Default is OFF " OFF)
if(AVOID_DUPLICATE_COUNT)
add_definitions(-DAVOID_DUPLICATE_COUNT)
endif(AVOID_DUPLICATE_COUNT)

option(ICNSE_TRACK_ONLY_PRIMARY "Enabling OPTICAL Physics, Default is OFF " OFF)
if(ICNSE_TRACK_ONLY_PRIMARY)
add_definitions(-DICNSE_TRACK_ONLY_PRIMARY)
endif(ICNSE_TRACK_ONLY_PRIMARY)

option(ICNSE_USE_RANECU_RANDOM "Enabling RANECU random number generator, Required CLHEP, Default is OFF " OFF)
if(ICNSE_USE_RANECU_RANDOM)
add_definitions(-DICNSE_USE_RANECU_RANDOM)
find_package(CLHEP REQUIRED)
message(STATUS ${CLHEP_INCLUDE_DIR})
message(STATUS ${CLHEP_LIBRARIES})
include_directories(${CLHEP_INCLUDE_DIR})
#set(REQLIBS ${REQLIBS} ${CLHEP_LIBRARIES} )
endif(ICNSE_USE_RANECU_RANDOM)


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

#----------------------------------------------------------------------------
file(GLOB MAC_FILES ${PROJECT_SOURCE_DIR}/MacFiles/*)
message(STATUS ${MAC_FILES})
#file(COPY ${MAC_FILES} DESTINATION ${PROJECT_SOURCE_DIR}/build)
file(COPY ${MAC_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(../..)

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})
#set(REQLIBS ${REQLIBS} ${ROOT_LIBRARIES} )

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.h ${PROJECT_SOURCE_DIR}/inc/*.hh ../../base/Vector3D.h) 

add_executable(main main.cpp ${sources} ${headers})
if(USE_RANECU_RANDOM)
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES})
else()
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
endif()

#add_executable(TestBoolean coreTest/TestBoolean.cpp)
#target_link_libraries(TestBoolean ${Geant4_LIBRARIES})
#
#add_executable(TestG4Units coreTest/TestG4Units.cpp)
#target_link_libraries(TestG4Units ${Geant4_LIBRARIES})
#
#add_executable(TestPtr coreTest/TestPtr.cpp)
#
##add_executable(Plot_gamma Plots/Plot_gamma.cpp)
##target_link_libraries(Plot_gamma ${ROOT_LIBRARIES})
#
#add_executable(Plot_all Plots/Plot_all.cpp)
#target_link_libraries(Plot_all ${ROOT_LIBRARIES})
#
#add_executable(testplot Plots/testplot.cpp)
#target_link_libraries(testplot ${ROOT_LIBRARIES})
#
##target_link_libraries(main ${Geant4_LIBRARIES} Tomo)
