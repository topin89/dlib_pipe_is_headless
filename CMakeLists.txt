cmake_minimum_required(VERSION 3.14)
project(layer)

add_executable(layer
    main.cpp
)

set_target_properties(layer PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
)