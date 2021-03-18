# https://stackoverflow.com/questions/5373714/how-to-generate-a-calling-graph-for-c-code

clang++ -S -emit-llvm src/montador.cpp -o - | 
  opt -analyze -std-link-opts -dot-callgraph

cat callgraph.dot |
  c++filt |
  sed 's,>,\\>,g; s,-\\>,->,g; s,<,\\<,g' |
  gawk '/external node/{id=$1} $1 != id' |
  dot -Tpng -ocallgraph.png