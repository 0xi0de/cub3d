CC = gcc
CFLAGS = -Iinclude -Ilib -g -fsanitize=address
LFLAGS = -lm -L./lib -lmlx -lX11 -lXext

BUILD_DIR = build
OBJS_DIR = $(BUILD_DIR)/objs
DEPS_DIR = $(BUILD_DIR)/deps

PRECOMPILE = mkdir -p $(dir $@)
POSTCOMPILE = sleep 0

ifndef NODEPS

PRECOMPILE += ;mkdir -p $(dir $(DEPS_DIR)/$*)
CFLAGS += -MT $@ -MMD -MP -MF $(DEPS_DIR)/$*.Td
POSTCOMPILE += ;mv -f $(DEPS_DIR)/$*.Td $(DEPS_DIR)/$*.d && touch $@

endif

include src.mk

OBJS = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRC))
OBJS_CUBE = $(filter $(OBJS_DIR)/Cub3d/%, $(OBJS))
OBJS_MLX = $(filter $(OBJS_DIR)/Minilibx/%, $(OBJS))
OBJS_COMMON = $(filter $(OBJS_DIR)/Common/%, $(OBJS))

all: cub3d

$(OBJS_DIR)/%.o: src/%.c Makefile
	@$(PRECOMPILE)
	make -s -C ./lib/
	$(CC) $(CFLAGS) -c -o $@ $<
	@$(POSTCOMPILE)

cub3d: $(OBJS_CUBE) $(OBJS_COMMON) $(OBJS_MLX)

cub3d:
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

clean:
	make -C lib/ clean
	rm -rf build

fclean: clean
	rm -rf cub3d

re:
	$(MAKE) fclean
	$(MAKE) all

include $(wildcard $(DEPS_DIR)/**/*.d)

.PHONY: all clean fclean re test
