#ifndef NETWORK_H_
# define NETWORK_H_

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

#endif /* !NETWORK_H_ */
