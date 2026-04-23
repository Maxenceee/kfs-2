[BITS 32]

section .data
align 8

idt_start:
	%rep 32
        dq 0        ; The first 32 entries are reserved for CPU exceptions and interrupts
    %endrep

	; 0x20 (32) : PIT (Timer)
    dw 0            ; Offset 0-15 (sera rempli au runtime ou via macros)
    dw 0x08         ; Sélecteur de segment (Kernel Code)
    db 0
    db 0x8E         ; Access Byte (Present, Ring 0, Interrupt Gate)
    dw 0            ; Offset 16-31

    ; 0x21 (33) : Clavier PS/2
    dw 0
    dw 0x08
    db 0
    db 0x8E
    dw 0

idt_end:

idtr:
    dw idt_end - idt_start - 1
    dd idt_start

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
    ; ICW4 : Mode 8086
    mov al, 0x01
    out 0x21, al
    out 0xA1, al
    ; Masquage : Enabling only IRQ0 (PIT) and IRQ1 (Clavier)
    mov al, 0x00
    out 0x21, al
    out 0xA1, al
    ret

global _setup_idt
extern _irq_pit_handler_stub
extern _irq_kbd_handler_stub

extern _init_pit

_setup_idt:
    ; Configure IRQ0 (PIT) - Entry 32
    mov eax, _irq_pit_handler_stub
    mov [idt_start + 32*8], ax          ; Offset 0-15
    shr eax, 16
    mov [idt_start + 32*8 + 6], ax      ; Offset 16-31

    ; Configure IRQ1 (Keyboard) - Entry 33
    mov eax, _irq_kbd_handler_stub
    mov [idt_start + 33*8], ax
    shr eax, 16
    mov [idt_start + 33*8 + 6], ax

    lidt [idtr]

    call _pic_remap

	call _init_pit

    ret
