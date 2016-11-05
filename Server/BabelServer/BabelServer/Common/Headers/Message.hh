#ifndef MESSAGE_HH_
# define MESSAGE_HH_

# include <cstdint>
# include <string>
# include "Mallocator.hh"

class Message
{
private:
	struct Msg			*_message;

public:
	Message(const int cmd, const std::string &message);
	~Message() {};

	Msg					*getMessage() const;
};

#endif /* !MESSAGE_HH_ */
