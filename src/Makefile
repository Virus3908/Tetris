OS = $(shell uname)
ifeq ("$(OS)","Linux")
	CC = gcc
	GCOV = gcovr 
	LEAKS_RUN_TEST = valgrind --tool=memcheck --leak-check=yes --log-file=1.txt ./test
	PKG =`pkg-config --cflags --libs check tinfo`
else
	CC = gcc-14 
	GCOV = gcov-14
	LEAKS_RUN_TEST = leaks -atExit -- ./test
	PKG =`pkg-config --cflags --libs check`
endif

CFLAGS = -std=c11 -Wall -Werror -Wextra -pedantic -D_POSIX_C_SOURCE=199309L

EXTRA_LIBS = -lm -lncurses $(PKG)
LIB_PATH = brick_game/tetris/
LIB_NAME = s21_backend
GUI_PATH = gui/cli/
GUI_NAME = s21_frontend
COMMON= common

SRC_LIBS= $(LIB_PATH)$(LIB_NAME).c $(GUI_PATH)$(GUI_NAME).c $(COMMON).c #$(LIB_PATH)$(SHAPE_NAME).c
LIBS = $(SRC_LIBS:.c=.a)
TEST_LIB = $(COMMON).o $(LIB_PATH)$(LIB_NAME).o 
TEST_LIB_A = $(TEST_LIB:.o=.a)
OBJECTS_GCOV = $(addprefix gcov_obj/,$(TEST_LIB))

all: install play

install: $(LIBS)
	mkdir -p tetris/
	$(CC) $(CFLAGS) main.c $(addprefix obj/,$(^F)) -o tetris/tetris $(EXTRA_LIBS)

play: install
	./tetris/tetris

%.a: %.o
	mkdir -p obj	
	ar rc obj/$(@F) obj/$(<F)
	ranlib obj/$(@F)

%.o: %.c
	mkdir -p obj
	$(CC) $(CFLAGS) -g -c $< -o obj/$(@F) -lncurses -lm

dvi:
	doxygen

dist:
	mkdir -p dist
	tar -czvf brick_game.tar ./
	mv brick_game.tar dist/

uninstall: clean
	rm -rf ./html ./latex
	rm -f score.txt
	rm -rf ./dist

include ./Makefiles/gcov_report.mk
include ./Makefiles/test.mk
include ./Makefiles/utilites.mk