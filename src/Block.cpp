#include "Block.h"
#include "definitions.h"


bool Block::insertItem(const Line line) {
  if (this->usedBytes == FREE_SIZE) {
    return false;
  }
  unsigned int offset;
  offset = this->usedBytes;
  std::memcpy(&(this->rawData[offset]), &line, sizeof(line));
  this->usedBytes += sizeof(line);
  return true;
}

// Line Block::getItem(unsigned int id) {
//   unsigned int cursor = 0;
//   Line *line;
//   while(cursor < this->usedBytes) {
//     line = reinterpret_cast<Line *>(&this->rawData[cursor]);
//   }
// }