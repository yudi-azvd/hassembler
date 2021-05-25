# Hassembler
Montador para um assembly hipotético estudado durante a disciplina de Software 
Básico da Universidade de Brasília.

Por enquanto ele só monta. Não tem ligador nem simulador.

Além disso, é garantido que funciona apenas em Linux ou 
[WSL](https://docs.microsoft.com/en-us/windows/wsl/). Usuários de Windows vão 
ter que esperar um pouco. Ainda assim, são incentivados a experimentar com esse
projeto e abrir [issues](https://github.com/yudi-azvd/hassembler/issues/new).


## Dependências
Para compilar esse projeto, você vai precisar ter os seguintes programas 
instalados em seu computador:

- [CMake](https://cmake.org/download/)
- [Make](https://www.gnu.org/software/make/) 
<!-- (ou [Ninja](https://ninja-build.org/)) -->


## Como usar
Baixe esse [repositório](https://github.com/yudi-azvd/hassembler) e entre nele:

    git clone https://github.com/yudi-azvd/hassembler
    cd hassembler

Crie a pasta de build, entre nela, gere os arquivos de build e compile:

    mkdir build
    cd build
    cmake ..
    make hasm

Se tudo deu certo, o programa foi compilado e o executável resultante é o 
`hasm`. Ainda no diretório `./build`, é possível montar um arquivo de exemplo
em assembly hipotético com:

    ./hasm ../asm_files/fatorial.asm

O resultado deve ser um arquivo objeto `fatorial.obj` no mesmo diretório. O 
`hasm` usa o nome do arquivo de entrada para gerar o nome do arquivo de saída 
substituindo a extensão por `.obj`. Atualmente, os arquivos objetos sempre são criados no mesmo diretório onde o programa foi executado.

Você ainda pode copiar esse executável para qualquer lugar do seu computaddor
e usá-lo normalmente atentando-se somente aos caminhos dos arquivos usados como
argumentos para `hasm`.

**Cheque a [documentação](docs/README.md)** 
para mais informações sobre o uso e o funcionamento do Hassembler.


## Testes
Dentro de `./build`, para compilar e executar os testes:

    make utests
    ./utests

Os testes estão nos diretórios `_tests`, seguindo uma organização inspirada no 
conceito [DDD](https://en.wikipedia.org/wiki/Domain-driven_design). Os tipos dos
testes são indicados com uma sub extensão:

- Testes unitários: `.ut`
- Testes de integração: `.it`
- Testes de ponta a ponta (end-to-end): `.e2et`


## Trabalhos originais
Para os curiosos, os trabalhos originais entregues na displina de Software 
básico podem ser contemplados nesses links:

- [Trabalho 1](https://github.com/yudi-azvd/hassembler/tree/sb-trabalho-1):
montador e simulador
- [Trabalho 2](https://github.com/yudi-azvd/hassembler/tree/sb-trabalho-2):
montador adpatado para ligação e ligador (simulador é o mesmo do Trabalho 1)

[Usando o filesystem em testes](https://softwareengineering.stackexchange.com/questions/330393/reading-a-file-before-testing-a-method-it-is-an-integration-test-or-a-unit-tes).
