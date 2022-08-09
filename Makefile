CC = gcc -Wall -Werror -Wextra

FLAGS = -lcheck
OPEN = open ./report/index.html
QMAKE=qmake
NAME=3D_viewer_c.app
OS=$(shell uname)
ifeq ($(OS), Linux)
QMAKE = /home/fbillye/Qt/6.2.4/gcc_64/bin/qmake
FLAGS += -lm -lpthread -lrt -lsubunit
OPEN = open ./report
NAME = untitled
endif

all: install gcov_report

rebuild: clean all

test: test_build
	-./testing.out

test_build:
	-$(CC) back.c afinne.c test.c -o testing.out $(FLAGS)

gcov_report: test_build
	-$(CC) back.c afinne.c test.c -fprofile-arcs -ftest-coverage $(FLAGS)
	-./a.out
	-lcov -t "viewer_3d" -o viewer_3d.info -c -d .
	-genhtml -o report viewer_3d.info
	-$(OPEN)
	rm -rf a.out

static_test:
	cp ./../materials/linters/CPPLINT.cfg .
	-cppcheck --enable=all --suppress=missingIncludeSystem *.c
	-python3 ../materials/linters/cpplint.py --extensions=c *.c
	rm -rf CPPLINT.cfg

clean:
	rm -rf .o *.out CPPLINT.cfg
	rm -rf .qmake.stash 3D_viewer_c.app ui_* *.o moc_* Makefile_qt Manual
	rm -rf *.info *.gcno *.gcda a.out qrc_shaders.cpp report

install:
	$(QMAKE) 3D_viewer_c.pro -o Makefile_qt
	make -f Makefile_qt
	- which convert > path_convert.txt
	- cp path_convert.txt ./3D_viewer_c.app/Contents/MacOS

dist:
	tar -czf Archive.tar.gz ./$(NAME)

dvi:
	open info.html

uninstall: clean