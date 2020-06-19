import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import UserType 1.0

Item {
    id:registerPage
    width: 420
    height: 800

    Rectangle {
      id: loginForm
      anchors.centerIn: parent
      color: "white"
      width: content.width + 48
      height: content.height + 16
      radius: 4
    }
    User{
      id:user
    }

    // registerform content
    GridLayout {
      id: content
      anchors.centerIn: loginForm
      columnSpacing: 20
      rowSpacing: 10
      columns: 2

      // headline
      Text {
        Layout.topMargin: 8
        Layout.bottomMargin: 12
        Layout.columnSpan: 2
        Layout.alignment: Qt.AlignHCenter
        text: "Register"
      }

      // email text and field
      Text {
        text: qsTr("E-mail")
        font.pixelSize: 12
      }

      TextField {
        id: txtUsername
        Layout.preferredWidth: 200
        font.pixelSize: 14
      }

      // password text and field
      Text {
        text: qsTr("Password")
        font.pixelSize: 12
      }

      TextField {
        id: txtPassword
        Layout.preferredWidth: 200
        font.pixelSize: 14
        echoMode: TextInput.Password //field
      }

      // column for buttons, we use column here to avoid additional spacing between buttons
      Column {
        Layout.fillWidth: true
        Layout.columnSpan: 2
        Layout.topMargin: 12

        // buttons
        Button {
          text: qsTr("ok")
          flat: false
          anchors.horizontalCenter: parent.horizontalCenter
          onClicked: {
              console.log(txtUsername.text,txtPassword.text)
//              if(user.insertMessage(txtUsername.text,txtPassword.text))
//              {
//                  var component = Qt.createComponent("Login.qml");
//                  component.createObject(registerPage);
//              }
          }
        }
      }
    }
}
