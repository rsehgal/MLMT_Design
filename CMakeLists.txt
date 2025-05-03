cmake_minimum_required(VERSION 2.8)
project(MST)

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

option(ICNSE_CYLINDRICAL_SHIELD "Enabling CYLINDRICAL shape shielding layers, Default is Cuboidal" OFF)
if(ICNSE_CYLINDRICAL_SHIELD)
add_definitions(-DICNSE_CYLINDRICAL_SHIELD)
endif(ICNSE_CYLINDRICAL_SHIELD)

option(USE_CARGO "Enabling Cargo" OFF)
if(USE_CARGO)
add_definitions(-DUSE_CARGO)
endif(USE_CARGO)

option(USE_CRY "Use cry to generate muons" OFF)
if(USE_CRY)
add_definitions(-DUSE_CRY)
add_subdirectory(cry)
include_directories(cry)
include_directories(cry/Cry/inc)
link_directories(cry)
endif(USE_CRY)

option(KILL_SECONDARIES "Kill secondaries particles produced during the simulation " OFF)
if(KILL_SECONDARIES)
add_definitions(-DKILL_SECONDARIES)
endif(KILL_SECONDARIES)

option(ML_TREE "Write Separate tree for ML " OFF)
if(ML_TREE)
add_definitions(-DML_TREE)
endif(ML_TREE)

option(USE_EVE "Use EVE visualizer" OFF)
if(USE_EVE)
add_definitions(-DUSE_EVE)
endif(USE_EVE)

option(TRAINING_DATA "Generated Training data" OFF)
if(TRAINING_DATA)
add_definitions(-DTRAINING_DATA)
endif(TRAINING_DATA)

option(TESTING_DATA "Generate Testing data" OFF)
if(TESTING_DATA)
add_definitions(-DTESTING_DATA)
endif(TESTING_DATA)

option(RANDOM_DIRECTION "Random direction in case CRY is not used " ON)
if(RANDOM_DIRECTION)
add_definitions(-DRANDOM_DIRECTION)
endif(RANDOM_DIRECTION)

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
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})
#set(REQLIBS ${REQLIBS} ${ROOT_LIBRARIES} )


include_directories(visualizer)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.h ${PROJECT_SOURCE_DIR}/inc/*.hh ../../base/Vector3D.h) 

add_executable(main main.cpp ${sources} ${headers})
if(USE_RANECU_RANDOM)
if(USE_CRY)
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES} cryInterface)
else()
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES})
endif(USE_CRY)
else()
if(USE_CRY)
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} cryInterface)
else()
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
endif(USE_CRY)
endif()


#add_executable(VisualizePoca VisualizePoca.cpp ${sources} ${headers})
#target_link_libraries(VisualizePoca ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

add_executable(Test_Track core/Test_Track.cpp ${PROJECT_SOURCE_DIR}/src/Track.cpp ${PROJECT_SOURCE_DIR}/src/Helpers.cpp)
target_link_libraries(Test_Track ${Geant4_LIBRARIES})

if(USE_EVE)
add_executable(TestEve core/TestEve.cpp visualizer/EveVisualizer.cpp)
target_link_libraries(TestEve ${ROOT_LIBRARIES} Eve RGL Gui Gpad Core)
endif(USE_EVE)

#add_executable(Test_Cry core/Test_Cry.cpp)
#target_link_libraries(Test_Cry ${ROOT_LIBRARIES} cryInterface)

#add_executable(Test_Visualization core/Test_Visualization.cpp ${PROJECT_SOURCE_DIR}/src/Track.cpp ${PROJECT_SOURCE_DIR}/src/Helpers.cpp)
#target_link_libraries(Test_Visualization ${Geant4_LIBRARIES})

#add_executable(Test_Vis core/Test_Vis.cpp )
#target_link_libraries(Test_Vis ${Geant4_LIBRARIES})

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
