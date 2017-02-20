export CC = gcc

export LIBHEADERLOC = include
export LIBLOCATION = lib

export CFLAGS = -g -O2 -w -I$(LIBHEADERLOC) -L$(LIBLOCATION)

queue_% :
	@make -f app/queue/Makefile clean
	@ln -sf app/queue/queue_ll.out ./queue_ll.out
