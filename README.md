ColourfulDanceCtl
----
arduino Joystick library code for any sort of controller using analogue switches & three-wire WS2812B LEDs.  
intended for dance game usage at 1000hz, using original, stock arcade tape switches (aka "sensors") & per-panel colour profile support via FastLED.

credit to [dominickp](https://github.com/dominickp) for his [original FastLED implementation](https://github.com/teejusb/fsr/compare/master...dominickp:dom-fastled-lights) amended to [teejusb's fsr repo.](https://github.com/teejusb/fsr)  
credit to [nato](https://github.com/Natologic) for both [restructuring the PANEL-LED array to support 3-wire WS2812B LEDs & writing the "setColors" functions.](https://github.com/Natologic/metalTravelPad)  
credit to [StarlightLumi](https://github.com/StarlightLumi) for [the original DanceCtl+lights implementation.](https://github.com/StarlightLumi/DanceCtl)


features
----
- works with any kind of analogue switch-based controller you may build
- supports as many buttons as you can fit on your arduino
- supports as many lights per button as you want
- polls at 1000hz
- made of cheap ass arduino hardware - tested working on a $10 pro micro
- comes with an uncommented version for speed demons, & a heavily commented version for those looking to learn


/!\ DISCLAIMER /!\
----
this code **has *NOT* been tested on a real pad/controller yet!!** it has only been extensively "breadboard" tested using a single sanwa obsf pushbutton in place of switches hooked up in parallel. it *should* work just fine however you rig it up, but i have not tested for example what would happen if two switches are pressed at once.
