export CC = gcc

export LIBHEADERLOC = include
export LIBLOCATION = lib

export CFLAGS = -g -O2 -w -I$(LIBHEADERLOC) -L$(LIBLOCATION)

queue :
	@make -f app/queue/Makefile 
	@ln -sf app/queue/queue_ll.out ./queue_ll.out

rebuild_queue : reconfigure_queue queue

reconfigure_queue :
	@bash scripts/createconfig.sh desc/queue.desc configs/queue_defconfig
