[Início](../README.md)

# Automatização no Visual Studio Code
Com ajuda de algumas extensões, você pode automatizar algumas tarefas repetivas
no VSCOde. Em `.vscode/tasks.json` e `.vscode/settings.json`, estão algumas
configurações para automação. Salvando os arquivos corretos, as tarefas
"Build hasm" e "Build utests" são executadas automaticamente. Pra isso funcionar
você precisa da extensão
[Trigger Task on Save](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.triggertaskonsave).

Se você não tem [Ninja](https://ninja-build.org/) instalado em seu computador,
as tarefas "Build hasm" e "Build utests" em `.vscode/task.json`
**não vão funcionar**. Para que funcione você pode mudar os comandos de build
system de `ninja` para `make` (`-j4` é o número de cores usado para fazer a
build do projeto. Use o número disponível no seu computador).

Atual:

    "command": "cd build ; ninja -j4 hasm"

Depois da mudança:

    "command": "cd build ; make -j4 hasm"

Além disso, você pode habilitar a opção "Enable autorun" para execução
automática dos testes assim que eles forem compilados.

![img](https://github.com/matepek/vscode-catch2-test-adapter/raw/HEAD/resources/Screenshot_2019-05-29.png)

Para isso funcionar, você precisa das extensões
[Test Explorer UI](https://marketplace.visualstudio.com/items?itemName=hbenl.vscode-test-explorer) e
[TestMate](https://marketplace.visualstudio.com/items?itemName=matepek.vscode-catch2-test-adapter).

