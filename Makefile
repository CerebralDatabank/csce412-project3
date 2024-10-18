CC := g++
CFLAGS := -Wall -Werror

all:
	$(CC) $(CFLAGS) -o project3.out *.cpp

.PHONY: clean
clean:
	rm -f project3.out
