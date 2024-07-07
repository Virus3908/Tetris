CLANG_FORMAT = ../materials/linters/.clang-format

clang:
	clang-format --style=file:$(CLANG_FORMAT) -i *.c *.h $(LIB_PATH)*.c $(LIB_PATH)*.h $(GUI_PATH)*.c $(GUI_PATH)*.h

clang_check:
	clang-format --style=file:$(CLANG_FORMAT) -n *.c *.h $(LIB_PATH)*.c $(LIB_PATH)*.h $(GUI_PATH)*.c $(GUI_PATH)*.h

check:
	cppcheck -q --enable=warning,portability --inconclusive ./

#.PHONY: all clean rebuild clang check

clean:
	rm -rf $(LIBS) $(TEST_LIB) *.o *.so *.a *.out *.gcda *.gcno *.info test test.c test_gcov report obj gcov_obj tetris

rebuild: clean all