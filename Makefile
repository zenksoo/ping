CC = cc -fsanitize=address -g3

RM = rm -rf

TARGET = ping

FILES = main.c common.c getip.c

INCLUDE_DIR = include/
SRC_DIR = src/
BUILD_DIR = build/

OBJ= $(addprefix $(BUILD_DIR), $(FILES:.c=.o))


$(TARGET): $(BUILD_DIR) $(OBJ)
	$(CC) $(OBJ) -o $@


$(BUILD_DIR):
		mkdir $(BUILD_DIR)


$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -I$(INCLUDE_DIR) -c $< -o $@
	
all: $(TARGET)

clean:
	@$(RM) $(OBJ) $(BUILD_DIR)

fclean: clean
	@$(RM) $(TARGET)

re: fclean all

