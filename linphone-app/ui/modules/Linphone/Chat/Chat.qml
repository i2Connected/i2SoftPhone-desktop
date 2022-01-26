import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Common 1.0
import Linphone 1.0
import Linphone.Styles 1.0
import Utils 1.0
import UtilsCpp 1.0

import Units 1.0

import 'Chat.js' as Logic

// =============================================================================

Rectangle {
	id: container
	
	property alias proxyModel: chat.model	// ChatRoomProxyModel
	property alias tryingToLoadMoreEntries : chat.tryToLoadMoreEntries
	
	property string noticeBannerText : ''	// When set, show a banner with text and hide after some time
	onNoticeBannerTextChanged: if(noticeBannerText!='') messageBlock.state = "showed"
	
	// ---------------------------------------------------------------------------
	
	signal messageToSend (string text)
	
	// ---------------------------------------------------------------------------
	
	color: ChatStyle.color
	
	ColumnLayout {
		anchors.fill: parent
		spacing: 0
		
		ScrollableListView {
			id: chat
			
			// -----------------------------------------------------------------------
			property bool bindToEnd: false
			property bool displaying: false
			property int loaderCount: 0
			property int readyItems : 0
			property bool loadingLoader: (readyItems != loaderCount)
			property bool loadingEntries: container.proxyModel.chatRoomModel.entriesLoading || displaying
			property bool tryToLoadMoreEntries: loadingEntries || loadingLoader
			property bool isMoving : false	// replace moving read-only property to allow using movement signals.
			
			onLoadingEntriesChanged: {
				if( loadingEntries && !displaying)
					displaying = true
			}
			onBindToEndChanged: if( bindToEnd){
				markAsReadTimer.start()
			}
			Timer{
				id: markAsReadTimer
				interval: 5000
				repeat: false
				running: false
				onTriggered: container.proxyModel.chatRoomModel.resetMessageCount()
			}
			//property var sipAddressObserver: SipAddressesModel.getSipAddressObserver(proxyModel.fullPeerAddress, proxyModel.fullLocalAddress)
			// -----------------------------------------------------------------------
			Layout.fillHeight: true
			Layout.fillWidth: true
			
			highlightFollowsCurrentItem: false
			// Use moving event => this is a user action.
			onIsMovingChanged:{
				if(!chat.isMoving && chat.atYBeginning && !chat.loadingEntries){// Moving has stopped. Check if we are at beginning
					chat.displaying = true
					container.proxyModel.loadMoreEntriesAsync()
				}
			}
			section {
				criteria: ViewSection.FullString
				delegate: sectionHeading
				property: '$sectionDate'
			}
			// -----------------------------------------------------------------------
			
			Component.onCompleted: Logic.initView()
			onMovementStarted: {Logic.handleMovementStarted(); chat.isMoving = true}
			onMovementEnded: {Logic.handleMovementEnded(); chat.isMoving = false}
			
			// -----------------------------------------------------------------------
			
			Connections {
				target: proxyModel
				
				// When the view is changed (for example `Calls` -> `Messages`),
				// the position is set at end and it can be possible to load
				// more entries.
				onEntryTypeFilterChanged: Logic.initView()
				
				onMoreEntriesLoaded: {
					Logic.handleMoreEntriesLoaded(n)// move view to n - 1 item
					chat.displaying = false
				}
			}
			
			// -----------------------------------------------------------------------
			// Heading.
			// -----------------------------------------------------------------------
			
			Component {
				id: sectionHeading
				
				Item {
					implicitHeight: container.height + ChatStyle.sectionHeading.bottomMargin
					width: parent.width
					
					Borders {
						id: container
						
						borderColor: ChatStyle.sectionHeading.border.color
						bottomWidth: ChatStyle.sectionHeading.border.width
						implicitHeight: text.contentHeight +
										ChatStyle.sectionHeading.padding * 2 +
										ChatStyle.sectionHeading.border.width * 2
						topWidth: ChatStyle.sectionHeading.border.width
						width: parent.width
						
						Text {
							id: text
							
							anchors.fill: parent
							color: ChatStyle.sectionHeading.text.color
							font {
								bold: true
								pointSize: ChatStyle.sectionHeading.text.pointSize
							}
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignVCenter
							
							// Cast section to integer because Qt converts the
							// sectionDate in string!!!
							text: new Date(section).toLocaleDateString(
									  Qt.locale(App.locale)
									  )
						}
					}
				}
			}
			
			// -----------------------------------------------------------------------
			// Message/Event renderer.
			// -----------------------------------------------------------------------
			
			delegate: Rectangle {
				id: entry
				property bool isNotice : $chatEntry.type === ChatRoomModel.NoticeEntry
				property bool isCall : $chatEntry.type === ChatRoomModel.CallEntry
				property bool isMessage : $chatEntry.type === ChatRoomModel.MessageEntry
				
				function isHoverEntry () {
					return mouseArea.containsMouse
				}
				
				function removeEntry () {
					proxyModel.removeRow(index)
				}
				
				anchors {
					left: parent ? parent.left : undefined
					leftMargin: isNotice?0:ChatStyle.entry.leftMargin
					right: parent ? parent.right : undefined
					
					rightMargin: isNotice?0:ChatStyle.entry.deleteIconSize +
										   ChatStyle.entry.message.extraContent.spacing +
										   ChatStyle.entry.message.extraContent.rightMargin +
										   ChatStyle.entry.message.extraContent.leftMargin +
										   ChatStyle.entry.message.outgoing.areaSize
				}
				
				color: ChatStyle.color
				implicitHeight: layout.height + ChatStyle.entry.bottomMargin
				
				// ---------------------------------------------------------------------
				
				MouseArea {
					id: mouseArea
					
					cursorShape: Qt.ArrowCursor
					hoverEnabled: true
					implicitHeight: layout.height
					width: parent.width + parent.anchors.rightMargin
					acceptedButtons: Qt.NoButton
					ColumnLayout{
						id: layout
						spacing: 0
						width: entry.width
						Text{
							id:authorName
							Layout.leftMargin: timeDisplay.width + 10
							Layout.fillWidth: true
							text : $chatEntry.fromDisplayName ? $chatEntry.fromDisplayName : ''
							property var previousItem : {
								if(index >0)
									return proxyModel.getAt(index-1)
								else 
									return null
							}
							
							color: ChatStyle.entry.event.text.color
							font.pointSize: ChatStyle.entry.event.text.pointSize
							visible: isMessage 
									 && $chatEntry != undefined
									 && !$chatEntry.isOutgoing // Only outgoing
									 && (!previousItem  //No previous entry
										 || previousItem.type != ChatRoomModel.MessageEntry // Previous entry is a message
										 || previousItem.fromSipAddress != $chatEntry.fromSipAddress // Different user
										 || (new Date(previousItem.timestamp)).setHours(0, 0, 0, 0) != (new Date($chatEntry.timestamp)).setHours(0, 0, 0, 0) // Same day == section
										 )
						}
						RowLayout {
							
							spacing: 0
							width: entry.width
							
							// Display time.
							Text {
								id:timeDisplay
								Layout.alignment: Qt.AlignTop
								Layout.preferredHeight: ChatStyle.entry.lineHeight
								Layout.preferredWidth: ChatStyle.entry.time.width
								
								color: ChatStyle.entry.event.text.color
								font.pointSize: ChatStyle.entry.time.pointSize
								
								text: $chatEntry.timestamp.toLocaleString(
										  Qt.locale(App.locale),
										  'hh:mm'
										  )
								
								verticalAlignment: Text.AlignVCenter
								
								TooltipArea {
									text: $chatEntry.timestamp.toLocaleString(Qt.locale(App.locale))
								}
								visible:!isNotice
							}
							
							// Display content.
							Loader {
								id: loader
								height: (item !== null && typeof(item)!== 'undefined')? item.height: 0
								Layout.fillWidth: true
								source: Logic.getComponentFromEntry($chatEntry)
								property int count: 0
								asynchronous: chat.count - count > 100
								onStatusChanged: if( status == Loader.Ready) ++chat.readyItems
								Component.onCompleted: count = ++chat.loaderCount
								Component.onDestruction: {
														--chat.loaderCount
														if( status == Loader.Ready)
															--chat.readyItems
														}
							}
							Connections{
								target: loader.item
								ignoreUnknownSignals: true
								//: "Copied to clipboard" : when a user copy a text from the menu, this message show up.
								onCopyAllDone: container.noticeBannerText = qsTr("allTextCopied")
								//: "Selection copied to clipboard" : when a user copy a text from the menu, this message show up.
								onCopySelectionDone: container.noticeBannerText = qsTr("selectedTextCopied")
								onReplyClicked: {
									proxyModel.chatRoomModel.reply = $chatEntry
								}
								onForwardClicked:{
									window.attachVirtualWindow(Qt.resolvedUrl('../Dialog/SipAddressDialog.qml')
										//: 'Choose where to forward the message' : Dialog title for choosing where to forward the current message.
										, {title: qsTr('forwardDialogTitle'),
											addressSelectedCallback: function (sipAddress) {
																		var chat = CallsListModel.createChat(sipAddress)
																		if(chat){
																			chat.forwardMessage($chatEntry)
																			TimelineListModel.select(chat)
																		}
																	},
											chatRoomSelectedCallback: function (chatRoomModel){
																		if(chatRoomModel){
																			chatRoomModel.forwardMessage($chatEntry)
																			TimelineListModel.select(chatRoomModel)
																		}
										}
									})
								}
							}
						}
					}
				}
			}
			footer: Item{
				implicitHeight: composersItem.implicitHeight
				width: parent.width
				Text {
					id: composersItem
					property var composers : container.proxyModel.chatRoomModel ? container.proxyModel.chatRoomModel.composers : undefined
					property int count : composers && composers.length ? composers.length : 0
					color: ChatStyle.composingText.color
					font.pointSize: ChatStyle.composingText.pointSize
					height: visible ? undefined : 0
					leftPadding: ChatStyle.composingText.leftPadding
					visible: count > 0 && ( (!proxyModel.chatRoomModel.haveEncryption && SettingsModel.standardChatEnabled)
														 || (proxyModel.chatRoomModel.haveEncryption && SettingsModel.secureChatEnabled) )
					wrapMode: Text.Wrap
					//: '%1 is typing...' indicate that someone is composing in chat
					text:(count==0?'': qsTr('chatTyping','',count).arg(container.proxyModel.getDisplayNameComposers()))
				}
			}
						
			ActionButton{
				id: gotToBottomButton
				anchors.bottom: parent.bottom
				anchors.bottomMargin: 10
				anchors.right: parent.right
				anchors.rightMargin: 40
				visible: chat.isIndexAfter(chat.count-1)
				onVisibleChanged: updateMarkAsRead()
				Component.onCompleted: updateMarkAsRead()
				function updateMarkAsRead(){
					if(!visible)
						container.proxyModel.markAsReadEnabled = true
				}
				
				Connections{
					target: container.proxyModel
					onMarkAsReadEnabledChanged: if( !container.proxyModel.markAsReadEnabled)
													gotToBottomButton.updateMarkAsRead()
				}
				
				isCustom: true
				backgroundRadius: width/2
				colorSet: ChatStyle.gotToBottom
				onClicked: {
						chat.bindToEnd = true
					}
				MessageCounter{
					anchors.left: parent.right
					anchors.bottom: parent.top
					anchors.bottomMargin: -5
					anchors.leftMargin: -5
					count: container.proxyModel.chatRoomModel ? container.proxyModel.chatRoomModel.unreadMessagesCount : 0
				}
			}
			
			
		}
		ChatMessagePreview{
				id: chatMessagePreview
				Layout.fillWidth: true
				
				replyChatRoomModel: proxyModel.chatRoomModel
				
			}
			Rectangle{
				id: messageBlock
				onHeightChanged: height = Layout.preferredHeight
				Layout.preferredHeight: visible && opacity > 0 ? 32 : 0
				Layout.fillWidth: true
				Layout.leftMargin: ChatStyle.entry.leftMargin
				Layout.rightMargin: ChatStyle.entry.rightMargin
				color: ChatStyle.messageBanner.color
				radius: 10
				state: "hidden"
				Timer{
					id: hideNoticeBanner
					interval: 4000
					repeat: false
					onTriggered: messageBlock.state = "hidden"
				}
				RowLayout{
					anchors.centerIn: parent
					spacing: 5
					Icon{
						icon: ChatStyle.copyTextIcon
						overwriteColor: ChatStyle.messageBanner.textColor
						iconSize: 20
					}
					Text{
						Layout.fillHeight: true
						Layout.fillWidth: true
						text: container.noticeBannerText
						font {
							pointSize: ChatStyle.messageBanner.pointSize
						}
						color: ChatStyle.messageBanner.textColor
					}
				}
				states: [
					State {
						name: "hidden"
						PropertyChanges { target: messageBlock; opacity: 0 }
					},
					State {
						name: "showed"
						PropertyChanges { target: messageBlock; opacity: 1 }
					}
				]
				transitions: [
					Transition {
						from: "*"; to: "showed"
						SequentialAnimation{
							NumberAnimation{ properties: "opacity"; easing.type: Easing.OutBounce; duration: 500 }
							ScriptAction{ script: hideNoticeBanner.start()}	
						}
					},
					Transition {
						SequentialAnimation{
							NumberAnimation{ properties: "opacity"; duration: 1000 }
							ScriptAction{ script: container.noticeBannerText = '' }
						}
					}
				]
			}
		// -------------------------------------------------------------------------
		// Send area.
		// -------------------------------------------------------------------------
		
		Borders {
			id: textAreaBorders
			Layout.fillWidth: true
			Layout.preferredHeight: textArea.height
			
			borderColor: ChatStyle.sendArea.border.color
			topWidth: ChatStyle.sendArea.border.width
			visible: proxyModel.chatRoomModel && !proxyModel.chatRoomModel.hasBeenLeft && (!proxyModel.chatRoomModel.haveEncryption && SettingsModel.standardChatEnabled || proxyModel.chatRoomModel.haveEncryption && SettingsModel.secureChatEnabled)
			
			
			DroppableTextArea {
				id: textArea
				
				enabled:proxyModel && proxyModel.chatRoomModel ? !proxyModel.chatRoomModel.hasBeenLeft:false
				isEphemeral : proxyModel && proxyModel.chatRoomModel ? proxyModel.chatRoomModel.ephemeralEnabled:false
				
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.bottom: parent.bottom
				
				height:ChatStyle.sendArea.height + ChatStyle.sendArea.border.width
				minimumHeight:ChatStyle.sendArea.height + ChatStyle.sendArea.border.width
				maximumHeight:container.height/2
				
				dropEnabled: SettingsModel.fileTransferUrl.length > 0
				dropDisabledReason: qsTr('noFileTransferUrl')
				placeholderText: qsTr('newMessagePlaceholder')
				
				onDropped: Logic.handleFilesDropped(files)
				onTextChanged: Logic.handleTextChanged(text)
				onValidText: {
					textArea.text = ''
					chat.bindToEnd = true
					if(proxyModel.chatRoomModel) {
						proxyModel.sendMessage(text)
					}else{
						console.log("Peer : " +proxyModel.peerAddress+ "/"+chat.model.peerAddress)
						proxyModel.chatRoomModel = CallsListModel.createChat(proxyModel.peerAddress)
						proxyModel.sendMessage(text)
					}
				}
				onAudioRecordRequest: RecorderManager.resetVocalRecorder()
				Component.onCompleted: {text = proxyModel.cachedText; cursorPosition=text.length}
				Rectangle{
					anchors.fill:parent
					color:'white'
					opacity: 0.5
					visible:!textArea.enabled
				}
			}
		}
	}
	
	
	
	// ---------------------------------------------------------------------------
	// Scroll at end if necessary.
	// ---------------------------------------------------------------------------
	
	Timer {
		interval: 100
		repeat: true
		running: true
		
		onTriggered: chat.bindToEnd && chat.positionViewAtEnd()
	}
	
}
