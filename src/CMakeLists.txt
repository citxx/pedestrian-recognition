add_definitions(-Wall -pedantic -O2)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost COMPONENTS filesystem system REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(LIBLINEAR_STATIC_LIBS
    liblinear-1.8/blas/blas.a
    liblinear-1.8/linear.o
    liblinear-1.8/tron.o
)

set(SOURCES
    LinearSVM.cpp
    Rectangle.cpp
    ImageSet.cpp
    PatchPositions.cpp
    Sample.cpp
)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(train train.cpp ${LIBLINEAR_STATIC_LIBS} ${SOURCES})
target_link_libraries(train ${OpenCV_LIBS})
target_link_libraries(train ${Boost_LIBRARIES})
