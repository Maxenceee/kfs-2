; kernel.asm - Entry point for the kernel in x86 protected mode
section .multiboot
	align 4
	dd 0x1BADB002              ; Magic number for Multiboot
	dd 0x00                    ; Flags
	dd -(0x1BADB002 + 0x00)    ; Checksum

extern _setup_gdt
extern _setup_idt

extern kmain

section .text
global _start
_start:
	cli                     ; Disable interrupts during setup

	call _setup_gdt         ; Setup Global Descriptor Table (GDT) for memory segmentation

	mov esp, _kstack_base	; Initialize stack pointer to the top of the reserved stack space

	call _setup_idt         ; Setup Interrupt Descriptor Table (IDT) for handling interrupts

	sti                     ; Enable interrupts

	; Call Kernel main function
	call kmain

; Keeping Kernel alive!
hang:
	hlt
	jmp hang

section .bss
global _kstack_base
_kstack_start:
align 16
resb 8192                   ; Reserve 8 Ko for the stack
_kstack_base:
