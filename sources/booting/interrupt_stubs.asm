; interrupt_stubs.asm
extern _irq_pit_handler
extern _irq_kbd_handler

global _irq_pit_handler_stub
global _irq_kbd_handler_stub

_irq_pit_handler_stub:
    pushad
    call _irq_pit_handler
    mov al, 0x20
    out 0x20, al
    popad
    iretd               ; Retour d'interruption (indispensable !)

_irq_kbd_handler_stub:
    pushad
    call _irq_kbd_handler
    mov al, 0x20
    out 0x20, al
    popad
    iretd
