Hi
to run boost tests use -> 
g++ -std=c++14 mainTest.cpp -lboost_system -lboost_unit_test_framework 
: that's just compiling the test 
and ./a.out --log_level=test_suite
run all tests 
