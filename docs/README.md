# Documentação
_Essa documentação ainda está desenvolvimento_.


## Conjunto de instruções da máquina hipotética
| Mnemônico | Opcode | Tamanho<br>(palavras) | Ação                     |
|-----------|--------|-----------------------|--------------------------|
| ADD       | 01     | 2                     | `ACC = ACC + mem[OP]`      |
| SUB       | 02     | 2                     | `ACC = ACC - mem[OP]`      |
| MUL       | 03     | 2                     | `ACC = ACC * mem[OP]`      |
| DIV       | 04     | 2                     | `ACC = ACC / mem[OP]`      |
| JMP       | 05     | 2                     | `PC = OP            `      |
| JMPN      | 06     | 2                     | `se ACC < 0 então PC = OP `|
| JMPP      | 07     | 2                     | `se ACC > 0 então PC = OP `|
| JMPZ      | 08     | 2                     | `se ACC = 0 então PC = OP `|
| COPY      | 09     | 3                     | `mem[OP2] = mem[OP1]`      |
| LOAD      | 10     | 2                     | `ACC = mem[OP]      `      |
| STORE     | 11     | 2                     | `mem[OP] = ACC      `      |
| INPUT     | 12     | 2                     | `mem[OP] = entrada  `      |
| OUTPUT    | 13     | 2                     | `saída = mem[OP]    `      |
| STOP      | 14     | 1                     | Suspende a execução      |

<small> Tabela feita com <a href="https://www.tablesgenerator.com/markdown_tables#"> Tables Generator</a></small>.


## Exemplo de programa
Programa em assembly hipotético que calcula a área de um triângulo tirado de
`asm_files/area_triangulo.asm`:

```asm
section DATA
B: SPACE
H: SPACE
DOIS: CONST 2
R: SPACE

section TEXT
INPUT B
INPUT H
LOAD B
MUL H
DIV DOIS
STORE R
OUTPUT R
STOP
```

Se `hasm` e `area_triangulo.asm` estiverem no mesmo diretório, para montar
basta executar:

    ./hasm area_triangulo.asm

O resultado deve ser o arquivo objeto `area_triangulo.obj` com o seguinte
conteúdo:

    H fatorial
    H 24
    R 010101010101010101010000
    T 12 22 10 22 2 23 8 18 11 21 3 22 11 22 10 21 5 4 13 22 14 0 0 1

`H fatorial`: cabeçalho (header) com o nome do programa.

`H 24`: cabeçalho (header) com o tamanho do programa em palavras.

`R 0101... `: informação de relocação (útil para o ligador).

`T 12 10 22... `: o programa em si, com seção de texto e seção de dados.

Essa formatação é apenas para _imitar_ a formatação de um arquivo objeto
tradicional. Por isso o arquivo objeto resultante ainda é um arquivo texto que
pode ser lido por qualquer editor de texto e compreendido por humanos.


## Simulação
_Essa parte ainda vai ser melhorada_. Se você quiser simular o programa
anterior, você pode usar o simulador do
[Trabalho 2](https://github.com/yudi-azvd/hassembler/tree/sb-trabalho-2) e
compilá-lo seguindo as instruções do
[README.md](https://github.com/yudi-azvd/hassembler/tree/sb-trabalho-2#usar-e-executar). Depois disso, copie o `simulador` para o
diretório do `fatorial.obj`.

Antes de simular, faça uma pequena correção em `fatorial.obj`: remova tudo o que
vem antes do primeiro número que vem depois do `T`. Esse processo pode ser
realizado para outros `.asm` únicos que forem montados. O resultado do arquivo
`fatorial.obj` deve ser isso:

    12 22 10 22 2 23 8 18 11 21 3 22 11 22 10 21 5 4 13 22 14 0 0 1

Simule com:

    ./simulador fatorial.obj

Futuramente não será necessário realizar esse ajuste manualmente. O próprio
`hasm` fará isso.


## "Diagrama" de classes
[Rascunho de um diagrama de classes](https://app.diagrams.net/#G16oGpIRZghYMjgEKRxyjuXornyU8yxIrf)
para o Hypothetical Assembler (Hassembler).
Visualize
[aqui](https://drive.google.com/file/d/16oGpIRZghYMjgEKRxyjuXornyU8yxIrf/view?usp=sharing).
