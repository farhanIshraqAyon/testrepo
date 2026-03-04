org 100h

.DATA
    oddArr db 9 dup(0)  
    evenArr db 9 dup(0)  
    
    N db ?
    ODD_SUM dw 0
    EVEN_SUM dw 0
                                                            
    Prompt db 'Enter value of N: $'

.CODE
    mov ax, @DATA ;moving the pointer to the data segment for segment:offset access
    mov ds, ax
    xor ax, ax ; Clearing the value of ax register
    
    
; Taking input here
    ; Input Prompt 
    mov ah, 9
    lea dx,  Prompt
    INT 21h
    
    ;input
    mov AH, 1
    int 21h
    sub al, 48
    mov N, al
     
; ODD array                  
                  
    mov cl, N
    mov si, offset oddArr
    mov al, 1
    
    ODD_GEN:
        mov [si], al
        add al, 2
        inc si
        loop ODD_GEN

; Even array
                  
    mov cl, N
    mov si, offset evenArr
    mov al, 2
    
    EVEN_GEN:
        mov [si], al
        add al, 2
        inc si
        loop EVEN_GEN                  
                      
; cal ODD SUM
    
    mov cl, N
    mov si, offset oddArr
    
    ODD_SUM_LOOP:
           mov al, [si]
           mul al
           add ODD_SUM, ax
           inc si
           loop ODD_SUM_LOOP    

           
; cal EVEN SUM

    mov cl, N
    mov si, offset evenArr
    
    EVEN_SUM_LOOP:
        mov al, [si]
        mul al
        add EVEN_SUM, ax
        inc si
        loop EVEN_SUM_LOOP

; Final Storing to display
mov dx, ODD_SUM
mov bx, EVEN_SUM

mov ah, 4Ch
int 21h
          