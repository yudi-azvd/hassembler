# Aleatórios e Curiosidades
Conhecimentos aleatórios e curiosidades sobre esse projeto.


## Origem do Nome
<b>H</b>ypothetical <b>Assembler</b> => <b> Hassembler</b>.


## Trabalhos Originais
Para os impacientes e curiosos, os trabalhos originais entregues na displina de
Software Básico podem ser consultados nesses links:

- [Trabalho 1](https://github.com/yudi-azvd/hassembler/tree/sb-trabalho-1):
montador e simulador
- [Trabalho 2](https://github.com/yudi-azvd/hassembler/tree/sb-trabalho-2):
montador adpatado para ligação e ligador (simulador é o mesmo do Trabalho 1)

Em cada um deles existem instruções para compilação e uso do projeto.


## Automatização no Visual Studio Code
Dê uma olhada [aqui](docs/vscode-automation.md) para automatizar os processos de
build no VSCode.

---

[Usando o filesystem em testes](https://softwareengineering.stackexchange.com/questions/330393/reading-a-file-before-testing-a-method-it-is-an-integration-test-or-a-unit-tes).

## Renomear múlitplos arquivos
[post no StackOverflow](https://stackoverflow.com/questions/15290186/find-a-pattern-in-files-and-rename-them):

`find src/** -name '*.test.cpp' -exec bash -c 'mv $0 ${0/.test./.ut.}' {} \;`

