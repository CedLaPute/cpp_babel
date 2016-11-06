# include "../Headers/Mallocator.hh"

Mallocator::Mallocator() {}

Msg		*Mallocator::MallocateMessage(Msg *message, int size, const std::string &dataString)
{
	int i = 0;
	char *data = (char *)dataString.c_str();
	
	if ((message = (Msg *)malloc(sizeof(struct Msg) + size)) == NULL)
	{
		return (NULL);
	}
	message->header.size = size;
	while (i < size)
	{
		message->data[i] = data[i];
		i++;
	}
	message->data[i++] = '\0';
	printf("Message header size : %d\n", message->header.size);
	printf("Message data : %s\n", message->data);
	return (message);
}