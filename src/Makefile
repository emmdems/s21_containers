CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Werror -g -pthread
TARGET = s21_containers_tests

# Phony targets
.PHONY: clean test format fix gcov_flag gcov_report

test: $(TARGET)

$(TARGET): tests/s21_containers_tests.cpp s21_containers.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) tests/s21_containers_tests.cpp -lgtest -lgtest_main

gcov_flag:
	$(eval CXXFLAGS += --coverage)
gcov_report: clean fix gcov_flag test 
	./$(TARGET)
	mkdir -p report
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '/usr/*' '*/tests/*' --output-file filtered_coverage.info
	genhtml filtered_coverage.info --output-directory report
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf coverage.info
	rm -rf filtered_coverage.info
	open report/index.html

# clang-format
format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.inc *.h
	clang-format -n tests/*.cpp
	rm -rf .clang-format
fix:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i *.inc *.h
	clang-format -i tests/*.cpp
	rm -rf .clang-format

clean:
	rm -f $(TARGET)
