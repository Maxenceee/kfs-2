; idt.asm - Interrupt Descriptor Table setup for x86 protected mode
; This code defines the structure of the Interrupt Descriptor Table (IDT) for handling
; CPU exceptions and hardware interrupts. It includes the setup for remapping the
; Programmable Interrupt Controller (PIC) to avoid conflicts with CPU exceptions, and
; initializes the IDT entries for the timer (PIT) and keyboard interrupts.
[BITS 32]

section .data
align 8

idt_start:
	%rep 32
		dq 0	; The first 32 entries are reserved for CPU exceptions and interrupts
	%endrep

	; 0x20 (32) : PIT (Timer)
	dw 0			; Offset 0-15 (will be filled at runtime or via macros)
	dw 0x08			; Segment selector (Kernel Code)
	db 0
	db 0x8E			; Access Byte (Present, Ring 0, Interrupt Gate)
	dw 0			; Offset 16-31

	; 0x21 (33) : PS/2 Keyboard
	dw 0
	dw 0x08
	db 0
	db 0x8E
	dw 0

idt_end:

idtr:
	dw idt_end - idt_start - 1
	dd idt_start

; A remap is necessary to avoid conflicts between the default PIC interrupt vectors (0-15) and
; the CPU exceptions (0-31). By remapping the PIC, we can ensure that hardware interrupts
; start from vector 0x20 (32) for the master PIC and 0x28 (40) for the slave PIC, allowing
; the CPU exceptions to occupy the first 32 entries of the IDT without interference.
_pic_remap:
	; ICW1 : Initialization 
	mov al, 0x11
	out 0x20, al
	out 0xA0, al
	; ICW2 : Base vector (IRQ0-7 -> 0x20, IRQ8-15 -> 0x28)
	mov al, 0x20
	out 0x21, al
	mov al, 0x28
	out 0xA1, al
	; ICW3 : Master has slave on IRQ2 (0x04), Slave is connected to master's IRQ2 (0x02)
	mov al, 0x04
	out 0x21, al
	mov al, 0x02
	out 0xA1, al
	; ICW4 : 8086 Mode
	mov al, 0x01
	out 0x21, al
	out 0xA1, al
	; Masking : Enable only IRQ0 (PIT) and IRQ1 (Keyboard)
	mov al, 0x00
	out 0x21, al
	out 0xA1, al
	ret

global _setup_idt
extern _irq_pit_handler_stub
extern _irq_kbd_handler_stub

extern _init_pit

_setup_idt:
	; Configure IRQ0 (PIT) - Entry 0x20
	mov eax, _irq_pit_handler_stub
	mov [idt_start + 0x20*8], ax			; Offset 0-15
	shr eax, 16
	mov [idt_start + 0x20*8 + 6], ax		; Offset 16-31

	; Configure IRQ1 (Keyboard) - Entry 0x21
	mov eax, _irq_kbd_handler_stub
	mov [idt_start + 0x21*8], ax
	shr eax, 16
	mov [idt_start + 0x21*8 + 6], ax

	lidt [idtr]

	call _pic_remap

	call _init_pit

	ret
