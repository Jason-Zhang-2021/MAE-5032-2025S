CC := gcc

foo: foo.o bar.o
	$(CC) -o foo foo.o bar.o

foo.o: foo.c bar.h
	$(CC) -c foo.c

bar.o: bar.c bar.h
	$(CC) -c bar.c

clean:
	rm -rf *.o foo
