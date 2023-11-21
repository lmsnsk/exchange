CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
FILES_C=source/*.c
FILES_O=*.o
LIB=s21_math.a
FLAGSADV= -lcheck_pic -pthread -lrt -lm -lsubunit
COVFLAG=--coverage

all: s21_math.a

library:
	@ar rcs $(LIB) $(FILES_O)

o_files:
	@$(CC) $(FLAGS) $(COVFLAG) -c $(FILES_C)

s21_math.a: o_files
	@ar rcs $(LIB) $(FILES_O)
	@rm -rf *.o

test: clean s21_math.a
	@$(CC) $(COVFLAG) tests/s21_test_abs.c -L. $(LIB) -o s21_test_abs $(FLAGSADV)
	@$(CC) $(COVFLAG) tests/s21_test_fabs.c -L. $(LIB) -o s21_test_fabs $(FLAGSADV)
	@$(CC) $(COVFLAG) tests/s21_test_floor.c -L. $(LIB) -o s21_test_floor $(FLAGSADV)
	@$(CC) $(COVFLAG) tests/s21_test_ceil.c -L. $(LIB) -o s21_test_ceil $(FLAGSADV)
	@$(CC) $(COVFLAG) tests/s21_test_fmod.c -L. $(LIB) -o s21_test_fmod $(FLAGSADV)
	@$(CC) $(COVFLAG) tests/s21_test_sin.c -L. $(LIB) -o s21_test_sin $(FLAGSADV)

run_test:
	@./s21_test_abs
	@./s21_test_fabs
	@./s21_test_floor
	@./s21_test_ceil
	@./s21_test_fmod
	@./s21_test_sin

gcov_report: clean test run_test
	@lcov -t "s21_math" -o tests.info -c -d .  
	@genhtml -o report tests.info
	@xdg-open report/index.html
	@make clean

run: clean test run_test

rep: gcov_report

cr: 
	@rm -rf report/

clean:
	@rm -rf *.o
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf *.a
	@rm -rf *.info
	@rm -rf s21*