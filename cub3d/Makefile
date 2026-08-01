# Project configuration
PROJECT     := cub3D
NAME        := $(PROJECT)

# Directories
SRC_DIR     := src
LIBFT_DIR   := lib/libft
MLX42_DIR   := lib/MLX42
LIBFT       := $(LIBFT_DIR)/bin/libft.a
MLX42_LIB   := $(MLX42_DIR)/build/libmlx42.a

# Compiler settings
CC          := cc
MODE        ?= release
BONUS       ?= 0
BASE_CFLAGS := -Wall -Wextra -Werror
PIE_CFLAGS  := -fPIE
INCLUDES    := -Iinclude -iquote $(LIBFT_DIR)/include \
               -I$(MLX42_DIR)/include/MLX42
DEPFLAGS    := -MMD -MP
LDFLAGS     := -pie

ifeq ($(MODE),release)
OPTFLAGS    := -O2
else ifeq ($(MODE),debug)
OPTFLAGS    := -O0 -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
else
$(error Unsupported MODE '$(MODE)'; use release or debug)
endif

FEATURE_TAG := mandatory
ifeq ($(BONUS),1)
CPPFLAGS    += -DBONUS_BUILD
FEATURE_TAG := bonus
endif

BUILD_TAG   := $(MODE)-$(FEATURE_TAG)

BIN_DIR     := bin/$(BUILD_TAG)
CFLAGS      := $(BASE_CFLAGS) $(OPTFLAGS) $(PIE_CFLAGS) $(INCLUDES)

# MLX42 flags for graphics (Linux)
MLX42_FLAGS := -I$(MLX42_DIR)/include -ldl -lglfw -pthread -lm

# Build tools
RM          := rm -f
RM_RF       := rm -rf
MKDIR_P     := mkdir -p

# Source files
PARSER_SRCS := src/parser/check_store_player.c \
               src/parser/check_walls.c \
               src/parser/errors.c \
               src/parser/fill_scene_cfg.c \
               src/parser/free_structs.c \
               src/parser/init_file.c \
               src/parser/init_scene_cfg.c \
               src/parser/input_control.c \
               src/parser/load_map.c \
               src/parser/parse_rgb.c \
               src/parser/parse_scene_cfg.c \
               src/parser/parse_store_config.c \
               src/parser/parse_texture.c \
               src/parser/utils.c \
               src/parser/validate_map.c

APP_SRCS    := src/app/engine.c \
               src/app/lifecycle.c \
               src/app/setup.c \
               src/app/setup_memory.c \
               src/app/setup_validation.c \
               src/app/textures.c \
               src/app/textures_bonus.c

WORLD_SRCS  := src/world/world.c \
               src/world/coordinates.c \
               src/world/collision.c

PLAYER_SRCS := src/player/input.c \
               src/player/movement.c \
               src/player/interaction.c

FIRE_SRCS   := src/fire/fire.c \
               src/fire/transition.c \
               src/fire/interaction.c

ORB_SRCS    := src/orb/orb.c \
               src/orb/collection.c \
               src/orb/random.c \
               src/orb/generation.c \
               src/orb/selection.c

RENDER_SRCS := src/render/renderer.c \
               src/render/frame_buffer.c \
               src/render/surface.c \
               src/render/wall/raycast.c \
               src/render/wall/wall.c \
               src/render/fire/fire.c \
               src/render/fire/scorch.c \
               src/render/orb/orb.c \
               src/render/orb/draw.c \
               src/render/minimap/minimap.c \
               src/render/minimap/draw.c \
               src/render/minimap/orbs.c

MAIN_SRCS   := src/main.c

ALL_SRCS    := $(PARSER_SRCS) $(APP_SRCS) $(WORLD_SRCS) $(PLAYER_SRCS) \
               $(FIRE_SRCS) $(ORB_SRCS) $(RENDER_SRCS) $(MAIN_SRCS)

OBJS        := $(ALL_SRCS:src/%.c=$(BIN_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

# Default target
all: $(NAME)

# Main executable
$(NAME): FORCE $(LIBFT) $(MLX42_LIB) $(OBJS)
	@$(MKDIR_P) $(BIN_DIR)
	@$(CC) $(LDFLAGS) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFT) $(MLX42_LIB) $(MLX42_FLAGS) -o $(NAME)
	@echo "Successfully built: $(NAME) [Mode: $(BUILD_TAG)]"

# Build profiles
debug:
	@$(MAKE) MODE=debug all

bonus:
	@$(MAKE) MODE=$(MODE) BONUS=1 all

# Compile objects
$(BIN_DIR)/%.o: src/%.c Makefile
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@

# Build libft
$(LIBFT): FORCE
	@$(MAKE) -C $(LIBFT_DIR) CC="$(CC)" bonus >/dev/null 2>&1

# Build MLX42
$(MLX42_DIR):
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR)

$(MLX42_LIB): | $(MLX42_DIR)
	@cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build >/dev/null 2>&1
	@cmake --build $(MLX42_DIR)/build -j4 >/dev/null 2>&1

-include $(DEPS)

# Clean rules
clean:
	@$(RM_RF) bin
	@$(MAKE) -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@$(RM_RF) $(MLX42_DIR)/build

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean >/dev/null 2>&1

re: fclean all

FORCE:

.PHONY: all clean fclean re debug bonus FORCE
