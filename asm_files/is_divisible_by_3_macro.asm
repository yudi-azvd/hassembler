section data
one: const 1
zero: const 0
three: const 3
n: space

section text
is_divisible_by_3:  MACRO &n
           repeat:  sub three
                    jmpp repeat
                    ENDMACRO
                    input n
                    is_divisible_by_3 n
                    load n
                    jmpn not_div
                    jmpz is_div
not_div:            output zero
                    stop
is_div:             output one
                    stop
