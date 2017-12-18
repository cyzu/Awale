
#  Makefile
#  Master1_Awale
#
#  Created by Chloé 雪乃 BENSOUSSAN 下村 on 18/12/2017.
#  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.

SHELL = /bin/bash
CC    = gcc
LIBS = -lm
CCFLAGS = -Wall -ggdb

OBJ = Awale.o Utils.o
EXEC = awale


all: $(EXEC)

$(EXEC): main.c $(OBJ)
	$(CC) $(CCFLAGS) $^ -o $(EXEC)

.c.o:
	$(CC) $(CCFLAGS) -c $<

.PHONY : clean

clean:
	rm -f $(OBJ) $(EXEC)
