#include "Block.h"
#include "definitions.h"
// max number of lines per block.
#define MAX_OCCUPIED 3072

bool Block::insertItem(const Line line) {
  if (this->usedBytes >= MAX_OCCUPIED) {
    return false;
  }
  unsigned int offset;
  offset = this->usedBytes;
  std::memcpy(&(this->rawData[offset]), &line, sizeof(line));
  this->usedBytes += sizeof(line);
  return true;
}

// scans an entire block sequentially untill it finds the required line
Line* Block::getItem(unsigned int id) {
  unsigned int cursor = 0;
  Line *line;
  while(cursor < this->usedBytes) {
    line = reinterpret_cast<Line *>(&this->rawData[cursor]);
    if(line->id == id) {
      return line;
    }
    cursor += sizeof(Line);
  }
  return nullptr;
}