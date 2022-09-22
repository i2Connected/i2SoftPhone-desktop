#ifndef COREMANAGERGUI_H
#define COREMANAGERGUI_H

#include <QObject>

class ChatRoomModel;
class HistoryModel;
class RecorderManager;

class CoreManagerGUI : public QObject{
	Q_OBJECT
	Q_PROPERTY(QString version READ getVersion CONSTANT)
	Q_PROPERTY(QString downloadUrl READ getDownloadUrl CONSTANT)
	Q_PROPERTY(int eventCount READ getEventCount NOTIFY eventCountChanged)
	Q_PROPERTY(int callLogsCount READ getCallLogsCount NOTIFY callLogsCountChanged)
public:
	CoreManagerGUI(QObject * parent = nullptr);

	QString getVersion () const;
	int getEventCount () const;
	int getCallLogsCount() const;
	static QString getDownloadUrl ();
signals:
	void coreManagerInitialized ();

	void chatRoomModelCreated (const QSharedPointer<ChatRoomModel> &chatRoomModel);
	void historyModelCreated (HistoryModel *historyModel);
	void recorderManagerCreated(RecorderManager *recorderModel);

	void logsUploaded (const QString &url);
	void eventCountChanged ();
	void callLogsCountChanged();

};

#endif // COREMANAGERGUI_H
