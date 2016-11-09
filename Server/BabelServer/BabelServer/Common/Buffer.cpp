#include <Buffer.hh>
#include <iostream>
#include <cstring>

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

void		Buffer::getCmd(char *str, int const size, int const cmd, char const *data)
{
  Buff		*b = new Buff();

  b->magic = MAGIC;
  b->size = size;
  b->cmd = cmd;
  std::strcpy((char *)(b->data), data);

  std::memcpy(str, b, sizeof(Buff) + size);
}

Buff		*Buffer::getValue(char *str)
{
  Buff		*b = new Buff();
  
  b = reinterpret_cast<Buff *>(str);
  return b;
}
