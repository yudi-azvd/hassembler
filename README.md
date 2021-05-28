# Hassembler
**Hassembler** é um montador e ligador para
o Assembly hipotético estudado durante a disciplina de Software Básico da
Universidade de Brasília. Como se trata de um montador para Assembly hipotético,
nada mais justo que considerar o montador também como hipotético:
<b>H</b>ypothetical <b>Assembler</b> ➜ <b> Hassembler</b>.


## O que o Hassembler consegue fazer atualmente:
- Montar códigos de Assembly hipotético traduzindo-os para arquivos objeto.
- Mostrar os erros de montagem indicando a respectiva linha (mas não o arquivo,
he he. Vai ser consertado).
- Suporte às diretivas `SPACE` (não funciona para vetores) e `CONST`.


### O que o Hassembler vai conseguir fazer em um futuro próximo:
- Montar e ligar, gerando o "executável" para o [simulador](docs/simulador.md).
- Mostrar erros de ligação, indicando linha e arquivo.
- Suporte às diretivas `EQU` para substituir valores e `SPACE` para alocar
vetores.
- Strings?
- E mais outras coisas se eu tiver paciência.

Se você estiver muito impaciente para montar e ligar, você pode usar o programa
em uma [versão anterior](docs/curiosidades.md#trabalhos-originais).


## Fique atento
É garantido que o Hassembler funciona (eu espero pelo menos isso) apenas em
Linux ou [WSL](https://docs.microsoft.com/en-us/windows/wsl/). Usuários de
Windows vão ter que esperar um pouco. Ainda assim, são incentivados a
experimentar com esse projeto e abrir
[issues](https://github.com/yudi-azvd/hassembler/issues/new).


## Dependências
Para compilar esse projeto, você vai precisar ter os seguintes programas
instalados em seu computador:

- g++
- [CMake](https://cmake.org/download/)
- [Make](https://www.gnu.org/software/make/)
<!-- (ou [Ninja](https://ninja-build.org/)) -->


## Como usar
Baixe esse [repositório](https://github.com/yudi-azvd/hassembler) e entre nele:

    git clone https://github.com/yudi-azvd/hassembler.git
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
substituindo a extensão por `.obj`. Atualmente, os arquivos objetos sempre são
criados no mesmo diretório onde o programa foi executado.

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
<!-- - Testes de integração: `.it`
- Testes de ponta a ponta (end-to-end): `.e2et` -->


## Aleatórios

### Automatização no Visual Studio Code
Dê uma olhada [aqui](docs/vscode-automation.md) para automatizar os processos de
build no VSCode.


### Trabalhos originais
Dê uma olhada [aqui](docs/curiosidades.md#trabalhos-originais)

[Usando o filesystem em testes](https://softwareengineering.stackexchange.com/questions/330393/reading-a-file-before-testing-a-method-it-is-an-integration-test-or-a-unit-tes).


### Coisas aleatórias que eu aprendi
- [Renomear múltiplos arquivos](https://stackoverflow.com/questions/15290186/find-a-pattern-in-files-and-rename-them):
`find src/** -name '*.test.cpp' -exec bash -c 'mv $0 ${0/.test./.ut.}' {} \;`
