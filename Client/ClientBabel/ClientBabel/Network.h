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

 private slots:
   void		newName(QString const &);
   void		sndCall(QString const &);
   void		acceptCall();
   void		refuseCall();
   void		endCall();
   
 signals:
   void		nameTaken();
   void		sndFailed();
   void		nameWrong();
   void		unknownName();
   void		callFailed();
   void		connectFailed();
};

#endif /* !NETWORK_H_ */
