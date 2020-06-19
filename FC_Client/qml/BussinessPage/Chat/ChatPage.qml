import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.LocalStorage 2.0
import "../../Component"

Page {
    id: chatPage

    property var s_username  //聊天对象名
    property var s_userid    //聊天对象ID

    //消息显示透明度设置
    property int opacityLeft : 1
    property int opacityRigtht : 0


    focus: true
    Keys.onBackPressed: {
        event.accepted = true;
        try { stackView.pop(); }  catch(e) { }
    }

    Constant { id: constant }

    topBar: TopBar {
        id: topBar

        //! aviod looping binding
        Item { anchors.fill: parent }
        RowLayout {
            anchors.fill: parent
            spacing: 10

            Item { width:  topBar.height - 2; height: width }

            IconButton {
                height: topBar.height - 2
                width: topBar.height - 2
                anchors.verticalCenter: parent.verticalCenter
                activeIconSource: constant.backActiveIcon
                inactiveIconSource: constant.backInactiveIcon
                onClicked: {
                    try { stackView.pop(); }  catch(e) { }
                }

                Separator {
                    color: "black"
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        // such as menuBar

        Row {
            parent: topBar
            anchors.left: parent.left
            anchors.leftMargin: (topBar.height - 2) * 1.5
            anchors.fill: parent
            Label {
                text: s_username + s_userid
                // Layout.alignment: Qt.AlignRight
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

    }

    bottomBar: BottomBar {
        RowLayout {
            anchors.fill: parent
            spacing: 5

            IconButton {
                width: topBar.height - 2
                height: topBar.height - 2
                activeIconSource: constant.soundActiveIcon
                inactiveIconSource: constant.soundInactiveIcon
            }

            Item {
                Layout.fillWidth: true
                implicitHeight: textInput.implicitHeight
                SampleTextArea {
                    id: textInput
                    width: parent.width
                    implicitHeight: {
                        if(lineCount >= 2) {
                            (topBar.height - 2) * 2
                        } else {
                            (topBar.height- 2) * lineCount
                        }
                    }
                    IconButton {
                        width: topBar.height * 0.9
                        height: topBar.height * 0.9
                        activeIconSource: constant.emoticonActiveIcon
                        inactiveIconSource: constant.emoticonInactiveIcon
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                    }

                }
            }

            SampleButton {
                Layout.alignment: Qt.AlignRight
                text: qsTr("Send")
                onClicked:  {
                    if(textInput.text != "" ) {
                        //传入用户ID,消息接收端ID,时间,消息内容
                        message_listModel.add([s_userid,profilemsg.account,"1",textInput.text])
                        message_listModel.currentIndex = message_listModel.count - 1
                        textInput.text = "";
                    }
                }
            }
            Item { width: 5; height: 5 }
        }
    }

    ListView {
        id: chatListView
        anchors.fill: parent

        model:message_listModel

        spacing: 20

        readonly property int itemSpacing: 10
        readonly property int headPortraitPictureWidth: 60

        readonly property int
        chatContentAreaWidth: chatListView.width - chatListView.headPortraitPictureWidth*2 - 2 *chatListView.itemSpacing

        delegate: chatAreaComponent
    }

    Connections{
        target: message_listModel
        onRecv_mess:{
//            if(message_listModel.msgOpacity==1){
//               opacityLeft=1 ;
//                opacityRigtht=0;
//            }else{
//               opacityRigtht=1;
//               opacityLeft=0;
//            }
            chatListView.currentIndex = chatListView.count - 1
        }
    }
    Component {
        id: chatAreaComponent
        Row {
            id: chatArea
            spacing: chatListView.itemSpacing
            Image {
                // 头像
                id: headPortraitPic1
                width: chatListView.headPortraitPictureWidth
                height: chatListView.headPortraitPictureWidth
                sourceSize: Qt.size(width, height)
                source: constant.testPic
                opacity: opacityLeft
            }

            Item {
                id: chatContentAreaLeft
                opacity: opacityLeft
                width: chatListView.chatContentAreaWidth
                height: chatContentTextLeft.contentHeight > 60 ? chatContentTextLeft.contentHeight : 60

                Rectangle {
                    id:chatRectangleLeft
                    border.width: 1
                    border.color: "#ccc"
                    anchors.left: parent.left
                    height: parent.height
                    color: "green"
                    width: chatContentTextLeft.contentWidth > 200 ? chatContentTextLeft.contentWidth : 200
                    Text {
                        id: chatContentTextLeft
                        width: 300
                        anchors.left: parent.left
                        anchors.leftMargin: chatListView.itemSpacing
                        anchors.top: parent.top
                        anchors.topMargin: chatListView.itemSpacing
                        // anchors.centerIn: parent
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        text:content
                        font.pointSize: constant.normalFontPointSize
                        font.family: "微软雅黑"
                    }
                }
            }

            Image {
                // 头像
                id: headPortraitPic2
                width: chatListView.headPortraitPictureWidth
                height: chatListView.headPortraitPictureWidth
                sourceSize: Qt.size(width, height)
                source: constant.testPic
                opacity: opacityRigtht
            }
            Item {
                id: chatContentAreaRight
                opacity: opacityRigtht
                width: chatListView.chatContentAreaWidth
                height: chatContentTextRight.contentHeight > 60 ? chatContentTextRight.contentHeight : 60

                Rectangle {
                    id:chatRectangleRight
                    border.width: 1
                    border.color: "#ccc"
                    anchors.right: parent.right
                    height: parent.height
                    color: "green"
                    width: chatContentTextRight.contentWidth > 200 ? chatContentTextRight.contentWidth : 200
                    Text {
                        id: chatContentTextRight
                        width: 300
                        anchors.right: parent.right
                        anchors.rightMargin: chatListView.itemSpacing
                        anchors.top: parent.top
                        anchors.topMargin: chatListView.itemSpacing
                        // anchors.centerIn: parent
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignRight
                        text:content
                        font.pointSize: constant.normalFontPointSize
                        font.family: "微软雅黑"
                    }
                }
            }
      }
    }

}

