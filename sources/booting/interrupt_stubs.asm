; interrupt_stubs.asm - Interrupt handler stubs for x86 protected mode
; This code defines the assembly stubs for handling hardware interrupts, specifically
; the timer (PIT) and keyboard interrupts. Each stub saves the CPU state, calls the
; corresponding C handler function, sends an End of Interrupt (EOI) signal to the PIC,
; and then returns from the interrupt using the IRET instruction.
[BITS 32]

extern _irq_pit_handler
extern _irq_kbd_handler

global _irq_pit_handler_stub
global _irq_kbd_handler_stub

_irq_pit_handler_stub:
	pushad			; Save all general-purpose registers on the stack
	cld				; Clear direction flag to ensure string operations work correctly in C handlers
	call _irq_pit_handler
	mov al, 0x20	; Send End of Interrupt (EOI) signal to the PIC
	out 0x20, al
	popad			; Restore all general-purpose registers from the stack
	iretd			; Return from the interrupt, restoring EIP, CS, and EFLAGS

_irq_kbd_handler_stub:
	pushad			; Save all general-purpose registers on the stack
	cld				; Clear direction flag to ensure string operations work correctly in C handlers
	call _irq_kbd_handler
	mov al, 0x20	; Send End of Interrupt (EOI) signal to the PIC
	out 0x20, al
	popad			; Restore all general-purpose registers from the stack
	iretd			; Return from the interrupt, restoring EIP, CS, and EFLAGS
