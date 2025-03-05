project(testing_classes_and_components)

add_executable(main85 main85.cpp)

set(to_include "./")
set(to_compile Person.cpp Student.cpp)

add_executable(main86 main86.cpp ${to_compile})
target_include_directories(main86 PUBLIC ${to_include})
