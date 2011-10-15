add_definitions(-Wall -pedantic -O2)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost COMPONENTS filesystem system REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES
    LinearSVM.cpp
    Rectangle.cpp
    ImageSet.cpp
    PatchPositions.cpp
    Sample.cpp
)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(train train.cpp ${SOURCES})
target_link_libraries(train ${OpenCV_LIBS})
target_link_libraries(train ${Boost_LIBRARIES})
target_link_libraries(train -lblas -llinear)

add_executable(show show.cpp ${SOURCES})
target_link_libraries(show ${OpenCV_LIBS})
target_link_libraries(show ${Boost_LIBRARIES})
target_link_libraries(show -lblas -llinear)

add_executable(classify classify.cpp ${SOURCES})
target_link_libraries(classify ${OpenCV_LIBS})
target_link_libraries(classify ${Boost_LIBRARIES})
target_link_libraries(classify -lblas -llinear)

add_executable(quality quality.cpp ${SOURCES})
target_link_libraries(quality ${OpenCV_LIBS})
target_link_libraries(quality ${Boost_LIBRARIES})
target_link_libraries(quality -lblas -llinear)
