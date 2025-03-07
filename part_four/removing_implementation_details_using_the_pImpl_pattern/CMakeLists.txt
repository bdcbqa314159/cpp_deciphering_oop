project(removing_implementation_details_using_the_pImpl_pattern)

set(to_include "./")
set(to_compile PersonImpl.cpp)

add_executable(main97 main97.cpp PersonImpl.cpp)
target_include_directories(main97 PUBLIC ${to_include})

add_executable(main98 main98.cpp PersonImpl.cpp)
target_include_directories(main98 PUBLIC ${to_include})

add_executable(main99 main99.cpp PersonImpl_unique_ptr.cpp)
target_include_directories(main99 PUBLIC ${to_include})