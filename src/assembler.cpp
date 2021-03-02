#include <iostream>

/*

contador_posição = 0
contador_linha = 1

Enquanto arquivo fonte não chegou ao fim, faça:
  Obtém uma linha do fonte
  Separa os elementos da linha:
    rótulo, operação, operandos, comentários
    Ignora os comentários
  
  Se existe rótulo:
    Procura rótulo na TS (Tabela de Símbolos)
    
    Se achou: 
      Erro => símbolo redefinido
    Senão: 
      Insere rótulo e contador_posição na TS

  Procura operação na tabela de instruções
  
  Se achou:
    contador_posição = contador_posição + tamanho da instrução
  Senão:
    Procura operação na tabela de diretivas
    Se achou:
      chama subrotina que executa a diretiva
      contador_posição = valor retornado pela subrotina
    Senão: 
      Erro, operação não identificada

  contador_linha = contador_linha + 1 ? aqui mesmo?
*/

int main() {
  std::cout << "hello world" << std::endl;

  /**
   * abre arquivo
   * le linha por linha
   *  primeira passagem:
   *    
   */

  return 0;
}