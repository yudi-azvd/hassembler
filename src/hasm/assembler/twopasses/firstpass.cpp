#include "firstpass.h"


FirstPass::FirstPass(AssemblyData* ad) {
  if (ad == nullptr)
    throw std::runtime_error("assemblyData cannot be null");
  assemblyData = ad;
}


void FirstPass::run() {
  for (auto src : assemblyData->getSources()) {
    runOn(src);
  }
}


void FirstPass::runOn(Source* src) {
  source = src;
  lineCounter = 1;
  positionCounter = 0;
  textSectionSize = 0;
  dataSectionSize = 0;

  for (auto ln : source->getLines()) {
    runOn(ln);
    ++lineCounter;
  }
}


void FirstPass::runOn(Line line) {
  // scanner.setAssemblyData(assemblyData);
  // scanner.setSource(source);
  tokens = Scanner::parseTokens(line.getContent());
  // parser.setAssemblyData(assemblyData);
  // parser.setSource(source);
  if (tokens.empty()) {
    return;
  }
  /*
  ### label, operation, operand1 e 2 tudo lower cased
  parser.runOn(tokens); // throws
  label = parser.getLabel()
  operation = parser.getOperation() // instrução ou diretiva
  operand1 = parser.getOperand1()
  operand2 = parser.getOperand2()

  if (!label.empty()) {
    labelFoundInSymbolsTable = symbolsTable.find(label);
    labelFoundInUsageTable = usageTable.find(label);

    if (!labelFoundInSymbolsTable && !labelFoundInUsageTable) {
      usageTable.add(label);
    }
    else {
      add? AssemblyError(source->getFilename(),
        lineCounter, "symbol " + label + " redefined");
    }
  }

  labelIsAloneInLine = !label.empty() &&
    operation.empty() && operand1.empty() && operand2.empty();
  if (labelIsAloneInLine) {
    // talvez isso fique dentro de Parser
    labelSavedForLater = label;
    continue;
  }

  operationIsInstruction = opcodeTable.has(operation);
  operationIsDirective = directiveTable.has(operation);
  if (operationIsInstruction) {
    int instructionSize = opcodeTable.getSizeOf(operation);
    positionCounter += instructionSize;
    textSectionSize += instructionSize;
  }
  else if (operationIsDirective) {
    directiveFunctionPointer = directiveTable.get(operation);
    positionCounter = (*directiveFunctionPointer)(positionCounter, operand1, operand2);

  }
  else {
    add? AssemblyError(source->getFilename(), lineCounter,
      "operation '" + operation + "' not identified);
  }
  */
}
