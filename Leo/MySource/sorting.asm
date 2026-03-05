ORG 0100H

.DATA
    N DB ?
    ARR DB 10 DUP(?) ; Array to hold up to 10 digits [6]
    
    msgN DB 'Enter value of N (1-9): $'
    msgDigits DB 0Dh, 0Ah, 'Enter digits: $'
    msgSorted DB 0Dh, 0Ah, 'Sorted digits: $'

.CODE
MAIN PROC
    MOV AX, @DATA ; Initialize data segment [1]
    MOV DS, AX
    
    ; 1. Prompt for N
    MOV AH, 09h
    LEA DX, msgN
    INT 21h ; Display prompt [7]
    
    MOV AH, 01h
    INT 21h ; Read N from keyboard [5]
    SUB AL, '0' ; Convert ASCII digit to numeric value [8]
    MOV N, AL
    XOR CH, CH ; Clear CH for loop counting [9]
    
    ; 2. Read N digits into array
    MOV AH, 09h
    LEA DX, msgDigits
    INT 21h
    
    MOV CL, N
    LEA SI, ARR ; Point SI to start of array [4]
RD_LP:
    MOV AH, 01h
    INT 21h ; Read one digit [5]
    MOV [SI], AL ; Store ASCII character directly [4]
    INC SI
    LOOP RD_LP ; Repeat N times [10]
    
    ; 3. Bubble Sort the Array
    MOV CL, N
    DEC CL ; Outer loop runs N-1 times [10]
OUTER_LP:
    PUSH CX ; Save outer loop counter [5]
    LEA SI, ARR ; Reset SI to beginning for each pass [4]
    
INNER_LP:
    MOV AL, [SI]
    CMP AL, [SI+1] ; Compare current element with next [11]
    JBE SKIP_SWAP ; If AL <= [SI+1], no swap needed [11]
    
    ; Swap elements if they are in the wrong order
    XCHG AL, [SI+1] ; Swap AX with memory [4]
    MOV [SI], AL ; Move the swapped value back to current position
    
SKIP_SWAP:
    INC SI
    LOOP INNER_LP ; Inner loop moves through the array [10]
    
    POP CX ; Restore outer loop counter [5]
    LOOP OUTER_LP
    
    ; 4. Print the sorted array
    MOV AH, 09h
    LEA DX, msgSorted
    INT 21h
    
    MOV CL, N
    LEA SI, ARR
PRT_LP:
    MOV DL, [SI] ; Load digit from array [4]
    MOV AH, 02h
    INT 21h ; Print the character in DL [5]
    INC SI
    LOOP PRT_LP
    
    ; Terminate program
    MOV AH, 4Ch
    INT 21h ; Exit to DOS [7]
MAIN ENDP
END MAIN