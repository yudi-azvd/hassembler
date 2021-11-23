; Apenas para N > 0
section data
AUX:    SPACE          ; 21
N:      SPACE          ; 22
ONE:    
  CONST 1        ; 23
section text
        INPUT N        ; 00
        LOAD N         ; 02
FAT:   
 SUB ONE        ; 04
        JMPZ FIM       ; 06
        STORE AUX      ; 08
        MUL N          ; 10
        STORE N        ; 12
        LOAD AUX       ; 14
        JMP FAT        ; 16
FIM:
    OUTPUT N       ; 18
        STOP           ; 20