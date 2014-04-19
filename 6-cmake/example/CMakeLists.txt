cmake_minimum_required(VERSION 2.8)

project(BOGGLE_COM)


add_library(libbcom SHARED communication.c)
add_library(libbcom_mockfile SHARED communication_mock_file.c)
add_library(libbcom_mockdata SHARED communication_mock_data.c)

add_executable(example example.c)
target_link_libraries(example libbcom)

add_executable(example_mock_file example.c)
target_link_libraries(example_mock_file libbcom_mockfile)


add_executable(example_mock_data example.c)
set_target_properties(example_mock_data PROPERTIES COMPILE_DEFINITIONS "MOCKDATA")
target_link_libraries(example_mock_data libbcom_mockdata)
