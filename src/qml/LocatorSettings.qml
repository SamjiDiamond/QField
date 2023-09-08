import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import org.qgis 1.0
import org.qfield 1.0

import Theme 1.0

Popup {
    id: popup

    property alias locatorFiltersModel: locatorfiltersList.model

    width: Math.min(400, mainWindow.width - Theme.popupScreenEdgeMargin)
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    padding: 0

    Page {
        id: page
        width: parent.width
        height: locatorfiltersList.height + 60
        padding: 10
        header: ToolBar {
          id: toolBar
          height: 48

          background: Rectangle {
            color: "transparent"
          }

          Label {
            anchors.centerIn: parent
            leftPadding: 48
            rightPadding: 48
            width: parent.width - 20
            text: qsTr( "Search Bar Settings" )
            font: Theme.strongFont
            color: Theme.mainColor
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
          }

          QfToolButton {
            id: closeButton
            anchors {
              top: parent.top
              right: parent.right
            }
            iconSource: Theme.getThemeIcon( 'ic_close_black_24dp' )
            iconColor: Theme.mainTextColor
            bgcolor: "transparent"

            onClicked: {
              popup.close();
            }
          }
        }

        Column {
            spacing: 4
            width: parent.width

            ListView {
                id: locatorfiltersList
                width: parent.width
                height: Math.min( childrenRect.height, mainWindow.height - 160 );
                clip: true

                delegate: Rectangle {
                    id: rectangle
                    width: parent ? parent.width : undefined
                    height: inner.height
                    color: "transparent"

                    ColumnLayout {
                        id: inner
                        width: parent.width

                        Text {
                            Layout.fillWidth: true
                            topPadding: 5
                            leftPadding: 5
                            text: Name
                            font: Theme.defaultFont
                            color: Theme.mainTextColor
                            wrapMode: Text.WordWrap
                        }
                        Text {
                            Layout.fillWidth: true
                            leftPadding: 5
                            bottomPadding: 5
                            text: Description
                            font: Theme.tipFont
                            color: Theme.secondaryTextColor
                            wrapMode: Text.WordWrap
                        }
                        Text {
                            visible: Default ? false : true
                            Layout.fillWidth: true
                            leftPadding: 5
                            bottomPadding: 5
                            text: qsTr('When disabled, this locator filter can still be used by typing the prefix %1 in the search bar.').arg('<b>'+Prefix+'</b>')
                            font: Theme.tipFont
                            color: Theme.secondaryTextColor
                            wrapMode: Text.WordWrap
                        }
                        CheckBox {
                              Layout.fillWidth: true
                              topPadding: 5
                              bottomPadding: 5
                              text: qsTr('Enable %1 locator by default').arg('<b>'+Name+'</b>')
                              font: Theme.tipFont
                              indicator.height: 16
                              indicator.width: 16
                              indicator.implicitHeight: 24
                              indicator.implicitWidth: 24
                              checked: Default? true : false
                              onCheckedChanged: Default = checked
                        }
                    }
                }
            }
        }
    }
}
