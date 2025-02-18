CC = gcc

CFLAGS = -Wall -Wextra -pedantic -ansi -g
LDFLAGS = $(CFLAGS)

BIN = calc.exe

all: clean $(BIN)

$(BIN): main.o expression.o long_arithmetic.o menu.o utils.o converter.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c
	$(CC) -c $(CFLAGS) -o $@ $<

expression.o: expression.c
	$(CC) -c $(CFLAGS) -o $@ $<

long_arithmetic.o: long_arithmetic.c
	$(CC) -c $(CFLAGS) -o $@ $<

menu.o: menu.c
	$(CC) -c $(CFLAGS) -o $@ $<

utils.o: utils.c
	$(CC) -c $(CFLAGS) -o $@ $<

converter.o: converter.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o
