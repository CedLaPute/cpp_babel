#include "Buffer.hh"
#include <iostream>
#include <cstring>

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

void Buffer::getCmd(char **str, int const size, int const cmd, char const *data)
{
  Buff *b;
  *str = new char[sizeof(Buff) + size];
  b = reinterpret_cast<Buff *>(*str);

  b->magic = MAGIC;
  b->size = size;
  b->cmd = cmd;
  std::strcpy((char *) (b->data), data);
  std::cout << (int)b->cmd << " " << b->data << std::endl;
}

Buff *Buffer::getValue(char *str)
{
  Buff *b;

  b = reinterpret_cast<Buff *>(str);
  return b;
}
