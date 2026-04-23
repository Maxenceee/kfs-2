[BITS 32]

%define PIT_FREQ 1193182
%define TARGET_HZ 100
%define PIT_DIVISOR (PIT_FREQ / TARGET_HZ)

section .text
global _init_pit
_init_pit:
    ; Send Command Register : 0x36 
    ; (Counter 0, LSB then MSB, Square Wave Mode, Binary)
    mov al, 0x36
    out 0x43, al

    ; Send Divisor to Counter 0
    mov ax, PIT_DIVISOR
    out 0x40, al        ; LSB
    mov al, ah
    out 0x40, al        ; MSB
    ret
