#define BLOCK_SIZE 4096
#define FREE_SIZE 4092

class Block {
  // 4 bytes
  unsigned int assignedBytes;
  char rawData[FREE_SIZE];
}