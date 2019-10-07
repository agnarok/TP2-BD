#include "Line.h"

#define BLOCK_SIZE 4096
#define FREE_SIZE 4092

class Block {
  // 4 bytes
  unsigned int usedBytes;
  char rawData[FREE_SIZE];
 public:
  bool insertItem(const Line);
  Line* getItem(unsigned int id);
};
