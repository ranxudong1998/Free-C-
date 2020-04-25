import QtQuick 2.0
import QtQuick.Controls 2.0
ApplicationWindow{
    id: window
    visible: true
    width: 640
    height: 480
    color: "lightblue"
    title: qsTr("Logup Dialog")

    TextInput{
        id: textinput
        x: 134
        y: 189
        width: 80
        height: 20
        text: qsTr("")
        font.pixelSize: 12
        focus: true
        validator: IntValidator{top:999999;bottom: 111111}
    }
    Label {
        id: label
        x: 134
        y: 150
        width: 135
        height: 21
        text: qsTr("enter your count:")
    }
    Button {
        id: button
        x: 382
        y: 283
        text: qsTr("log_up")
        onClicked: {
            if(textinput.text.length!=0){
                console.log(textinput.text+"log up");
                profile.set_account(textinput.text)
//                console.log(profile.account);
                chat_dialog.visible = true;
                window.visible = false;
            }
        }
    }
    Fc_chat_dialog{
        id: chat_dialog
        visible: false
    }

}
