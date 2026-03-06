MACARRAY MACRO arr_addr
    LEA SI, arr_addr
    CALL odd_even_proc
ENDM

org 100h

.data
array db 2, 0, 4, 7, 1, 9
oddmsg db 0dh,0ah,'ODD Digits: $'
evenmsg db 0dh,0ah,'EVEN Digits: $'

.code
main proc
    mov ax, @data
    mov ds, ax

    MACARRAY array
    
    MACARRAY array
    
    mov ah,4ch
    int 21h
main endp

odd_even_proc proc

    
    mov dx, offset oddmsg
    mov ah, 09h
    int 21h

    mov cx, 6
    push si       

odd_loop:
    mov al,[si]
    test al,1
    jz not_odd

    add al,30h
    mov dl,al
    mov ah,02h
    int 21h

    mov dl,' '
    int 21h

not_odd:
    inc si
    loop odd_loop

    mov dx, offset evenmsg
    mov ah, 09h
    int 21h

    pop si         
    mov cx,6

even_loop:
    mov al,[si]
    test al,1
    jnz not_even

    add al,30h
    mov dl,al
    mov ah,02h
    int 21h

    mov dl,' '
    int 21h

not_even:
    inc si
    loop even_loop

    ret
odd_even_proc endp

end main
