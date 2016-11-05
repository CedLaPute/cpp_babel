# include "../Headers/Message.hh"
# include <iostream>

Message::Message(const int cmd, const std::string &message)
{
	try
	{
		int size = message.size();

		Mallocator *m = new Mallocator();

		_message = m->MallocateMessage(_message, size, message);
		_message->header.cmd = 101;
		printf("Message header cmd : %d\n", _message->header.cmd);
	}
	catch (const std::string &err)
	{
		std::cout << err << std::endl;
	}
}

Msg			*Message::getMessage() const
{
	return _message;
}