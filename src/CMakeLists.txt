add_definitions(-Wall -pedantic -O2)

FIND_PACKAGE(OpenCV REQUIRED)

set(LIBLINEAR_STATIC_LIBS
    liblinear-1.8/blas/blas.a
    liblinear-1.8/linear.o
    liblinear-1.8/tron.o
)

set(SOURCES
    main.cpp
    PRmain.cpp
    PRtrainingMode.cpp
    PRrecognitionMode.cpp
    PRgraphicsMode.cpp
    LinearSVM.cpp
)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(psearch ${LIBLINEAR_STATIC_LIBS} ${SOURCES} ${HEADERS} ${FORMS_HEADERS})
target_link_libraries(psearch ${OpenCV_LIBS})

