# Montador
O ponto de entrada do montador está em `montador.cpp`. A função `main`
invoca os métodos de um objeto `Assembler`. De maneira geral, a chamada dos 
métodos acontece assim:

```cpp
assemble()
└─ getInputFileContent(_filename);
└─ runZerothPass();
└─ runFirstPass();
└─ runSecondPass();
└─ generateOutput();
```

*`getInputFileContent`*: abre o arquivo `.asm` e carrega o conteúdo em um 
vetor de strings

*`runZerothPass`*: determina a ordem de section data e text.

*`runFirstPass`*: adiciona erros no vetor de erros se existirem e monta a tabela 
de símbolos segundo o algoritmo dos slides.

*`runSecondPass`*: adiciona erros no vetor de erros se existirem e gera os números que vão para o código objeto em um vetor `_objectCode`.
 
*`generateOutput`*: se o vetor de erros estiver vazio, o números em `_objectCode` 
são passados para um arquivo text `.obj` onde o binário foi executado. Se vetor de 
erros não estiver vazio, `.obj` não é gerado e os erros são impressos na tela.

> Observação: o montador também faz um ajuste na tabela de símbolos e
> no código objeto caso section data venha antes de section text no `.asm`.


# Simulador
O ponto de entrada do simulador está em `simulador.cpp`. A função `main`
invoca métodos de um objeto `Simulator`. De maneira geral, o simulador funciona 
em uma grande sequência de `if else if`, verificando qual é o opcode lido e 
executando a rotina necessária.
