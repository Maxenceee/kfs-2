MANDATORY_DIR   =   sources
INCLUDES_DIR    =   includes
OBJ_DIR         =   .objs
ISO_DIR         =   iso_root

SRCS            =   $(shell find $(MANDATORY_DIR) -name "*.c")
SRCS_ASM        =   $(shell find $(MANDATORY_DIR) -name "*.asm")

OBJS            =   $(patsubst $(MANDATORY_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_ASM        =   $(patsubst $(MANDATORY_DIR)/%.asm, $(OBJ_DIR)/%.o, $(SRCS_ASM))

NAME            =   Galileo.bin
ISO_NAME        =   Galileo.iso

CC              =   gcc
ASM             =   nasm
RM              =   rm -rf

CFLAGS          =   -m32 -fno-builtin -fno-stack-protector \
                    -nostdlib -nodefaultlibs -ffreestanding \
                    -fno-pie -Wall \
					-I $(INCLUDES_DIR)
# 					-Wextra -Werror 

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

GREEN           =   \033[1;32m
YELLOW          =   \033[1;33m
RED             =   \033[1;31m
DEFAULT         =   \033[0m

all: $(ISO_NAME)

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling C [$<]$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.asm
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling ASM [$<]$(DEFAULT)"
	@$(ASM) $(ASMFLAGS) $< -o $@

$(NAME): $(OBJS) $(OBJS_ASM)
	@echo "$(YELLOW)Linking $(NAME)...$(DEFAULT)"
	@$(CC) $(LDFLAGS) $^ -o $(NAME)

$(ISO_NAME): $(NAME)
	@echo "$(YELLOW)Creating ISO...$(DEFAULT)"
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp $(NAME) $(ISO_DIR)/boot/
	@echo "$$GRUB_CONFIG" > $(ISO_DIR)/boot/grub/grub.cfg
	@grub-mkrescue -o $(ISO_NAME) $(ISO_DIR) 
	@echo "$(GREEN)$(ISO_NAME) is ready!$(DEFAULT)"

clean:
	@echo "$(RED)Cleaning objects$(DEFAULT)"
	@$(RM) $(OBJ_DIR) $(ISO_DIR)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@$(RM) $(NAME) $(ISO_NAME)

run-kernel: $(NAME)
	qemu-system-i386 -kernel $(NAME) -icount shift=2 -vga std

run-iso: $(ISO_NAME)
	qemu-system-i386 -cdrom $(ISO_NAME) -icount shift=2 -vga std

re: fclean all

.PHONY: all clean fclean re