ifdef OS
   RM = del 
   FixPath = $(subst /,\,$1)
   EXEC = exe
else
   ifeq ($(shell uname), Linux)
      RM = rm -rf
      FixPath = $1
	  EXEC = out
   endif
endif
.PHONY: run clean test doc all

all:
	gcc sdl_test5.c -lmingw32 -lSDL2main -lSDL2 -o $(call FixPath,example.$(EXEC))