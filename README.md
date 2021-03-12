# Software Básico: Montador e Simulador
Montador simluador desenvolvidos durante a disciplina de 
Software Básico da Universidade de Brasília.

## Baixar
Baixe esse repositório por esse [link](https://github.com/yudi-azvd/sb-assembler-and-simulator) clicando no botão verde. Ou baixe pela linha de 
comando.

```sh
git clone https://github.com/yudi-azvd/sb-assembler-and-simulator
cd sb-assembler-and-simulator
```

Abra o terminal e navegue até o repositório baixado.

```sh
cd sb-assembler-and-simulator
```

## Usar e executar
Para compilar o projeto é necessário ter o Make instalado em seu computador.
Foi usado **g++ 7.5.0** com **Ubuntu 18.04**.

Para compilar o `montador`:
<!-- e o `simulador`: -->

```sh
make

# execute com:
./montador ./asm_files/bin1.asm # AINDA NÃO FAZ NADA
```
<!-- ./simulador ./caminho/para/arquivo/obj -->

<!-- 
Para compilar um dos dois individualmente:

```sh
make assembler
# ou
make simulator
``` -->

---

### Testes unitários
Pra quem tiver interesse, para ver os testes unitários, eles também podem ser 
compilados com:

```sh
make utests
```
