[BITS 32]

; Descriptor flag macros
%define SEG_DESCTYPE(x)  ((x) << 0x04) ; Descriptor type (0 = system, 1 = code/data)
%define SEG_PRES(x)      ((x) << 0x07) ; Present (segment is valid)
%define SEG_SAVL(x)      ((x) << 0x0C) ; Available for software use
%define SEG_LONG(x)      ((x) << 0x0D) ; Long mode (64-bit code segment)
%define SEG_SIZE(x)      ((x) << 0x0E) ; Size (0 = 16-bit segment, 1 = 32-bit segment)
%define SEG_GRAN(x)      ((x) << 0x0F) ; Granularity (0 = byte granularity, 1 = 4KB granularity)
%define SEG_PRIV(x)      (((x) & 0x03) << 0x05) ; Privilege level (0-3)

; Data segment types
%define SEG_DATA_RD        0x00 ; Read-Only
%define SEG_DATA_RDA       0x01 ; Read-Only, Accessed
%define SEG_DATA_RDWR      0x02 ; Read/Write
%define SEG_DATA_RDWRA     0x03 ; Read/Write, Accessed
%define SEG_DATA_RDEXPD    0x04 ; Read-Only, Expand Down
%define SEG_DATA_RDEXPDA   0x05 ; Read-Only, Expand Down, Accessed
%define SEG_DATA_RDWREXPD  0x06 ; Read/Write, Expand Down
%define SEG_DATA_RDWREXPDA 0x07 ; Read/Write, Expand Down, Accessed

; Code segment types
%define SEG_CODE_EX        0x08 ; Execute-Only
%define SEG_CODE_EXA       0x09 ; Execute-Only, Accessed
%define SEG_CODE_EXRD      0x0A ; Execute/Read
%define SEG_CODE_EXRDA     0x0B ; Execute/Read, Accessed
%define SEG_CODE_EXC       0x0C ; Execute-Only, Conforming
%define SEG_CODE_EXCA      0x0D ; Execute-Only, Conforming, Accessed
%define SEG_CODE_EXRDC     0x0E ; Execute/Read, Conforming
%define SEG_CODE_EXRDCA    0x0F ; Execute/Read, Conforming, Accessed

; GDT Segment Descriptor Macros for Kernel and User-Space
; These macros define Global Descriptor Table (GDT) entries for x86 protected mode
; with different privilege levels (PL0 = Kernel, PL3 = User)
;
; GDT_CODE_PL0: Kernel-mode code segment
;   - Descriptor type: System segment
;   - Present: Yes (segment is valid)
;   - Available: No (not available for software use)
;   - Long mode: No (32-bit mode)
;   - Size: 32-bit
;   - Granularity: 4KB page-based
;   - Privilege level: 0 (Kernel)
;   - Type: Code, Execute/Read
;
; GDT_DATA_PL0: Kernel-mode data segment
;   - Same flags as CODE_PL0 but Type: Data, Read/Write
;
; GDT_STACK_PL0: Kernel-mode stack segment
;   - Same flags as DATA_PL0 (stack uses data segment properties)
;
; GDT_CODE_PL3: User-mode code segment
;   - Same as CODE_PL0 but Privilege level: 3 (User)
;
; GDT_DATA_PL3: User-mode data segment
;   - Same as DATA_PL0 but Privilege level: 3 (User)
;
; GDT_STACK_PL3: User-mode stack segment
;   - Same as DATA_PL3 (stack uses data segment properties)
%define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
					 SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
					 SEG_PRIV(0)     | SEG_CODE_EXRD

%define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
					 SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
					 SEG_PRIV(0)     | SEG_DATA_RDWR

%define GDT_STACK_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
					 SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
					 SEG_PRIV(0)     | SEG_DATA_RDWR

%define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
					 SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
					 SEG_PRIV(3)     | SEG_CODE_EXRD

%define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
					 SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
					 SEG_PRIV(3)     | SEG_DATA_RDWR

%define GDT_STACK_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
					 SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
					 SEG_PRIV(3)     | SEG_DATA_RDWR

%define GET_ACCESS(x) ((x) & 0xFF)
%define GET_FLAGS(x)  (((x) >> 8) & 0xFF)

section .data
align 4

gdt_start:
    ; 0x00 : Null Descriptor
    dq 0

    ; 0x08 : Kernel Code (PL0)
    dw 0xFFFF                   ; Limit (0-15)
    dw 0x0000                   ; Base (0-15)
    db 0x00                     ; Base (16-23)
    db GET_ACCESS(GDT_CODE_PL0) ; Access Byte
    db GET_FLAGS(GDT_CODE_PL0) | 0x0F ; Flags + Limit (16-19) -> 0xF pour 4Go
    db 0x00                     ; Base (24-31)

    ; 0x10 : Kernel Data (PL0)
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db GET_ACCESS(GDT_DATA_PL0)
    db GET_FLAGS(GDT_DATA_PL0) | 0x0F
    db 0x00

	; 0x18 : Kernel Stack (PL0)
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db GET_ACCESS(GDT_STACK_PL0)
	db GET_FLAGS(GDT_STACK_PL0) | 0x0F
	db 0x00

    ; 0x20 : User Code (PL3)
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db GET_ACCESS(GDT_CODE_PL3)
    db GET_FLAGS(GDT_CODE_PL3) | 0x0F
    db 0x00

    ; 0x28 : User Data (PL3)
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db GET_ACCESS(GDT_DATA_PL3)
    db GET_FLAGS(GDT_DATA_PL3) | 0x0F
    db 0x00

	; 0x30 : User Stack (PL3)
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db GET_ACCESS(GDT_STACK_PL3)
	db GET_FLAGS(GDT_STACK_PL3) | 0x0F
	db 0x00

gdt_end:

gdtr:
    dw gdt_end - gdt_start - 1 ; Limite
    dd 0x00000800              ; Base

section .text
global _setup_gdt

_setup_gdt:
    mov esi, gdt_start          ; Source (at 1Mo+)
    mov edi, 0x800              ; Destination address in memory
    mov ecx, (gdt_end - gdt_start)
    cld                         ; Clear direction flag for forward copying
    rep movsb                   ; Copy GDT to 0x800 byte by byte

    lgdt [gdtr]
	mov ax, 0x10          ; Load Kernel Data segment selector
	mov ds, ax            ; Load data segment selector into DS (The Data Segment is used for all data accesses, including stack)
	mov es, ax            ; Load data segment selector into ES (Extra Segment is often used for string operations)
	mov fs, ax            ; Load data segment selector into FS (General-purpose segment, often used for thread-local storage)
	mov gs, ax            ; Load data segment selector into GS (General-purpose segment, often used for thread-local storage)
	mov ss, ax            ; Load data segment selector into SS (Stack Segment is used for stack operations)
	jmp 0x08:.flush        ; Far jump to flush the instruction pipeline
.flush:
	ret
