SOURCE_DIR      =   sources
INCLUDES_DIR    =   includes
OBJ_DIR         =   .objs
ISO_DIR         =   iso_root

SRCS            =   $(shell find $(SOURCE_DIR) -name "*.c" 2>/dev/null)
SRCS_ASM        =   $(shell find $(SOURCE_DIR) -name "*.asm" 2>/dev/null)

OBJS            =   $(patsubst $(SOURCE_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_ASM        =   $(patsubst $(SOURCE_DIR)/%.asm, $(OBJ_DIR)/%.o, $(SRCS_ASM))
ALL_OBJS        =   $(OBJS) $(OBJS_ASM)

NAME            =   Galileo.bin
ISO_NAME        =   Galileo.iso

CC              =   gcc
ASM             =   nasm
RM              =   rm -rf

CFLAGS          =   -m32 -fno-builtin -fno-stack-protector \
                    -nostdlib -nodefaultlibs -ffreestanding \
                    -fno-pie -Wall \
                    -I $(INCLUDES_DIR) -I $(SOURCE_DIR) \
                    -Wextra -Werror 

ASMFLAGS        =   -f elf32
LDFLAGS         =   -m32 -T linker.ld -nostdlib -nodefaultlibs -no-pie

define GRUB_CONFIG
set timeout=0
set default=0
menuentry "$(NAME)" {
    multiboot /boot/$(NAME)
    boot
}
endef
export GRUB_CONFIG

BOLD            =   \033[1m
DIM             =   \033[2m
CYAN            =   \033[36m
GREEN           =   \033[32m
YELLOW          =   \033[33m
MAGENTA         =   \033[35m
RED             =   \033[31m
RESET           =   \033[0m

TOTAL_FILES     :=  $(words $(ALL_OBJS))
CURRENT_FILE    :=  0

define print_progress
	$(eval CURRENT_FILE=$(shell expr $(CURRENT_FILE) + 1))
	$(eval PERCENT=$(shell expr $(CURRENT_FILE) \* 100 / $(TOTAL_FILES)))
	$(eval PROGRESS=$(shell expr $(CURRENT_FILE) \* 20 / $(TOTAL_FILES)))
	$(eval REMAINING=$(shell expr 20 - $(PROGRESS)))
	@printf "\r\033[K   $(GREEN)✔$(RESET) %b %-30s$(RESET)\n" "$(1)" "$(2)"
	@printf "   [$(GREEN)%s$(DIM)%s$(RESET)] %3d%%" \
		"$(shell printf '%0.s#' $$(seq 1 $(PROGRESS) 2>/dev/null))" \
		"$(shell printf '%0.s-' $$(seq 1 $(REMAINING) 2>/dev/null))" \
		"$(PERCENT)"
endef

all: $(ISO_NAME)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(@D)
	$(call print_progress,$(YELLOW)Compiling C  , $<)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.asm
	@mkdir -p $(@D)
	$(call print_progress,$(MAGENTA)Compiling ASM, $<)
	@$(ASM) $(ASMFLAGS) $< -o $@

$(NAME): $(ALL_OBJS)
	@printf "\r\033[K\n   $(BOLD)$(CYAN)Linking Kernel...$(RESET)\n"
	@$(CC) $(LDFLAGS) $^ -o $(NAME)
	@printf "   $(GREEN)✔ $(NAME) compiled successfully!$(RESET) $(DIM)(%s)$(RESET)\n\n" "$$(du -h $(NAME) | cut -f1)"

$(ISO_NAME): $(NAME)
	@printf "   $(BOLD)$(CYAN)Creating ISO image...$(RESET)\n"
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp $(NAME) $(ISO_DIR)/boot/
	@echo "$$GRUB_CONFIG" > $(ISO_DIR)/boot/grub/grub.cfg
	@grub-mkrescue -o $(ISO_NAME) $(ISO_DIR) 2>&1 | grep -i "error" || true
	@if [ -f $(ISO_NAME) ]; then \
		printf "   $(BOLD)$(GREEN)✔ $(ISO_NAME) is ready to boot!$(RESET) $(DIM)(%s)$(RESET)\n\n" "$$(du -h $(ISO_NAME) | cut -f1)"; \
	else \
		printf "   $(RED)✖ Failed to create $(ISO_NAME)$(RESET)\n\n"; \
		exit 1; \
	fi

clean:
	@printf "   $(RED)➤ Cleaning objects...$(RESET)\n"
	@$(RM) $(OBJ_DIR) $(ISO_DIR)

fclean: clean
	@printf "   $(RED)➤ Removing executables...$(RESET)\n"
	@$(RM) $(NAME) $(ISO_NAME)

run-kernel: $(NAME)
	@printf "   $(CYAN)⌘ Launching QEMU (Kernel Mode)...$(RESET)\n"
	@qemu-system-i386 -kernel $(NAME) -vga std

run-iso: $(ISO_NAME)
	@printf "   $(CYAN)⌘ Launching QEMU (ISO Mode)...$(RESET)\n"
	@qemu-system-i386 -cdrom $(ISO_NAME) -vga std

re: fclean all

.PHONY: all clean fclean re run-kernel run-iso