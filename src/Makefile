CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror

LDFLAGS = -lm -lsubunit

TEST_DIR = tests/

ADD_LIB = -lcheck

SRC_FILES := $(wildcard s21_*.c)

SRC_FILES := $(filter-out s21_arithmetic_old.c, $(SRC_FILES))

ifeq ($(shell uname), Linux)

	LDFLAGS += -lpthread -lrt

	OPEN = xdg-open

else

	OPEN = open

endif

all: format s21_decimal.a test 

#$(TEST_DIR)*.c

test: s21_decimal.a

	$(CC) $(CFLAGS) $(TEST_DIR)*.c s21_decimal.a $(ADD_LIB) $(LDFLAGS) -o s21_test

	./s21_test

#valgrind --tool=memcheck --leak-check=yes ./s21_test

s21_decimal.a: clean s21_decimal.o

	ar rcs s21_decimal.a *.o

s21_decimal.o:

	$(CC) $(CFLAGS) -c $(SRC_FILES)

gcov_report: clean

	$(CC) --coverage $(SRC_FILES) $(LDFLAGS) -c

	$(CC) $(TEST_DIR)*.c  $(LDFLAGS) -c

	gcc -o s21_test *.o $(ADD_LIB) $(LDFLAGS) --coverage

	./s21_test

	lcov -t "s21_test" -o s21_test.info -c -d . && lcov --remove s21_test.info '/usr/local/lib/*' -o s21_test.info 

	genhtml -o report s21_test.info

	$(OPEN) ./report/index.html

clean:

	rm -rf *.o s21_decimal.a s21_test *.gcno *.gcda s21_test.info report log_valgrind

rebuild: clean s21_decimal.a

format-check:

	@cp ../materials/linters/.clang-format ./

	@clang-format -n *.c *.h 

	@clang-format -n $(TEST_DIR)*.c $(TEST_DIR)*.h 

	@rm .clang-format

format:

	@cp ../materials/linters/.clang-format ./

	@clang-format -i *.c *.h 

	@clang-format -i $(TEST_DIR)*.c $(TEST_DIR)*.h 

	@rm .clang-format

cppcheck:

	cppcheck -q --enable=all --inconclusive .

valgrind:

	valgrind --leak-check=full --log-file=log_valgrind ./s21_test
