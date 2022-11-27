CPP = --suppress=missingIncludeSystem --suppress=unmatchedSuppression --suppress=unusedFunction --suppress=useStlAlgorithm
STD = g++ --std=c++17
TEST =  -lgtest -lgmock -pthread --coverage
OS=$(shell uname)

ifeq ($(OS), Linux)
	LEAKS=CK_FORK=no valgrind --leak-check=full --track-origins=yes -s
	TEST =  -lgtest -lgmock -pthread --coverage
else
	LEAKS=CK_FORK=no leaks --atExit --
	TEST =  -lgtest -fsanitize=address -lgmock -pthread --coverage
endif

all: test_all check_leaks_all


# **************** All *****************

gcov_report_all: test_all
	./test_all
	mkdir report
	gcovr -r ../ -e ../googletest-1.10.x --html --html-details -o report/result.html
	open report/result.html

test_all: 
	$(STD) test_all.cpp -o test_all $(TEST)
	./test_all
	-cppcheck --language=c++ --enable=all --std=c++17 my_containers.h $(CPP)
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp *.h

check_leaks_all:
	$(LEAKS) ./test_all



# ******* Stack ********

gcov_report_stack: test_stack
	./test_stack
	mkdir report
	gcovr -r ../ -e ../googletest-1.10.x --html --html-details -o report/result.html
	open report/result.html

test_stack: 
	$(STD) test_stack.cpp -o test_stack -lgtest -lgmock -pthread --coverage 
	./test_stack
	-cppcheck --language=c++ --enable=all --std=c++17 my_stack.h $(CPP)
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp *.h

check_leaks_stack:
	$(LEAKS) ./test_stack


# ******** Vector ********

gcov_report_vector: test_vector
	./test_vector
	mkdir report
	gcovr -r ../ -e ../googletest-1.10.x --html --html-details -o report/result.html
	open report/result.html

test_vector: 
	$(STD) test_vector.cpp -o test_vector -lgtest -lgmock -pthread --coverage 
	./test_vector
	-cppcheck --language=c++ --enable=all --std=c++17 my_vector.h $(CPP)
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp *.h

check_leaks_vector:
	$(LEAKS) ./test_vector



# ******** List ********

gcov_report_list: test_list
	./test_list
	mkdir report
	gcovr -r ../ -e ../googletest-1.10.x --html --html-details -o report/result.html
	open report/result.html

test_list: 
	$(STD) test_list.cpp -o test_list -lgtest -lgmock -pthread --coverage 
	./test_list
	-cppcheck --language=c++ --enable=all --std=c++17 my_list.h $(CPP)
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp *.h

check_leaks_list:
	$(LEAKS) ./test_list


# ******** Queue ********

gcov_report_queue: test_queue
	./test_queue
	mkdir report
	gcovr -r ../ -e ../googletest-1.10.x --html --html-details -o report/result.html
	open report/result.html

test_queue: 
	$(STD) test_queue.cpp -o test_queue -lgtest -lgmock -pthread --coverage 
	./test_queue
	-cppcheck --language=c++ --enable=all --std=c++17 my_queue.h $(CPP)
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp *.h


check_leaks_queue:
	$(LEAKS) ./test_queue


# ******** Map ********

gcov_report_map: test_map
	./test_map
	mkdir report
	gcovr -r ../ -e ../googletest-1.10.x --html --html-details -o report/result.html
	open report/result.html

test_map: 
	$(STD) test_map.cpp -o test_map -lgtest -lgmock -pthread --coverage 
	./test_map
	-cppcheck --language=c++ --enable=all --std=c++17 my_list.h $(CPP)
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp *.h

check_leaks_map:
	$(LEAKS) ./test_map



clean:
	rm -rf *.gcda *.gcno test_stack report test_vector test_list test_queue test_map test_all .clang-format