CC=zcc
CFLAGS=+cpm -lm -lndos -vn -o termy.com
#CFLAGS= +zxn -lndos -clib=classic -create-app -subtype=nex -o test
SRC_DIR ?= ./src
CSRC := $(shell find $(SRC_DIR) -name *.c)

all:
		$(CC) $(CFLAGS) $(CSRC)