; pit.asm - Programmable Interval Timer (PIT) setup for x86 protected mode
; This code initializes the PIT to generate timer interrupts at a specified frequency (TARGET_HZ).
; The PIT is a crucial component for implementing multitasking and timekeeping in an operating system.
[BITS 32]

; Define PIT frequency and divisor for the desired timer interrupt frequency
; The PIT operates at a base frequency of 1.193182 MHz, and the divisor is calculated
; to achieve the target frequency (e.g., 100 Hz for 100 timer interrupts per second).
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
