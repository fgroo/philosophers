NAME := philo

### DIR ###
OBJ_DIR = ./obj
INC_DIR = ./inc
SRC_DIR = ./src
PRINT_DIR = ./src/print

### FLAGS ###
CFLAGS :=
CFLAGS += -Wall  
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wpedantic
CFLAGS += -pthread
CFLAGS += -O2
CFLAGS += -D_FORTIFY_SOURCE=2
CFLAGS += -I$(INC_DIR)

LDFLAGS :=
LDFLAGS += -pthread

ifeq ($(GDB), 1)
	CFLAGS += -g
	CFLAGS += -fno-omit-frame-pointer
	CFLAGS := $(filter-out -O2 -D_FORTIFY_SOURCE=2,$(CFLAGS))
endif

ifeq ($(TSAN), 1)
	CFLAGS += -fsanitize=thread
	LDFLAGS += -fsanitize=thread
endif

ifeq ($(LSAN), 1)
	CFLAGS += -fsanitize=leak
	LDFLAGS += -fsanitize=leak
endif

ifeq ($(ASAN), 1)
	CFLAGS += -fsanitize=address
	LDFLAGS += -fsanitize=address
endif


### .o ###

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

### .h ###

INC :=

vpath %.h $(INC_DIR)

INC += philo.h

### .c ###
SRC :=

vpath %.c $(SRC_DIR)
SRC += main.c
SRC += create_philos.c
SRC += cleanup1.c
SRC += eating1.c
SRC += sleeping1.c
SRC += thinking1.c
SRC += exiting1.c
SRC += hub1.c
SRC += dying1.c

vpath %.c $(PRINT_DIR)
SRC += print1.c


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -fr $(OBJ_DIR)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: $(NAME) clean fclean re all