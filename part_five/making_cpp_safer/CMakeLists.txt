project(making_cpp_safer)

set(to_include "./")
set(to_compile Person.cpp)

add_executable(main100 main100.cpp Person.cpp)
target_include_directories(main100 PUBLIC ${to_include})

add_executable(main101 main101.cpp Person.cpp)
target_include_directories(main101 PUBLIC ${to_include})

add_executable(main102 main102.cpp Person.cpp)
target_include_directories(main102 PUBLIC ${to_include})

add_executable(main103 main103.cpp)
add_executable(main104 main104.cpp)
add_executable(main105 main105.cpp)