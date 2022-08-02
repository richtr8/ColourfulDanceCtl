ColourfulDanceCtl
----
arduino Joystick library code for any sort of controller using analogue switches & three-wire WS2812B LEDs.  
intended for dance game usage at 1000hz, using original arcade sensors & per-panel colour profile support via FastLED.

credit to dominickp for his original FastLED implementation amended to teejusb's fsr repo.  
credit to nato for both restructuring the PANEL-LED array to support 3-wire ws2812b LEDs & writing the "setColors" functions.  


features
----
- works with any kind of analogue switch-based controller you may build
- supports as many buttons as you can fit on your arduino
- supports as many lights per button as you want
- polls at 1000hz
- made of cheap ass arduino hardware - tested working on a $10 pro micro  


/!\ DISCLAIMER /!\
----
this code **has *NOT* been tested on a real pad yet!!** it has however been extensively "breadboard" tested using a single sanwa obsf pushbutton in place of switches hooked up in parallel. it *should* work just fine however you rig it up, but i have not tested for example what would happen if two switches are pressed at once.
