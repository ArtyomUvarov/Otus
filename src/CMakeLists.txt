add_library(hello hello.cpp)

target_compile_features(hello PUBLIC cxx_std_17)
target_include_directories(hello INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

 
add_executable(logging_allocator logging_allocator.cpp)
set_target_properties(logging_allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

add_executable(allocator_traits allocator_traits.cpp)
set_target_properties(allocator_traits PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

add_executable(polymorphism polymorphism.cpp)
set_target_properties(polymorphism PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(00_new_overload new_overload.cpp)
set_target_properties(00_new_overload PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

add_executable(01_std_03_allocator simple_allocator.cpp)
set_target_properties(01_std_03_allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

add_executable(sayhello main.cpp)
target_link_libraries(sayhello hello)
