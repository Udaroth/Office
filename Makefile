
output: office.o office_test.o
	clang office_test.o office.o -o office -fsanitize=address -g

office.o: office.c office.h
	clang -c office.c

office_test.o: office_test.c office.h
	clang -c office_test.c

clean:
	rm *.o output