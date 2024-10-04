CC = gcc
MV = mv
RM_F = rm -f
RM_R = rm -r
GCOV = gcov
ARRC = ar rc
LCOV = lcov -c -d . -o
LIBS = -lcheck -lm -lpthread -D_GNU_SOURCE
RM_RF = -rm -rf
WHILE = while
FILES = $(wildcard s21_*.c)
O_FLAG = -o
CHANGE = $(patsubst %.c,%.o, ${FILES})
RANLIB = ranlib
CFLAGS = -c -Wall -Werror -Wextra -std=c11
GENHTML = genhtml
TESTFILE = s21_test
TESTFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -Wall -Werror -Wextra -std=c11 -fprofile-arcs -ftest-coverage
TESTFILE.C = test/s21_test.c test/test_s21_strncpy.c  test/test_s21_to_upper.c test/test_s21_to_lower.c test/test_s21_insert.c test/test_s21_trim.c test/test_s21_sprintf.c
S21_STRING.A = s21_string.a
DIR_FOR_GCDA = test
DO_SLEEP_DONE = do sleep 1; done
GCOV_DIR_REMOVE = coverage_report
GCDA_GCNO_EXTENT = *.gcda *.gcno
S21_TEST_GCOV_MV = s21_test.c.gcov
S21_TESTGCDA_RENAME = test/s21_test.gcda
S21_TESTGCNO_RENAME = test/s21_test.gcno
S21_TESTGCDA_DEFAULT = test/s21_test-s21_test.gcda
S21_TESTGCNO_DEFAULT = test/s21_test-s21_test.gcno
S21_TESTING_GCOV_INFO = s21_testing_gcov.info


OS:=$(shell uname -s)
ifeq ($(OS), Linux)
  LIBS += -lsubunit -lrt
endif


all: $(S21_STRING.A)

s21_string.a: ${FILES}
	${CC} ${CFLAGS} $(LIBS) $(FILES)
	$(ARRC) $@ $(CHANGE)
	$(RANLIB) $@
	$(RM_RF) *.o

test: $(TESTFILE.C) $(S21_STRING.A)
	${CC} $(TESTFLAGS) $(O_FLAG) $(TESTFILE) $^ $(LIBS)
	./$(TESTFILE)

gcov_report: $(TESTFILE.C) $(S21_STRING.A)
	${CC} $(GCOVFLAGS) $(O_FLAG) $(TESTFILE) $^ $(LIBS)
	./$(TESTFILE)
	$(WHILE) [ ! -f $(wildcard *.gcda) ] || [ ! -f $(wildcard *.gcno) ]; $(DO_SLEEP_DONE)
	$(MV) $(GCDA_GCNO_EXTENT) $(DIR_FOR_GCDA)/
	$(MV) $(S21_TESTGCDA_DEFAULT) $(S21_TESTGCDA_RENAME)
	$(MV) $(S21_TESTGCNO_DEFAULT) $(S21_TESTGCNO_RENAME)
	$(GCOV) $(TESTFILE.C)
	$(MV) $(S21_TEST_GCOV_MV) $(DIR_FOR_GCDA)
	$(LCOV) $(S21_TESTING_GCOV_INFO)
	$(GENHTML) $(S21_TESTING_GCOV_INFO) $(O_FLAG) $(GCOV_DIR_REMOVE)

clean:
	$(RM_F) *.a
	$(RM_F) *.o
	$(RM_F) *.gcda
	$(RM_F) *.gcno
	$(RM_F) test/*.gcda
	$(RM_F) test/*.gcno
	$(RM_F) test/*.gcov
	$(RM_F) *.info
	$(RM_F) *.gcov
	$(RM_F) s21_test
	$(RM_F) s21_string
	$(RM_R) $(GCOV_DIR_REMOVE)

rebuild: clean all

build: all

format:
	mv ../materials/linters/.clang-format .clang-format
	@clang-format -i -verbose *.c *.h
	mv .clang-format test/.clang-format
	@clang-format -i -verbose test/*.c test/*.h
	mv test/.clang-format ../materials/linters/.clang-format
format-check:
	mv ../materials/linters/.clang-format .clang-format
	@clang-format -n -verbose *.c *.h
	mv .clang-format test/.clang-format
	@clang-format -n -verbose test/*.c test/*.h
	mv test/.clang-format ../materials/linters/.clang-format

leaks:
	valgrind --tool=memcheck --leak-check=yes ./$(TESTFILE)
