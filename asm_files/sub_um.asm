load dez          ; 00
add neg_um        ; 02
store result      ; 04
output result     ; 06
stop              ; 07
neg_um: const -1  ; 08
dez: const 10     ; 09
result: space     ; 10