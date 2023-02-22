CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -std=c11
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

FILES=files/s21_SmartCalc.c\
		files/deposit.c\
		files/credit.c

OBJ_LIB=files/obj/s21_SmartCalc.o\
		files/obj/deposit.o\
		files/obj/credit.o

all:  uninstall s21_SmartCalc.a test gcov_report open_report install clean dvi

install: uninstall
	@mkdir "build"
	@cd build && cmake ../files/CMakeLists.txt && make
	@mv build/SmartCalc_v1.app SmartCalc_v1.app

uninstall: clean
	@rm -rf SmartCalc_v1.app

dist:
	@rm -rf arch/
	@mkdir arch && mkdir arch/files && mkdir arch/files/img
	@cp Makefile *.md arch/
	@cp files/*.c files/*.h files/*.cpp files/*.ui files/*.txt arch/files/
	@cp files/img/*.png arch/files/img/
	@tar cvzf SmartCalc_v1.tgz arch/
	@rm -rf arch/

s21_SmartCalc.a: s21_SmartCalc.o
	@ar r files/s21_SmartCalc.a $(OBJ_LIB)
	@cp files/s21_SmartCalc.a files/libs21_SmartCalc.a
	@cp files/s21_SmartCalc.a files/ls21_SmartCalc.a
	@ranlib files/libs21_SmartCalc.a
	@ranlib files/ls21_SmartCalc.a

s21_SmartCalc.o: $(FILES)
	@$(CC) $(FILES) -c
	@rm -rf files/obj report
	@mkdir files/obj
	@mv *.o files/obj/

test: s21_SmartCalc.a
ifeq ($(OS), Darwin)
	@$(CC) $(CFLAGS) files/s21_test.c files/s21_SmartCalc.a -o files/s21_test  $(LIBS)
	@files/./s21_test
else
	@$(CC) $(CFLAGS) files/s21_test.c files/s21_SmartCalc.a -o files/s21_test $(LINUX) $(LIBS)
	@files/./s21_test
endif

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) files/s21_test.c $(FILES) -o files/s21_test $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) files/s21_test.c $(FILES) -o files/s21_test $(LINUX) $(LIBS)
endif
	@files/./s21_test
	@lcov -t "test" -o files/s21_test.info -c -d .
	@genhtml -o files/report files/s21_test.info
	@mv *.gc* files/report/

dvi:
	@open dvi.md

open_report:
	@open files/report/index.html

open:
	@open SmartCalc_v1.app

rebuild: clean all

check: test
	@cp ../materials/linters/.clang-format files/.clang-format
	@chmod 777 files/.clang-format
	clang-format -n files/*.c files/*.h files/*.cpp
ifeq ($(OS), Darwin)
	@CK_FORK=no leaks --atExit -- files/./s21_test
else
	@valgrind ./s21_test --leak-check=full
endif
	@make clean

clean:
	@rm -rf arch
	@rm -rf build
	@rm -rf files/*.gc* files/obj files/*.a files/*.out files/*.info files/s21_test
	@rm -rf files/report files/obj files/*.dSYM files/.clang-format
