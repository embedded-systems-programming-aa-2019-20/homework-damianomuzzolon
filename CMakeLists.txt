# Works with 3.10.2
cmake_minimum_required(VERSION 3.10.2)

# Project name and a few useful settings.
# Other commands can pick up the results
project (Homework
        VERSION 0.1
        DESCRIPTION "Homework Winter 2019"
        LANGUAGES CXX)

# The test code is here
add_subdirectory(tests)
