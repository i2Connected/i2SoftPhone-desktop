#include "CoreManagerGUI.hpp"

#include "components/Components.hpp"

CoreManagerGUI::CoreManagerGUI(QObject * parent) : QObject(parent){
	auto core = CoreManager::getInstance();

	connect(core, &CoreManager::coreManagerInitialized, this, &CoreManagerGUI::coreManagerInitialized);
	connect(core, &CoreManager::chatRoomModelCreated, this, &CoreManagerGUI::chatRoomModelCreated);
	connect(core, &CoreManager::historyModelCreated, this, &CoreManagerGUI::historyModelCreated);
	connect(core, &CoreManager::recorderManagerCreated, this, &CoreManagerGUI::recorderManagerCreated);

	connect(core, &CoreManager::eventCountChanged, this, &CoreManagerGUI::eventCountChanged);
	connect(core, &CoreManager::callLogsCountChanged, this, &CoreManagerGUI::callLogsCountChanged);
}

QString CoreManagerGUI::getDownloadUrl (){
	return CoreManager::getDownloadUrl();
}

QString CoreManagerGUI::getVersion () const{
	return CoreManager::getInstance()->getVersion();
}
int CoreManagerGUI::getEventCount () const{
	return CoreManager::getInstance()->getEventCount();
}
int CoreManagerGUI::getCallLogsCount() const{
	return CoreManager::getInstance()->getCallLogsCount();
}
