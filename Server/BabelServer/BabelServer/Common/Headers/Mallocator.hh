#ifndef MALLOCATOR_HH_
# define MALLOCATOR_HH_

# include <string>
# include <stdio.h>
# include <stdlib.h>

struct MsgHeader
{
	uint8_t		cmd;
	uint32_t	size;
};

struct Msg
{
	struct MsgHeader	header;
	uint8_t				data[1];
};

class Mallocator
{
private:

public:
	Mallocator();
	~Mallocator() {};

	Msg	*MallocateMessage(Msg *message, int size, const std::string &data);
};

#endif /* !MALLOCATOR_HH_ */
