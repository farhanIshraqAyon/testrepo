org 100h  

main proc
                
mov AH, 1
INT 21h 
    
mov bl, al

and bl, 1

cmp bl, 1
jnz Label_Even
 
    ; go to a new line with carriage return
    MOV AH, 2
    MOV DL, 0DH
    INT 21h
    MOV DL, 0AH
    INT 21h
    
    ; Display Character
    mov AH, 2
    mov DL, 'O'
    int 21h 
    
    MOV AH, 4CH
    INT 21H 
    
Label_Even:
    ; go to a new line with carriage return
    MOV AH, 2
    MOV DL, 0DH
    INT 21h
    MOV DL, 0AH
    INT 21h  
    
    ; Display character
    mov AH, 2
    mov DL, 'E'
    int 21h 

main endp
ret