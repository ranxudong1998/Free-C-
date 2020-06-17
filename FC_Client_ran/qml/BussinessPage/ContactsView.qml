import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1
import "../Component"

Page {
    id: contactsView

    // contactsView

    title: qsTr("Contacts")
    property int headPrtraitSize: 50

    Constant { id: constant }

    ListView {
        id: contactsListView
        width: contactsView.width
        height: contactsView.height
        //model: contactsItemsModel
        model: contactsItemsModel  //item数量
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
        states: [
            State {
                name: "ShowBar"
                when: contactsListView.movingVertically
                PropertyChanges { target: verticalScrollBar; opacity: 1 }
            },
            State {
                name: "HideBar"
                when: !contactsListView.movingVertically
                PropertyChanges { target: verticalScrollBar; opacity: 0 }
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
            height: contactsListView.height - width
            anchors.right: contactsListView.right
            orientation: Qt.Vertical
            position: contactsListView.visibleArea.yPosition
            pageSize: contactsListView.visibleArea.heightRatio
        }

        delegate: ColumnLayout {
            id:columnlayout
            width: contactsView.width
            height: 70
            IconLabel {
                id:inconlabel
                spacing: 10
                Layout.fillWidth: true;
                height: 70
                iconWidth: headPrtraitSize
                iconHeight: headPrtraitSize
                iconSource: constant.testPic
                labelText: name
                fontPointSize: constant.normalFontPointSize



                onPressAndHold: {
                    menu.chatItemIndex = index;
                    menu.popup();
                }


                //分割线
                Separator {
                    color: "#666"; orientation: Qt.Horizontal ;
                    length: parent.width * 0.8
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                onClicked: {
                    console.log("go to the person profile");
                    __LoadProfilePage(id, name)
                 //   __PushPage(Qt.resolvedUrl("./ProfilePage.qml"));
                }
            }

        }

        Menu {
            id: menu
            property int chatItemIndex: 0
            MenuItem {
                text: qsTr("Set Remarks and Tags")
                onTriggered: {
                    contactsListView.model.remove(menu.chatItemIndex);
                }
            }
        }



        ListModel {

            id: contactsItemsModel

            Component.onCompleted: {

                contactsItemsModel.append(
                            {"name":"ran1",
                             "id":"11111111"
                            });

                contactsItemsModel.append(
                            {"name":"ran2",
                             "id":"11111112"
                            });

                contactsItemsModel.append(
                            {"name":"ran3",
                             "id":"11111113"
                            });

                contactsItemsModel.append(
                            {"name":"ran4",
                             "id":"11111114"
                            });

            }
        }
    }
    function __LoadProfilePage(userid, username){
        if(1+1==2){
        __PushPage(Qt.resolvedUrl("./ProfilePage.qml"),
                   {s_userid:userid,s_username: username } );}

    }

}

