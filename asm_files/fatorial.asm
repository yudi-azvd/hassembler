        INPUT N
        LOAD N
FAT:    SUB ONE
        JNPZ FIM
        STORE AUX
        MULT N
        STORE N
        LOAD AUX
        JNP FAT
FIM:    OUTPUT N
        STOP
AUX:    SPACE
N:      SPACE
ONE:    CONST 1