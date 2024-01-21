import QtQuick 2.15
import QtMultimedia

Item {

   property bool play:false

   SoundEffect
   {
       id:moving
       source: "/sounds/04_step_grass_3.wav"


   }

   Timer
   {
       id:movePlay
       running: true
       repeat: true
       interval: 500
       onTriggered: if(play) moving.play()
   }


}
