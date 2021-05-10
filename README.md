# Software Básico: Montador e Ligador
Montador e ligador desenvolvidos por Yudi Yamane (16/0149410) para o trabalho 2
da disciplina de Software Básico.

## Funcionamento
Para entender melhor como eles funcionam leia sobre isso [aqui](./explicação.md).

## Baixar
Baixe esse repositório por esse [link](https://github.com/yudi-azvd/hassembler) 
clicando no botão verde. Ou baixe pela linha de comando e entre no repositório 
baixado.

    git clone https://github.com/yudi-azvd/hassembler

    cd hassembler


## Usar e executar
Para compilar o projeto é necessário ter o 
[Make](https://www.gnu.org/software/make/) 
instalado em seu computador. Foi usado **g++ 7.5.0** com **Ubuntu 18.04**.

Para compilar o **montador**, o **ligador** e o **simulador**:

    make

Para usar o programas:

    ./montador asm_files/main.asm asm_files/mul_div.asm asm_files/soma_sub.asm
    
    ./ligador main.obj mul_div.obj soma_sub.obj

    ./simulador a.out


Para compilar qualquer um dos três individualmente:

    make assembler

    make linker

    make simulator

Para limpar o diretório:

    make clean

---

### Testes
Pra quem tiver interesse e quiser ver os testes, eles também podem ser 
compilados com:

    make utests
