section .data
    scale: dd 255.0

section .text
    global imgCvtGrayFloatToInt

imgCvtGrayFloatToInt:
    ; RCX = float* input
    ; RDX = uint8_t* output
    ; R8D = width
    ; R9D = height

    push rbx
    mov eax, r8d
    imul eax, r9d            ; eax = total pixels
    xor ebx, ebx             ; index = 0

.loop:
    cmp ebx, eax
    jge .done

    ; Load float input[ebx] -> xmm0
    movss xmm0, [rcx + rbx * 4]
    movss xmm1, [rel scale]
    mulss xmm0, xmm1         ; xmm0 = input[i] * 255.0

    ; Convert float to int
    cvtss2si edi, xmm0

    ; Clamp to [0, 255]
    cmp edi, 0
    jl .set_zero
    cmp edi, 255
    jg .set_max
    jmp .store

.set_zero:
    xor edi, edi
    jmp .store

.set_max:
    mov edi, 255

.store:
    mov [rdx + rbx], dil     ; store to output[rbx] as uint8
    inc ebx
    jmp .loop

.done:
    pop rbx
    ret
