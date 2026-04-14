CC=gcc
SRCS = main.c display.c input.c catch.c
NAME = catch.11

all : $(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) -pthread -o $@

run : all
	./$(NAME)

clean :
	rm -rf $(NAME)
	rm -rf catch.debug

debug :
	$(CC) $(SRCS) -g -pthread -o catch.debug
	gdb catch.debug

.PHONY = debug clean run all
