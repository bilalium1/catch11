CC=gcc
SRCS = src/main.c src/display.c src/input.c src/catch.c src/parser.c
NAME = catch.11

all : $(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) -pthread -o $@

run : all
	./$(NAME) 11 11 5 11

clean :
	rm -rf $(NAME)
	rm -rf catch.debug

debug :
	$(CC) $(SRCS) -g -pthread -o catch.debug
	gdb catch.debug

.PHONY = debug clean run all
