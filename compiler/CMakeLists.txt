cmake_minimum_required(VERSION 3.0.0)
project(coffee-maker)

set(SRC
    Java/JavaBuilder.cpp
    Java/JavaWriter.cpp
    Java/JavaCode.cpp
    
    Utils.cpp
)

add_library(coffee-maker SHARED ${SRC})
