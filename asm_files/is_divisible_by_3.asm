section data
one: const 1
zero: const 0
three: const 3
n: space

section text
input n
load n

repeat: 
  sub three
  jmpp repeat
  jmpn not_divisible_by_3
  jmpz is_divisible_by_3
not_divisible_by_3: 
  output zero
  stop
is_divisible_by_3: 
  output one
  stop
