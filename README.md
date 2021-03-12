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
Para compilar o projeto é necessário ter o [Make](https://www.gnu.org/software/make/) instalado em seu computador.
Foi usado **g++ 7.5.0** com **Ubuntu 18.04**.

Para compilar o `montador`:
<!-- e o `simulador`: -->

```sh
make

# execute com:
./montador <caminho-relativo-do-seu-arquivo.asm>

# exemplo
./montador ./asm_files/fatorial.asm # "./" é necessário para o 
                                    # funcionamento do programa
```
Se tudo deu certo executando o comando do exemplo anterior,
 o arquivo `fatorial.obj` está no diretório raíz do projeto.

<!-- ./simulador ./caminho/para/arquivo/obj -->

<!-- 
Para compilar um dos dois individualmente:

```sh
make assembler
# ou
make simulator
``` -->

---

### Testes
Pra quem tiver interesse, para ver os testes, eles também podem ser 
compilados com:

```sh
make utests
```
