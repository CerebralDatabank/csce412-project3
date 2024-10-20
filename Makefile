CC := g++
CFLAGS := -Wall -Werror

all:
	$(CC) $(CFLAGS) -o project3 *.cpp

.PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	del project3*
else
	rm -f project3
endif
