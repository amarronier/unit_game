NAME = endgame

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SDL = -F resource/framework -I resource/framework/SDL2.framework/SDL2 -I resource/framework/SDL2_image.framework/SDL2_image

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
INC_FILES = $(wildcard $(INC_DIR)/*.h)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))


CC = clang
CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic) -g \

SDL_FLAGS = -rpath resource/framework -framework SDL2 \
		-framework SDL2_image \
		-I resource/framework/SDL2_image.framework/Headers \
		-framework SDL2_mixer \
        -I inc/framework/SDL2_mixer.framework/Headers \

MKDIR = mkdir -p
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) $(SDL_FLAGS) $(SDL)
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) $(SDL)


$(OBJ_DIR):
	@$(MKDIR) $@

clean:
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)

# удаляем и заново собираем библиотеку
reinstall: uninstall all

# .PHONY - это явное указание имен целей мейкфайла, например, если
# в папке будет файл clean и попытаться выполнить команду make clean,
# то make попытается выполнить файл clean, а не цель clean
.PHONY: all uninstall clean reinstall