org 0100h

.data

test_string db 'Hello, I am Monazir', '$'
len equ ($ - test_string)

input_prompt db 'Input: ', '$'
input db ? ;input stores the character
count db 0 ;counts the frequency 

output_format db 'Output: ', '$'

.code

mov ah, 9
LEA dx, test_string
int 21h

; go to a new line with carriage return
MOV AH, 2
MOV DL, 0DH
INT 21h
MOV DL, 0AH
INT 21h
             
             
;input prompt
mov ah, 9
LEA dx, input_prompt
int 21h


;input      
mov ah, 1
int 21h 
mov input, al     
        
; go to a new line with carriage return
MOV AH, 2
MOV DL, 0DH
INT 21h
MOV DL, 0AH
INT 21h

       
;Processing Starts from here
     
mov si, offset test_string ; pointer to string
mov cx, len  ; cx = no. of characters

next_char:
    mov al, [si]  ; load char
     
    cmp al, input
    
    jne not_match  ; not equal so, skip increment
    
    inc count
    
    not_match:
    inc si        ; next byte
    loop next_char

; Output
mov ah, 9
LEA dx, output_format
int 21h

mov al, count  ; Numeric value of count

; Converting count to ascii before print
add al, '0'    
mov dl, al
mov ah, 2
int 21h          