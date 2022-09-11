#ifndef CORE_H
#define CORE_H

#include <linphone++/core.hh>
#include "components/linphoneObject/LinphoneObject.h"

#include <QThread>

class QTimer;

class Core : public LinphoneObject<std::shared_ptr<linphone::Core>>{
public:
	Core(QObject * parent = nullptr);

	void startIterate();
	void stopIterate();
	void iterate ();
private:
	QTimer * mCbsTimer;
};

#endif // CORE_H
