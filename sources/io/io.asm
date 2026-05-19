; io.asm - I/O port access functions for x86 architecture
; This code provides low-level functions to perform input and output operations on I/O ports.
[BITS 32]

global outb
; void outb(uint16_t port, uint8_t data)
outb:
	mov dx, [esp + 4]    ; Gets the port (1st argument)
	mov al, [esp + 8]    ; Gets the data (2nd argument)
	out dx, al           ; Sends the data to the port!
	ret

global outw
; void outw(uint16_t port, uint16_t data)
outw:
	mov dx, [esp + 4]    ; Gets the port (1st argument)
	mov ax, [esp + 8]    ; Gets the data (2nd argument)
	out dx, ax           ; Sends the data to the port!
	ret

global outl
; void outl(uint16_t port, uint32_t data)
outl:
	mov dx, [esp + 4]    ; Gets the port (1st argument)
	mov eax, [esp + 8]   ; Gets the data (2nd argument)
	out dx, eax          ; Sends the data to the port!
	ret

global inb
; uint8_t inb(uint16_t port)
inb:
	mov dx, [esp + 4]    ; Gets the port (1st argument)
	in al, dx            ; Reads the data from the port into AL
	movzx eax, al        ; Zero-extends AL to EAX for return
	ret

global inw
; uint16_t inw(uint16_t port)
inw:
	mov dx, [esp + 4]    ; Gets the port (1st argument)
	in ax, dx            ; Reads the data from the port into AX
	movzx eax, ax        ; Zero-extends AX to EAX for return
	ret

global inl
; uint32_t inl(uint16_t port)
inl:
	mov dx, [esp + 4]    ; Gets the port (1st argument)
	in eax, dx           ; Reads the data from the port into EAX
	ret
