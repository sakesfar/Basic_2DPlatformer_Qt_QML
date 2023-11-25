import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id:mainWnd
    width: 640
    height: 368
    visible: true
    title: qsTr("2D Platformer")

    StackView{
        id:stackView
        anchors.fill: parent
        initialItem: MainMenu{
            onStartGame: {
                stackView.pop()
                stackView.push("LoadingScreen.qml")
                gameViewLoader.source = "GameView.qml"
            }
        }

    }

    Loader {
          id: gameViewLoader
          asynchronous: true
          onLoaded: {
              stackView.pop()
              stackView.push(item)
              item.isGameViewLoaded = true
          }
      }










    /*
    Background
    {
        id:backgr
    }


    Repeater {
        id: foregroundDisplay
        anchors.fill:parent
        model: tilesData
        delegate: OuterDelegate{}
    }

    Player
    {
        id:pl

    }


    Repeater{

        id:skelSpread
        anchors.fill: parent
        model: Woo.getSKeletonPos()
        delegate: Skeleton
        {
            id:skeletonItem


        }

    }
    */




}
