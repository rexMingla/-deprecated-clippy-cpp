clippy
======

Introduction
------------

Most likely this is just a note to myself. If you are not me, welcome!

This is Clippy, a clipboard manager that is written in C++ Qt. The app runs out of the system tray and will also feature a global os 
hotkey to trigger it's menu. It is a work in progress, currently being tested on mac, with
the intention of targetting windows at a later point in time. **This is not ready for consumption yet, check back later when it's more polished.**

Background
----------

I really love clipMenu (http://www.clipmenu.com/). It's great for my mac development, but now I'm on windows for work and saw this as 
an opportunity to write my own. Obv, a solved problem, but seemed like a bit of fun. More details to come soon.

Dependencies
------------

* Qxt: Logging and shortcut key features have been pulled out the qxt lib. Don't worry- this is recommended on their wiki: http://dev.libqxt.org/libqxt/wiki/Home

> Qxt will likely not work with newer Qt versions due to usage of internal api. We recommend that you pick out the parts you want instead of using the entire libqxt.


