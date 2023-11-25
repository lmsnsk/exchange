CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
FILES_C=func/*.c
FILES_O=*.o
LIB=s21_string.a
COVFLAG=--coverage

OS = $(shell uname)
ifeq ($(OS), Darwin)
TESTFLAGS=-pthread -lm -lcheck
OPEN_CMD=open
else
TESTFLAGS=-pthread -lcheck_pic -lrt -lm -lsubunit
OPEN_CMD=xdg-open
endif

all: s21_string.a

o_files:
	@$(CC) $(FLAGS) $(COVFLAG) -c $(FILES_C)

s21_string.a: o_files
	@ar rcs $(LIB) $(FILES_O)
	@rm -rf *.o

test: clean s21_string.a
	@$(CC) $(COVFLAG) tests/s21_test_string.c -L. $(LIB) -o s21_tests $(TESTFLAGS)


run_test:
	@./s21_tests

gcov_report: clean test run_test
	@lcov -t "s21_string" -o tests.info -c -d .  
	@genhtml -o report tests.info
	@$(OPEN_CMD) report/index.html

run: clean test run_test

rep: gcov_report

cr: 
	@rm -rf report/

cpp:
	@cppcheck --enable=all --suppress=missingIncludeSystem func/*.c func/*.h tests/*.c

clean:
	@rm -rf *.o
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf *.a
	@rm -rf *.info
	@rm -rf s21*

clang:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -n func/*.c func/*.h
	@clang-format -n tests/*.c 
	@clang-format -i func/*.c func/*.h
	@clang-format -i tests/*.c 
	@rm -rf .clang-format