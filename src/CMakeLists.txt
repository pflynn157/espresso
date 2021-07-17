cmake_minimum_required(VERSION 3.0.0)
project(espresso_main)

set(SRC
    main.cpp
)

add_executable(esp ${SRC})

target_link_libraries(esp
    coffee-grinder
    coffee-maker
)

