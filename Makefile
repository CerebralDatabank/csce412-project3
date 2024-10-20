CC := g++
CFLAGS := -Wall -Werror

all:
	$(CC) $(CFLAGS) -o project3 *.cpp

.PHONY: clean
clean:
	rm -f project3
