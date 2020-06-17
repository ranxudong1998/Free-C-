import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1
import "../Component"

Page {
    id: chatsView
    title: "FriendList"
    color: "white"
    property int headPrtraitSize: 90
    signal openNewChat(int s_userid, string s_username)

    onOpenNewChat: {

        if(__find(s_userid) !== null) {
            // go to the chat page
            __LoadChatPage(s_userid, s_username);
        } else {
            chatItemsModel.append(
                        {
                            "chatName":s_username,
                            "chatContext":s_userid
                        });

            // go to the chat page
            __LoadChatPage(s_userid, s_username);

        }
    }

    ListView {
        id: listView
        width: chatsView.width
        height: chatsView.height

        model: chatItemsModel

        add: Transition {
            NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 400 }
            NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 400 }
        }
        move: Transition {
            NumberAnimation { properties: "x,y"; duration: 800; easing.type: Easing.OutBack }
        }
        displaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
        }

        //scrollbar移动效果
        states: [
            State {
                name: "ShowBar"
                when: listView.movingVertically
                PropertyChanges { target: verticalScrollBar; opacity: 0}
            },
            State {
                name: "HideBar"
                when: !listView.movingVertically
                PropertyChanges { target: verticalScrollBar; opacity: 1}
            }
        ]

        transitions: [
            Transition {
                from: "ShowBar"
                to: "HideBar"
                NumberAnimation { properties: "opacity"; duration: 400 }
            },
            Transition {
                from: "HideBar"
                to: "ShowBar"
                NumberAnimation { properties: "opacity"; duration: 400 }
            }
        ]


        ScrollBar {
            id: verticalScrollBar
            width: 10 * Screen.devicePixelRatio
            height: listView.height - width
            anchors.right: listView.right
            orientation: Qt.Vertical
            position: listView.visibleArea.yPosition
            pageSize: listView.visibleArea.heightRatio
        }


        delegate: Rectangle {
            id: chatItem
            // chatItem
            width: chatsView.width
            height: headPrtraitSize
            color: "transparent"
            border.width: 1
            border.color: "#ccc"
            state: "UnSelected"
            states: [
                State {
                    name: "Selected"
                    PropertyChanges { target:chatItem; color: "#ccc" }
                },
                State {
                    name: "UnSelected"
                    PropertyChanges { target:chatItem; color: "transparent" }
                }
            ]

            transitions: [
                Transition {
                    from: "Selected"
                    to: "UnSelected"
                    NumberAnimation { properties: "color"; duration: 400 }
                },
                Transition {
                    from: "UnSelected"
                    to: "Selected"
                    NumberAnimation { properties: "color"; duration: 400 }
                }
            ]

            RowLayout {
                anchors.fill: parent
                anchors.margins: spacing
                Image {
                    width: headPrtraitSize
                    height: headPrtraitSize
                    anchors.verticalCenter: parent.verticalCenter
                    sourceSize.width: headPrtraitSize - 2
                    sourceSize.height: headPrtraitSize - 2
                    source: "../resource/tests/tests001.jpeg"
                    fillMode: Image.PreserveAspectFit
                    //clip: true
                }
                ColumnLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    RowLayout {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Label { Layout.fillWidth: true; text: name }
                        
                    }
                    RowLayout {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Label { Layout.fillWidth: true; text: chatContext }
                       
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onPressAndHold: {
                    chatItem.state = "Selected";
                    chatItemMenu.aboutToHide.connect(function(){
                        chatItemMenu.aboutToHide.disconnect(arguments.callee);
                        chatItem.state = "UnSelected";
                    });
                    chatItemMenu.aboutToShow.connect(function(){
                        chatItemMenu.aboutToShow.disconnect(arguments.callee);
                        chatItem.state = "Selected";
                    });
                    chatItemMenu.chatItemIndex = index;
                    chatItemMenu.popup();
                }
                onClicked: {
                    __LoadChatPage(chatContext, name);
                }
            }
        }

        Menu {
            id: chatItemMenu
            property int chatItemIndex: 0
            MenuItem {
                text: qsTr("Delete conversation")
                onTriggered: {
                    listView.model.remove(chatItemMenu.chatItemIndex);
                }
            }
            MenuItem {
                text: qsTr("Sticky on top")
                onTriggered: {
                    listView.model.move(chatItemMenu.chatItemIndex, 0, 1);
                }
            }
            MenuItem {
                text: qsTr("Clear")
                onTriggered: {
                    listView.model.clear();
                }
            }
        }

        ListModel {
            id: chatItemsModel

            /*
                  联系人名字
                  聊天记录
                  时间
                  是否
                 */
            Component.onCompleted: {

                //暂时假定添加20个消息
                for(var i=11111111; i<11111121; i++) {

                    chatItemsModel
                    .append(
                         {
                             "name":"Ran: ",
                             "chatName":""+i,
                             "chatContext": i
                         });
                }
            }
        }
    }

    function __find(s) {
        if(chatItemsModel.count == 0) return null;
        var chatItemsCount = chatItemsModel.count;
        for(var i=0; i<chatItemsCount; i++) {


            if(chatItemsModel.get(i).chatContext === s_userid) {
                return chatItemsModel.get(i);
            }
        }
        return null;
    }

    function __LoadChatPage(s_userid, s_username){

        __PushPage(Qt.resolvedUrl("./Chat/ChatPage.qml"),
                   {s_userid:s_userid,s_username: s_username } );


    }

}

