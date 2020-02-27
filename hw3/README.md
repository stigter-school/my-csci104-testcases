#Test Cases for hw3

It's a gtest file, you know how to compile it ;)




































##Okay fine here's the steps  
1. Copy test.cpp file into your folder for todolist  
2. Compile with g++ -Wall -g test.cpp todolist.cpp -I /usr/include/gtest/ -l gtest -l gtest_main -pthread -o todolist-Gtest  
3. Run with valgrind -tool=memcheck --leak-check=yes ./todolist-Gtest  
4. Find bugs and fix them