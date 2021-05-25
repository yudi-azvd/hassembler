#ifndef DEFINITIONSTABLE_H_INCLUDED
#define DEFINITIONSTABLE_H_INCLUDED

#include <map>
#include <iostream>

class DefinitionsTable {
public:
  DefinitionsTable() {}

  ~DefinitionsTable() {}

  void add(std::string name, int position);

  // Ideia maluca: fazer esse método retornar um pair<bool, int>
  // Se a tabela tem o nome => true e o número é a posição
  // Se a tabela não tem o nome => false e p número é zero.
  bool has(std::string name);

  int getPositionOf(std::string name);

  std::map<std::string, int>& getTable();

  friend std::ostream& operator<<(std::ostream& os, const DefinitionsTable& dt);
  
private:
  std::map<std::string, int> table;  
};

#endif // DEFINITIONSTABLE_H_INCLUDED