[BITS 32]
global ksleep

;
; Since for now we don't have a timer interrupt, we will use a simple busy-wait loop for ksleep.
; The PIT requires that a GDT is defined.
;

; void ksleep(uint32_t duration)
ksleep:
    push ebp
    mov ebp, esp
    push ecx
    push eax

    mov ecx, [ebp + 8]
    test ecx, ecx
    jz .done

.outer_loop:
    push ecx
    ; With -icount shift=2, about 40000 iterations ~= 1ms
    mov ecx, 40000       
.inner_loop:
    nop
    loop .inner_loop
    pop ecx
    loop .outer_loop

.done:
    pop eax
    pop ecx
    pop ebp
    ret