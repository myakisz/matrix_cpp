CC = g++
FLAGS = -Wall -Werror -Wextra
CPPFLAGS = -lgtest -std=c++17 -g -pthread -lpthread

all: s21_matrix_oop.a

clean:
	rm -rf *.o *.a *.gcno *.gcda *.gcov *.html *.css *.out test

s21_matrix_oop.a: s21_matrix_oop.o
	ar rcs s21_matrix_oop.a  s21_matrix_oop.o
	ranlib s21_matrix_oop.a
	rm -rf *.o

s21_matrix_oop.o:
	$(CC) $(FLAGS) $(CPPFLAGS) s21_matrix_oop.cc -c -o s21_matrix_oop.o

test: s21_matrix_oop.a
	clear
	$(CC) tests/test.cc s21_matrix_oop.a -o test `pkg-config --cflags --libs check` $(FLAGS) $(CPPFLAGS)
	./test

gcov_report: add_coverage_flag test
	./test
	gcov -b -l -p -c s21_*.gcno
	gcovr -o gcov_report.html --html --html-details

add_coverage_flag:
	$(eval FLAGS += --coverage)

clang:
	clang-format -i *.cc *.h tests/*.cc

valgrind: test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test