#include "hashFile.h"
#include <cstdio>
#include <iostream>

HashFile::HashFile(bool createFile = true) {
  if (createFile) {
    file = fopen(SMALL_HASH_FILE_PATH, "w+");
    fseek(file, 0, SEEK_SET);
    Block placeHolder;
    try {
      for (int i = 0; i < LARGE_PRIME * 2; i++) {
        fwrite(&placeHolder, BLOCK_SIZE, 1, file);
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  } else {
    file = fopen(SMALL_HASH_FILE_PATH, "r");
    fseek(file, 0, SEEK_SET);
  }
}

// -1 because .csv starts with 1
int HashFile::calculateHash(int id) { return (id % LARGE_PRIME); }

int HashFile::commitInsertion(Block *outputBlock) {
  int res = fwrite(outputBlock, BLOCK_SIZE, 1, this->file);
  return res;
}

/**
 * Each block has 4096 bytes. If each bucket has 2 blocks, then each bucket
 * occupies 8192 bytes. That's the offset jump.
 */
bool HashFile::insertItem(Line &line) {
  int inputBucket = calculateHash(line.id);
  unsigned long long int offset = inputBucket * ((unsigned long long int) BUCKET_SIZE);
  Block outputBlock;
  fseek(this->file, offset, SEEK_SET);
  if (!fread(&outputBlock, sizeof(Block), 1, this->file)) {
    return false;
  }
  fseek(this->file, offset, SEEK_SET);
  if (outputBlock.insertItem(line)) {
    commitInsertion(&outputBlock);
    if (line.id == 500000) {
      fseek(this->file, offset, SEEK_SET);
      cout << "tell" << ftell(this->file) << endl;
    }
    return true;
  } else {
    offset += BLOCK_SIZE;
    fseek(this->file, offset, SEEK_SET);
    if (!fread(&outputBlock, sizeof(Block), 1, this->file)) {
      return false;
    }
    if (outputBlock.insertItem(line)) {
      fseek(this->file, offset, SEEK_SET);
      commitInsertion(&outputBlock);
      int t = commitInsertion(&outputBlock);
      // cout << "offset: " << offset << endl;
      // cout << "escrevi no outro: " << line.id << endl;

      return true;
    };
  }
  return false;
}

Line *HashFile::getLineFromBlock(int lineId) {
  int outputBucket = calculateHash(lineId);
  unsigned long long int offset = outputBucket * ((unsigned long long int) BUCKET_SIZE);
  cout << "bloco de saida: " << offset << endl;
  Block outputBlock;
  Line *outputLine;
  fseek(this->file, offset, SEEK_SET);
  cout  << "tell: " << ftell(this->file) << endl;
  fread(&outputBlock, BLOCK_SIZE, 1, this->file);
  outputLine = outputBlock.getItem(lineId);
  cout << "used bytes : " << outputBlock.usedBytes << endl;
  if (outputLine != nullptr) {
    return outputLine;
  }
  offset += BLOCK_SIZE;
  fseek(this->file, offset, SEEK_SET);
  fread(&outputBlock, BLOCK_SIZE, 1, this->file);
  outputLine = outputBlock.getItem(lineId);
  if (outputLine != nullptr) {
    return outputLine;
  }
  return nullptr;
}

void HashFile::closeFile() { fclose(this->file); }