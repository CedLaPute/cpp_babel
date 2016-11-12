#ifndef NETWORK_HH_
# define NETWORK_HH_

#include <QThread>

class Network : public QThread
{
  Q_OBJECT
public:
  Network();
protected:
  void		run();
signals:
  void		sig(QString const &);
};

#endif /* !NETWORK_HH_ */
