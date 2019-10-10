#include "Line.h"
#include "definitions.h"

class Block {
  // 4 bytes
  char rawData[FREE_SIZE];
 public:
  unsigned int usedBytes;
  Block();
  bool insertItem(const Line);
  Line* getItem(unsigned int id);
};
