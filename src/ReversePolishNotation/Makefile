CC=gcc
CC_FLAGS=-g -Wall -Werror -Wextra -std=c11 -pedantic  #-fsanitize=address
test_flags=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
VALGRIND_FLAGS = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med
CALC_APP_NAME=SmartCalc1

ifeq ($(OS),Linux)
	test_libs=-lcheck -lm -lpthread -lsubunit
	open=xdg-open
else
	test_libs=-lcheck
	open=open
endif

all: clean install gcov_report clang

install: uninstall clean
	mkdir build
	cd QtProject/SmartCalc1/ && qmake && make  && mv $(CALC_APP_NAME) ../../build #&& make clean

	
uninstall: 
	rm -rf bulid/$(CALC_APP_NAME)
	
dvi:
	open README.md
	
dist: install
	mkdir dist
	cp build/$(CALC_APP_NAME) dist/$(CALC_APP_NAME).app
	cp README.md dist/README.md
	cd dist
	tar -cvzf $(CALC_APP_NAME).tgz *.*
	rm $(CALC_APP_NAME).app README.md

test: clean
	$(CC) -c $(CC_FLAGS) $(test_flags) *.c $(test_libs)
	$(CC) $(CC_FLAGS) $(test_flags) *.o -o test $(test_libs)
	rm *.o
	./test
	mv *.gcda *.gcno tests/

gcov_report: test
	lcov -t "test" -o $(tests_info)test.info -c -d .
	genhtml -o report $(tests_info)test.info
	$(open) report/index.html

clean:
	rm -f tests/*.gcda tests/*.gcno *.gcda *.gcno *.txt
	rm -f test
	rm -f *.o
	rm -rf report
	rm -rf build dist
	rm -f QtProject/SmartCalc1/*.o QtProject/SmartCalc1/moc_*.*

clang:
	clang-format -i *.c *.h --style=Google

valgrind:
	$(CC) $(CC_FLAGS) $(test_flags) *.c src*/*.c tests/*.c -o test $(test_libs)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) ./test

cleanv:
	rm -rf test-s21_* test
