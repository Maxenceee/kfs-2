; kernel.asm - Entry point for the kernel in x86 protected mode
section .multiboot_header
header_start:
    dd 0xe85250d6                ; Magic number (Multiboot2)
    dd 0                         ; Architecture 0 (protected mode i386)
    dd header_end - header_start ; Header length
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; Checksum

    ; --- TAG FRAMEBUFFER ---
    align 8
    dw 5                         ; Type 5 : Framebuffer request
    dw 0                         ; Flags
    dd 20                        ; Taille du tag (20 octets)
    dd 1024                      ; Largeur souhaitée (Width)
    dd 768                       ; Hauteur souhaitée (Height)
    dd 32                        ; Profondeur (32 bits par pixel pour du RGBA)

    ; Tag de fin
    align 8
    dw 0
    dw 0
    dd 8
header_end: