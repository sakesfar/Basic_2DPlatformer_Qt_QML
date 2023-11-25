import QtQuick 2.15
import QtQuick.Controls 2.15

Item {

    id:gameView
    //Component.onCompleted:  {pl.focus=true; console.log("WTF")}
    property bool isGameViewLoaded: false





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
        focus:parent.focus
        id:pl
        gameViewLoaded: isGameViewLoaded
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

}


