CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(pattern-fun)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Debug")
ENDIF()

GET_FILENAME_COMPONENT( SOURCE_ROOT . ABSOLUTE )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SOURCE_ROOT}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SOURCE_ROOT}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SOURCE_ROOT}/bin)

ADD_COMPILE_OPTIONS(-std=c++14)
ADD_COMPILE_OPTIONS(-Wall)
ADD_COMPILE_OPTIONS(-Werror)

INCLUDE_DIRECTORIES(${SOURCE_ROOT})
LINK_LIBRARIES(stdc++)

ADD_EXECUTABLE(Composite Composite/Composite.cpp)
ADD_EXECUTABLE(Factory Factory/Factory.cpp)
ADD_EXECUTABLE(State State/State.cpp)
ADD_EXECUTABLE(Decorator Decorator/Decorator.cpp)
ADD_EXECUTABLE(FluentBuilder FluentBuilder/FluentBuilder.cpp)
ADD_EXECUTABLE(Visitor Visitor/Visitor.cpp)
ADD_EXECUTABLE(Singleton Singleton/Singleton.cpp)
ADD_EXECUTABLE(Strategy Strategy/Strategy.cpp)
ADD_EXECUTABLE(Pimpl Pimpl/Processor.cpp Pimpl/Pimpl.cpp)
ADD_EXECUTABLE(Template Template/Template.cpp)
ADD_EXECUTABLE(Command Command/Command.cpp)

