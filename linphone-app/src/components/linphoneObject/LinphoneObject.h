#ifndef LINPHONEOBJECT_H
#define LINPHONEOBJECT_H

#include <QObject>
#include <QThread>
#include <QDebug>


template<class T>
class LinphoneObject : public QObject{
public:
	LinphoneObject(QObject * parent = nullptr) : QObject(parent){}

	bool isValid() const{
		bool ok = true;
		if(!gLinphoneThread)
			gLinphoneThread = QThread::currentThread();
		else if(gLinphoneThread != QThread::currentThread()){
			ok = false;
			qCritical() << "Current Linphone Object is being used in the wrong thread" << this;
		}
		return ok;
	}
private:
	T mLinphoneObject;

	static QThread * gLinphoneThread;
};
template<class T>
QThread *LinphoneObject<T>::gLinphoneThread = nullptr;
#endif // LINPHONEOBJECT_H
