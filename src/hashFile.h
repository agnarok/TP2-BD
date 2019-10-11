#include <cstring>
#include <iostream>
#include "definitions.h"
#include "Block.h"

using namespace std;

// A funcao hash encontra o bucket que um dado registro está. O número do bucket
// pode ser multiplicado por um offset (bytes) para encontrar o inicio do
// bucket.
class HashFile {
  FILE* file;
 public:
  HashFile();
  void closeFile();
  Line* getLineFromBlock(int lineId);
  int calculateHash(int id);
  bool insertItem(Line& line);
  void commitInsertion(Block *outputBlock);
};