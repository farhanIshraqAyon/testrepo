
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

.data
msg1 db "Enter first digit $"
msg2 db 0Dh, 0Ah, "Enter second digit $"
msgG db 0Dh, 0Ah, "GCD:  $"
msgL db 0Dh, 0Ah, "LCM: $"

num1 db ?
num2 db ?
gcd db ?
lcm db ?

.code
main proc
  mov ax, @DATA
  mov ds, ax
  
  LEA dx, msg1
  mov ah, 09h
  int 21h
  
  mov ah, 01h
  int 21h
  sub al, 30h
  mov num1, al  
              
  
  LEA dx, msg2
  mov ah, 09h
  int 21h
  
  mov ah, 01h
  int 21h
  sub al, 30h
  mov num2, al
  
  
  mov al, num1
  mov bl, num2
  call FIND_GCD
  mov gcd, al
  
  mov al, num1
  mov bl, num2
  call FIND_LCM
  mov lcm, al
  
  
  LEA dx, msgG
  mov ah, 09h
  int 21h
  
  mov al, gcd
  add al, 30h
  mov dl, al
  mov ah, 02h
  int 21h
              
  
  LEA dx, msgL
  mov ah, 09h
  int 21h
  
  mov al, lcm
  add al, 30h
  mov dl, al
  mov ah, 02h
  int 21h
  
  
  
  
  mov ah, 4ch
  int 21h
main endp


FIND_GCD proc
    
    GCD_LOOP:
        cmp bl, 0
        je GCD_DONE
        mov ah, 0
        div bl
        mov al, bl
        mov bl, ah
        jmp GCD_LOOP  
    GCD_DONE:
        ret    
FIND_GCD endp

   
FIND_LCM proc
    
    
    mul bl   

    mov dl, gcd     
    div dl               

ret 
FIND_LCM endp

ret




