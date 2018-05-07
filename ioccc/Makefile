CC = gcc
#FLAGS = -Wall -Wextra -pedantic -g
FLAGS = -g
SPECIAL_HEADER =
INCLUDES =
OBJ_DIR = obj
C_FILES = $(wildcard *.c)
H_FILES = $(wildcard *.h)
O_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(C_FILES))
TARGETS = $(patsubst %.c,%.exe,$(C_FILES))

all: $(TARGETS)

%.exe: %.c $(H_FILES)
	$(CC) $(FLAGS) $(SPECIAL_HEADER) $< -o $@
