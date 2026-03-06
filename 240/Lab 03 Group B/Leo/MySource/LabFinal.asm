
org 100h

.data
    
    msgG db 'GCD: $'
    
    num1 db ?
    num2 db ?
    gcd db ?
    
.code  
   mov ah, 01h
   int 21h
   mov cl, al   
   sub cl, '0'
   ;mov num1, al
   
   call NEWLINE
   
   mov ah, 01h 
   int 21h
   mov bl, al
   sub bl, '0'
   ;mov num2, al
   
   call NEWLINE   
   
   cmp cl, bl
               
   mov num1, cl
   mov num2, bl            
               
   jg MAIN_LOGIC
   
   mov num2, cl
   mov num1, bl
   

   MAIN_LOGIC:
   
   mov al, num1
   mov bl, num2 
   
   call FIND_GCD_PROC   
   
   mov gcd, al
   
   mov ah, 09h
   LEA dx, msgG
   int 21h
   
   mov ah, 02h 
   mov dl, gcd 
   add dl, '0'
   int 21h   

ret


FIND_GCD_PROC PROC
    
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
    
    FIND_GCD_PROC ENDP

NEWLINE PROC
    
    mov ah, 02h
    mov dl, 0Dh
    int 21h
    
    mov dl, 0Ah
    int 21h
    
    ret
    
    NEWLINE ENDP



