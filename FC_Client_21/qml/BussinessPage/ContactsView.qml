import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Window 2.0
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11
import buddy 1.0
import "../Component"
Page {
    id: contactsView

    // contactsView
    width: 360
    height: 720

    title: qsTr("Contacts")

    property int headPrtraitSize: 50
    property alias listModel: listView.model
    Constant { id: constant }

    Rectangle {
        id: rectangle
        width: parent.width
        height: 64
        color: "#ffffff"
        Image {
            id:image
            width: 40
            height: 40
            source: constant.newfriendsIcon
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 10
        }
        Label{
            id:lable
            width: parent.width-120
            height: 40
            text: qsTr("新的朋友")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pointSize: 15
            anchors.centerIn: parent
            anchors.right: rectangle.right
        }
        Separator {
            color: "black"
            orientation: Qt.Horizontal
            anchors.top: lable.bottom
            anchors.left: image.right
            anchors.leftMargin: 10
        }
        Rectangle{
            id:numRect
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20
            visible: {
                parseInt(numValue.text) ? true : false;
//              转换位int类型 如果为0则不显示，否则显示数量
            }
            width: 20
            color: "red"
            height: 20
            radius: 50
            Text {
                id:numValue
                color: "#ebebeb"
                anchors.fill: parent
                text: buddy.value
                styleColor: "#ebebeb"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
        MouseArea{
            id:newfriends
            enabled: parseInt(numValue.text) ? true : false;
            anchors.fill: parent
            onClicked: {
                __PushPage(Qt.resolvedUrl("./Contact/NewFriendsPage.qml"), {} ); //压入一个新的界面
            }
        }
    }
    Rectangle {
        id: rectangle1
        width: parent.width
        anchors.top: rectangle.bottom
        height: 64
        color: "#ffffff"
        Image {
            id:image1
            width: 40
            height: 40
            source: constant.groupchatIcon
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 10
        }
        Label{
            id:lable1
            width: parent.width-120
            height: 40
            text: qsTr("群聊")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pointSize: 15
            anchors.centerIn: parent
            anchors.right: rectangle1.right
        }
        Separator {
            color: "black"
            orientation: Qt.Horizontal
            anchors.top: lable1.bottom
            anchors.left: image1.right
            anchors.leftMargin: 10
        }
        MouseArea{
            id:groupchat
            onClicked: {
            }
        }
    }

    ListView{
        id:listView
        anchors.fill: parent
        anchors.top: rectangle.bottom
        anchors.topMargin:145
        spacing: 20
        Material.background: "white"
        model: teamModel.teams
        delegate: list_delegate
    }
    Component{
        id:list_delegate

        Column{
            id:objColumn


            //在这里设置的是否显现
            Component.onCompleted: {
                for(var i = 1; i < objColumn.children.length - 1; ++i) {
                    objColumn.children[i].visible = false
                }
            }

            MouseArea{
                width:listView.width
                height: objItem.implicitHeight
                enabled: objColumn.children.length > 2
                onClicked: {
                    console.log("onClicked..")
                    var flag = false;
                    for(var i = 1; i < parent.children.length - 1; ++i) {
                        console.log("onClicked..i=",i)
                        flag = parent.children[i].visible;
                        parent.children[i].visible = !parent.children[i].visible
                    }
                    console.log("onClicked..flag = ",flag)

                    //旋转，图片
                    if(!flag){
                        iconAin.from = 0
                        iconAin.to = 90
                        iconAin.start()
                    }
                    else{
                        iconAin.from = 90
                        iconAin.to = 0
                        iconAin.start()
                    }
                }
                Row{
                    id:objItem
                    spacing: 10
//                    leftPadding: 20

                    Image {
                        id: icon
                        width: 20
                        height: 20
                        source: constant.friendlistright
                        anchors.verticalCenter: parent.verticalCenter
                        RotationAnimation{
                            id:iconAin
                            target: icon
                            duration: 100
                        }
                    }
                    Label{
                        id:meeting_name
                        text: teamname
                        font.pointSize: constant.middleFontPointSize+1.0
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Label{
                        text: date
                        font.pointSize: constant.middleFontPointSize+1.0
                        color:"grey"
                        anchors.verticalCenter: parent.verticalCenter

                    }
                }
            }
            Repeater {
               model:buddys

               delegate: Rectangle{
                   id:rect
                   width: parent.width
                   height: 80
                   Rectangle {
                       id: fileicon
                       width: 50
                       height: 50
                       radius: 50
                       Image {
                           id: head
                           anchors.fill: parent
                           source: heading
                       }
                       anchors{
                           left: parent.left
                           leftMargin: 20
                           verticalCenter: parent.verticalCenter
                       }
                       //使其位于margin
                   }
                   Column{
                       anchors{
                           left: fileicon.right
                           leftMargin: 20
                           top: parent.top
                           topMargin:20
                       }
//                       topPadding: 10
                       spacing: 10

                       Label{
                           text: account
                           font.pointSize: constant.middleFontPointSize+1.0
                       }
                       Label{
                           text: nickname
                           color: "grey"
                           font.pointSize: constant.middleFontPointSize+1.0
                       }
                   }
                   MouseArea{
                    anchors.fill: rect
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: {
                        if(mouse.button == Qt.RightButton)
                            contextMenu.popup()
                    }
                    //弹出菜单
                    Menu {
                              id: contextMenu
                              MenuItem { text: "修改好友备注"
                                  onClicked: {
                                      var component = Qt.createComponent("UpdateRemarkDialog.qml");
                                      if(component.status === Component.Ready){
                                          var object=component.createObject(contactsView);
                                          object.teamId = teamId;
                                          object.itemId = itemId;
                                          //可以修改对方的值
                                      }
                                  }

                              }
                              MenuItem {
                                  text: "删除好友"
                                  onClicked: {
                                      message_handle.delete_friend(teamId,itemId);
                                      listModel = teamModel.teams;
                                  }

                              }
                              MenuItem { text: "移动联系人至"}
                    }
                   }
               }

            }
        }
    }

//    Rectangle {
//        id: rectangle
//        x: 0
//        y: 0
//        width: 640
//        height: 61
//        color: "#ffffff"

//        Image {
//            id: image
//            x: 0
//            y: 0
//            width: 71
//            height: 61
//            fillMode: Image.PreserveAspectFit
//            source: "qrc:/qtquickplugin/images/template_image.png"
//        }
//    }

//    ListView {
//        id: contactsListView
//        width: contactsView.width
//        height: contactsView.height
//        //model: contactsItemsModel
//        model: contactsItemsModel  //item数量
//        add: Transition {
//            NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 400 }
//            NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 400 }
//        }
//        move: Transition {
//            NumberAnimation { properties: "x,y"; duration: 800; easing.type: Easing.OutBack }
//        }
//        displaced: Transition {
//            NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
//        }
//        states: [
//            State {
//                name: "ShowBar"
//                when: contactsListView.movingVertically
//                PropertyChanges { target: verticalScrollBar; opacity: 1 }
//            },
//            State {
//                name: "HideBar"
//                when: !contactsListView.movingVertically
//                PropertyChanges { target: verticalScrollBar; opacity: 0 }
//            }
//        ]

//        transitions: [
//            Transition {
//                from: "ShowBar"
//                to: "HideBar"
//                NumberAnimation { properties: "opacity"; duration: 400 }
//            },
//            Transition {
//                from: "HideBar"
//                to: "ShowBar"
//                NumberAnimation { properties: "opacity"; duration: 400 }
//            }
//        ]

//        ScrollBar {
//            id: verticalScrollBar
//            width: 10 * Screen.devicePixelRatio
//            height: contactsListView.height - width
//            anchors.right: contactsListView.right
//            orientation: Qt.Vertical
//            position: contactsListView.visibleArea.yPosition
//            pageSize: contactsListView.visibleArea.heightRatio
//        }

//        delegate: ColumnLayout {
//            id:columnlayout
//            width: contactsView.width
//            height: 70
//            IconLabel {
//                id:inconlabel
//                spacing: 10
//                Layout.fillWidth: true;
//                height: 70
//                iconWidth: headPrtraitSize
//                iconHeight: headPrtraitSize
//                iconSource: constant.testPic
//                labelText: name
//                fontPointSize: constant.normalFontPointSize



//                onPressAndHold: {
//                    menu.chatItemIndex = index;
//                    menu.popup();
//                }


//                //分割线
//                Separator {
//                    color: "#666"; orientation: Qt.Horizontal ;
//                    length: parent.width * 0.8
//                    anchors.bottom: parent.bottom
//                    anchors.horizontalCenter: parent.horizontalCenter
//                }

//                onClicked: {
//                    console.log("go to the person profile");
//                    __LoadProfilePage(id, name)
//                 //   __PushPage(Qt.resolvedUrl("./ProfilePage.qml"));
//                }
//            }

//        }

//        Menu {
//            id: menu
//            property int chatItemIndex: 0
//            MenuItem {
//                text: qsTr("Set Remarks and Tags")
//                onTriggered: {
//                    contactsListView.model.remove(menu.chatItemIndex);
//                }
//            }
//        }

//    function __LoadProfilePage(userid, username){
//        if(1+1==2){
//        __PushPage(Qt.resolvedUrl("./ProfilePage.qml"),
//                   {s_userid:userid,s_username: username } );}

//    }

}

