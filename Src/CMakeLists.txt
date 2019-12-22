target_include_directories(main Public ../Include)
add_compile_options(-Wall -Wextra -pedantic -Werror)
add_executable(main main.cpp Park1.cpp Auto.cpp Date.cpp)