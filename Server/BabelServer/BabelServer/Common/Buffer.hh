#ifndef BUFFER_HH_
# define BUFFER_HH_

# include <cstdint>

# define MAGIC 0x42133708

typedef struct
{
  unsigned int		magic;
  unsigned int		size;
  unsigned char		cmd;
  unsigned char		data[1];
}			Buff;

class	Buffer
{
private:
public:
  Buffer();
  ~Buffer();

  static void		getCmd(char *, int const, int const, char const *);
  static Buff		*getValue(char *);
};

#endif /* !BUFFER_HH_ */
