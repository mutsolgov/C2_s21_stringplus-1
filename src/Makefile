CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -std=c11
LFLAGS = -Wall -Werror -Wextra -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector -fanalyzer
COVFLAGS = -fprofile-arcs -ftest-coverage
TESTFLAGS = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
FILES = s21_memchr s21_memcmp s21_memcpy s21_memset s21_strncat s21_strchr s21_strncmp s21_strncpy s21_strcspn s21_strerror s21_strlen s21_strpbrk s21_strrchr s21_strstr s21_strtok s21_utils s21_sprintf s21_sscanf s21_strcat s21_strcpy s21_to_upper s21_to_lower s21_insert s21_trim
TESTFILES = s21_memchr s21_memcmp s21_memcpy s21_memset s21_strncat s21_strchr s21_strncmp s21_strncpy s21_strcspn s21_strerror s21_strlen s21_strpbrk s21_strrchr s21_strstr s21_strtok s21_sprintf s21_sscanf s21_to_upper s21_to_lower s21_insert s21_trim
$(shell echo "RUN TESTS" > log.txt)

all: clean s21_string.a

s21_string.a: s21_string.o
	ar rc s21_string.a $(foreach FILE,$(FILES),$(FILE).o)
	ranlib s21_string.a
	rm *.o

s21_string.o: $(foreach FILE,$(FILES),$(FILE).c) s21_string.h
	 $(foreach FILE,$(FILES), $(shell $(CC) $(CFLAGS) -c $(FILE).c -o $(FILE).o))

test: $(foreach FILE,$(TESTFILES),$(FILE)_test.c) s21_string.a s21_string.h
	$(foreach FILE,$(TESTFILES),$(shell $(CC) $(CFLAGS) $(FILE)_test.c s21_string.a $(TESTFLAGS) -o $(FILE)_test))
	$(foreach FILE,$(TESTFILES),$(shell ./$(FILE)_test >> log.txt))
	$(foreach FILE,$(TESTFILES),$(shell rm -rf $(FILE)_test)) 

gcov_report: $(foreach FILE,$(TESTFILES),$(FILE)_test.c) s21_string.a s21_string.h
	$(foreach FILE,$(TESTFILES),$(shell $(CC) $(CFLAGS) $(FILE)_test.c s21_string.a $(TESTFLAGS) $(COVFLAGS) -o $(FILE)_test))
	$(foreach FILE,$(TESTFILES),$(shell ./$(FILE)_test >> log.txt))
	$(foreach FILE,$(TESTFILES),$(shell lcov -t "TEST GCOV" -o $(FILE)_test.info -c -d .))
	$(foreach FILE,$(TESTFILES),$(shell genhtml -o report $(FILE)_test.info))
	###_genhtml -o report *.info
	rm -rf *.gcda *.gcno *.info
	open report/index.html

style:
	clang-format -i --style=Google *.c *.h

clean:
	rm -rf report 
	$(foreach FILE, $(FILES), $(shell rm -rf $(FILE)_test)) 
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcda *.gcno *.info

leaks: $(foreach FILE,$(TESTFILES),$(FILE)_test.c) s21_string.a s21_string.h
	clear
	$(foreach FILE,$(TESTFILES),$(shell $(CC) $(CFLAGS) $(FILE)_test.c s21_string.a $(TESTFLAGS) -o $(FILE)_test))
	$(foreach FILE,$(TESTFILES),$(shell valgrind --tool=memcheck --leak-check=yes $(FILE)_test))
	$(foreach FILE,$(TESTFILES),$(shell leaks -atExit -- $(FILE)_test))
	

.PHONY: all, test, gcov_report, style, clean, s21_string.a
