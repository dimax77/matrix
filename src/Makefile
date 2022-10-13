PROJECT_NAME=s21_matrix

CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
GCOV_FLAGS=--coverage -lgcov
TEST_NAME=$(PROJECT_NAME)_test
GCOV_NAME=gcov_report
SOURCES=$(PROJECT_NAME).c
OBJECTS=$(SOURCES:.c=.o)

ifeq ($(shell uname -s), Darwin)
CHECK_FLAGS=-lcheck
MEM_CHECK=leaks --atExit -- ./$(TEST_NAME)
endif

ifeq ($(shell uname -s), Linux)
CHECK_FLAGS=-lcheck -pthread -lrt -lm -lsubunit
MEM_CHECK=valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_NAME)
endif

all: $(PROJECT_NAME).a test gcov_report

$(PROJECT_NAME).a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

test: $(TEST_NAME).c $(PROJECT_NAME).a
	$(CC) $(CFLAGS) $^ $(CHECK_FLAGS) -o $(TEST_NAME)
	- ./$(TEST_NAME)

gcov_report: $(TEST_NAME).c $(SOURCES)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $^ $(CHECK_FLAGS) -o $(GCOV_NAME)
	@./$(GCOV_NAME)
	@lcov -t "$(GCOV_NAME)" -o $(GCOV_NAME).info -c -d .
	@genhtml -o report $(GCOV_NAME).info 
	@- open ./report/index.html
	rm -rf *.gcno *.gcda $(GCOV_NAME).* $(GCOV_NAME)

check: clean
	cppcheck --suppress=missingIncludeSystem *.h $(SOURCES)
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.h $(SOURCES) $(TEST_NAME).c
	@rm .clang-format

mem_check: clean test
	$(MEM_CHECK)

sanitize: $(TEST_NAME).c $(PROJECT_NAME).a
	$(CC) $(CFLAGS) -fsanitize=address $^ $(CHECK_FLAGS) -o $(TEST_NAME)
	- ./$(TEST_NAME)

unit: $(TEST_NAME).check
	checkmk clean_mode=1 $(TEST_NAME).check > $(TEST_NAME).c
	sed -i 's/srunner_run_all(sr, CK_ENV);/srunner_set_fork_status(sr, CK_NOFORK);srunner_run_all(sr, CK_NORMAL);/' $(TEST_NAME).c

git: #make git CMT="commit"
	git add Makefile $(PROJECT_NAME).h $(PROJECT_NAME).c $(TEST_NAME).c $(TEST_NAME).check s21_addons.c
	git commit -m'$(CMT)'
	git push

clean:
	rm -rf *.o *.a gcov_report *.gcno *.gcda ./report *.info *.html gcov_report $(TEST_NAME) valgrind_out.txt a.out

rebuild: clean all
