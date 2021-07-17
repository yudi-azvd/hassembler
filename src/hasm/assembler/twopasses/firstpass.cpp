#include "firstpass.h"


FirstPass::FirstPass(AssemblyData* ad) {
  if (ad == nullptr)
    throw std::runtime_error("assemblyData cannot be null");
  assemblyData = ad;
  parser.setAssemblyData(assemblyData);
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
  parser.setFilename(src->getInputfilename());

  for (auto ln : source->getLines()) {
    runOn(ln);
    ++lineCounter;
  }
}


void FirstPass::runOn(Line line) {
  tokens = scanner.parseTokens(line.getContent());
  if (tokens.empty()) {
    return;
  }

  /*
  tokens = scanner.run(line.getContent());
  if (tokens.empty()) return;
  parser.run(tokens);
  addErrors(scanner.getErrorMessages());
  addErrors(parser.getErrorMessages());

  addScannerAndParserErrors(); { precisa desse método?
    addErrors(scanner.getErrorMessages());
    addErrors(parser.getErrorMessages());
  }
  */

  bool symbolsTableHasLabel, usageTableHasLabel;
  parser.setLineCounter(lineCounter);
  parser.runOn(tokens);
  auto label = toLower(parser.getLabel());
  auto operation = toLower(parser.getOperation()); // instrução ou diretiva
  auto operand1 = toLower(parser.getOperand1());
  auto operand2 = toLower(parser.getOperand2());

  if (!label.empty()) {
    symbolsTableHasLabel = source->getSymbolsTable()->has(label);
    usageTableHasLabel = source->getUsageTable()->has(label);

    if (!symbolsTableHasLabel && !usageTableHasLabel) {
      source->getUsageTable()->add(label, positionCounter);
      source->getSymbolsTable()->add(label, positionCounter);
      positionCounter++;
    }
    else {
      assemblyData->addError(
        source->getInputfilename(),
        lineCounter, "symbol " + label + " redefined");
    }
  }

  /*
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