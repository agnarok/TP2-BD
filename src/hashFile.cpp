#include "hashFile.h"
#include <cstdio>
#include <iostream>

HashFile::HashFile() {
  file = fopen(SMALL_HASH_FILE_PATH, "w+");
  fseek(file, 0, SEEK_SET);
  Block placeHolder;
  try {
    for (int i = 0; i < LARGE_PRIME*2; i++) {
      cout << "escrevendo bloco " << i << endl;  
      fwrite(&placeHolder, BLOCK_SIZE, 1, file);
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}

// -1 because .csv starts with 1
int HashFile::calculateHash(int id) { return (id % LARGE_PRIME); }

void HashFile::commitInsertion(Block *outputBlock) {
  fwrite(outputBlock, BLOCK_SIZE, 1, this->file);
}

/**
 * Each block has 4096 bytes. If each bucket has 2 blocks, then each bucket
 * occupies 8192 bytes. That's the offset jump.
 */
bool HashFile::insertItem(Line &line) {
  int inputBucket = calculateHash(line.id);
  cout << inputBucket << endl;
  int offset = inputBucket * BUCKET_SIZE;
  Block outputBlock;
  fseek(this->file, offset, SEEK_SET);
  if (!fread(&outputBlock, sizeof(Block), 1, this->file)) {
    return false;
  }
  fseek(this->file, offset, SEEK_SET);
  if (outputBlock.insertItem(line)) {
    commitInsertion(&outputBlock);
    return true;
  } else {
    offset += BLOCK_SIZE;
    fseek(this->file, offset, SEEK_SET);
    if(!fread(&outputBlock, sizeof(Block), 1, this->file)) {
      return false;
    }
    if (outputBlock.insertItem(line)) {
      offset -= BLOCK_SIZE;
      fseek(this->file, offset, SEEK_SET);
      cout << "ME CHUPA " << ftell(this->file) << endl;
      commitInsertion(&outputBlock);
      return true;
    };
  }
  return false;
}

Line *HashFile::getLineFromBlock(int lineId) {
  int outputBucket = calculateHash(lineId);
  int offset = outputBucket * BUCKET_SIZE;
  Block outputBlock;
  Line *outputLine;
  fseek(this->file, offset, SEEK_SET);
  fread(&outputBlock, BLOCK_SIZE, 1, this->file);
  cout << " PRIMEIRO BLOCO " << ftell(this->file) << endl;
  outputLine = outputBlock.getItem(lineId);
  if (outputLine != nullptr) {
    return outputLine;
  }
  fread(&outputBlock, BLOCK_SIZE, 1, this->file);
  cout << "TAMANHO SEGUNDO BLOCO: " << outputBlock.usedBytes << endl;
  cout << " SEGUNDO BLOCO " << ftell(this->file) << endl;  
  outputLine = outputBlock.getItem(lineId);
  if (outputLine != nullptr) {
    cout << "deu bom " << endl;
    return outputLine;
  }
  return nullptr;
}

void HashFile::closeFile() { fclose(this->file); }