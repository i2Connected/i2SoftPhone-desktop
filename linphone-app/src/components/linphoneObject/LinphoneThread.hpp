#ifndef LINPHONETHREAD_HPP
#define LINPHONETHREAD_HPP

#include <QThread>
#include <QTimer>


class LinphoneThread : public QObject{
	Q_OBJECT
public:

	class LThread : public QThread{
	public:
		LThread(QObject * parent) : QThread(parent){}
		virtual void run(){
			exec();
		}
	};
	LThread * mThread;
	LinphoneThread(QObject * parent = nullptr) : QObject(nullptr){
		mThread = new LThread(parent);
		this->moveToThread(mThread);
		connect(this, &LinphoneThread::startT, this, &LinphoneThread::startAsync, Qt::QueuedConnection);
		connect(this, &LinphoneThread::stopT, this, &LinphoneThread::stopAsync, Qt::QueuedConnection);
	}
	void start(){
		mThread->start();
	}
	void exit(){
		mThread->exit();
	}

	void objectToThread(QObject * object){
		object->moveToThread(mThread);
	}
signals:
	void startT(QTimer * timer);
	void stopT(QTimer * timer);
public slots:
	void startAsync(QTimer * timer){
		timer->moveToThread(mThread);
		timer->start();
	}
	void stopAsync(QTimer * timer){
		timer->stop();
	}
	/*
	template<class T>
	void create(T t){
		t->moveToThread(this);
	}*/
};

#endif // LINPHONETHREAD_HPP
