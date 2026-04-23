[BITS 32]

global outb
; void outb(uint16_t port, uint8_t data)
outb:
	mov dx, [esp + 4]    ; Récupère le port (1er argument)
	mov al, [esp + 8]    ; Récupère la donnée (2e argument)
	out dx, al           ; Envoie la donnée au port !
	ret

global outw
; void outw(uint16_t port, uint16_t data)
outw:
	mov dx, [esp + 4]    ; Récupère le port (1er argument)
	mov ax, [esp + 8]    ; Récupère la donnée (2e argument)
	out dx, ax           ; Envoie la donnée au port !
	ret

global outl
; void outl(uint16_t port, uint32_t data)
outl:
	mov dx, [esp + 4]    ; Récupère le port (1er argument)
	mov eax, [esp + 8]   ; Récupère la donnée (2e argument)
	out dx, eax          ; Envoie la donnée au port !
	ret

global inb
; uint8_t inb(uint16_t port)
inb:
	mov dx, [esp + 4]    ; Récupère le port (1er argument)
	in al, dx            ; Lit la donnée du port dans AL
	movzx eax, al        ; Zéro-étend AL à EAX pour le retour
	ret

global inw
; uint16_t inw(uint16_t port)
inw:
	mov dx, [esp + 4]    ; Récupère le port (1er argument)
	in ax, dx            ; Lit la donnée du port dans AX
	movzx eax, ax        ; Zéro-étend AX à EAX pour le retour
	ret

global inl
; uint32_t inl(uint16_t port)
inl:
	mov dx, [esp + 4]    ; Récupère le port (1er argument)
	in eax, dx           ; Lit la donnée du port dans EAX
	ret
