CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
FILES_C=source/*.c
FILES_O=s21_abs.o s21_fabs.o
LIB=s21_math.a
CHECKFLAGS=$(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage
FLAGSADV=-pthread -lcheck_pic -pthread -lrt -lm -lsubunit
GLFLAGS=--coverage
GCOVFLAGS=-fprofile-arcs -ftest-coverage

all: s21_math.a

s21_math.a: 
	@$(CC) $(FLAGS) -c $(FILES_C)
	@ar rcs $(LIB) $(FILES_O)
	@rm -rf *.o

test: clean s21_math.a
	@$(CC) $(GLFLAGS) tests/s21_test_abs.c -L. s21_math.a -o s21_test_abs $(FLAGSADV)
	@$(CC) $(GLFLAGS) tests/s21_test_fabs.c -L. s21_math.a -o s21_test_fabs $(FLAGSADV)

run_test:
	@./s21_test_abs
	@./s21_test_fabs

gcov_report: test run_test
	@lcov -t "s21_math" -o tests.info -c -d .  
	@genhtml -o report tests.info
	@xdg-open report/index.html
	@make clean

clean:
	@rm -rf *.o
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf *.a
	@rm -rf *.info
	@rm -rf s21*