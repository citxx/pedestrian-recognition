add_definitions(-Wall -pedantic -O2)

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(SOURCES
    main.cpp
    trainingMode.cpp
    classifyingMode.cpp
    graphicsMode.cpp
    SampleSet.cpp
    Signal2D.cpp
)

set(MOC_HEADERS
)

set(FORMS
)

QT4_WRAP_CPP(HEADERS ${MOC_HEADERS})
QT4_WRAP_UI(FORMS_HEADERS ${FORMS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(psearch ${SOURCES} ${HEADERS} ${FORMS_HEADERS})
target_link_libraries(psearch ${QT_LIBRARIES})

