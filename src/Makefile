CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -std=c11
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

FILES=files/my_SmartCalc.c\
		files/deposit.c\
		files/credit.c

OBJ_LIB=files/obj/my_SmartCalc.o\
		files/obj/deposit.o\
		files/obj/credit.o

all:  uninstall my_SmartCalc.a test gcov_report open_report install clean dvi

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

my_SmartCalc.a: my_SmartCalc.o
	@ar r files/my_SmartCalc.a $(OBJ_LIB)
	@cp files/my_SmartCalc.a files/libmy_SmartCalc.a
	@cp files/my_SmartCalc.a files/lmy_SmartCalc.a
	@ranlib files/libmy_SmartCalc.a
	@ranlib files/lmy_SmartCalc.a

my_SmartCalc.o: $(FILES)
	@$(CC) $(FILES) -c
	@rm -rf files/obj report
	@mkdir files/obj
	@mv *.o files/obj/

test: my_SmartCalc.a
ifeq ($(OS), Darwin)
	@$(CC) $(CFLAGS) files/my_test.c files/my_SmartCalc.a -o files/my_test  $(LIBS)
	@files/./my_test
else
	@$(CC) $(CFLAGS) files/my_test.c files/my_SmartCalc.a -o files/my_test $(LINUX) $(LIBS)
	@files/./my_test
endif

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) files/my_test.c $(FILES) -o files/my_test $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) files/my_test.c $(FILES) -o files/my_test $(LINUX) $(LIBS)
endif
	@files/./my_test
	@lcov -t "test" -o files/my_test.info -c -d .
	@genhtml -o files/report files/my_test.info
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
	@CK_FORK=no leaks --atExit -- files/./my_test
else
	@valgrind ./my_test --leak-check=full
endif
	@make clean

clean:
	@rm -rf arch
	@rm -rf build
	@rm -rf files/*.gc* files/obj files/*.a files/*.out files/*.info files/my_test
	@rm -rf files/report files/obj files/*.dSYM files/.clang-format
