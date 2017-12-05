gtest_include_path=/d/Programs/Mingw_libs/gtest/include
gtest_lib_path=/d/Programs/Mingw_libs/gtest/lib
test_all:*.cpp
	g++ -std=c++11 -o test *.cpp -I../../  -I../ -I$(gtest_include_path) -L$(gtest_lib_path) -lgmock -lgmock_main -lgtest -lgtest_main
