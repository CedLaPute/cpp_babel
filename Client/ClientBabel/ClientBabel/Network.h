#ifndef NETWORK_H_
# define NETWORK_H_

#include <QThread>
#include <QEventLoop>
#include <QTimer>
#include <QLabel>
#include "SocketManager.hh"

class Network : public QThread
{
  Q_OBJECT
 private:
  bool		_isCalling;
public:
  Network();
  void getSignalFromSocketManager();
  
  public slots:
   void		run();

   void		newName(QString const &);
   void		sndCall(QString const &);
   void		acceptCall();
   void		refuseCall();
   void		endCall();
   
 signals:
   void   listLogin(QLabel *);
   void		nameTaken();
   void   calling(QString);
   void		sndFailed();
   void		nameWrong();
   void		unknownName();
   void		callFailed();
   void		connectFailed();
  
  private:
    SocketManager *_sm;
    QEventLoop *_loop;
    QTimer *_timer;
};

#endif /* !NETWORK_H_ */
