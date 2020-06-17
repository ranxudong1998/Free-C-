import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.0
import "./Component"
import "./BussinessPage"

Page {
    id: mainPage
    title: "Free C"
    color: "white"

    Constant { id: constant }

    Rectangle {
      id: loginForm
      anchors.centerIn: parent
      color: "white"
      width: content.width + 48
      height: content.height + 16
      radius: 4
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
        text: "Login"
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
      Loader{
        id:loader
      }

      // column for buttons, we use column here to avoid additional spacing between buttons
      Column {
        Layout.fillWidth: true
        Layout.columnSpan: 2
        Layout.topMargin: 12

        // buttons
        Button {
          text: qsTr("Login")
          flat: false
          anchors.horizontalCenter: parent.horizontalCenter
          onClicked: {
              profile_handle.login(txtUsername.text,txtPassword.text)
              __PushPage(Qt.resolvedUrl("./Fc_MainView.qml"), {} ); //压入一个新的界面
          }
        }

        Button {
          text: qsTr("No account yet? Register now")
          flat: true
          anchors.horizontalCenter: parent.horizontalCenter
          onClicked: {
            var component = Qt.createComponent("Register.qml");
            component.createObject(loginPage);
            console.debug("registering...")
          }
        }
      }
    }
}
