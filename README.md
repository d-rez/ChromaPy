# ChromaPy

ChromaPy is a small ChromaSDK Extension for Python[Windows].

Usage
--------
As simple as 
```
import ChromaPy as Chroma

RED = (255,0,0)

Chroma.setColor(RED) 
```
For further information take a look at the wiki of this repo. You can also find multiple examples in the "Example Script"-directory.

Supported Devices
--------
Razer devices:
* Keyboard
* Keypad
* Mouse
* Mousepad
* Headset
* Systems

Building
--------

To compile it by your own don't forget to include the "include\" and the "libs\" directories of your Python Instance.

A compiled version of ChromaPy for Python 3.6 can be found on the official [Insider thread][insider].

Dependencies
------------

ChromaPy depends on the "Razer Chroma SDK".

The "Razer Chroma SDK" is provided by Razer and can be found on their [Website][rzdev].

License
-------

Copyright &copy; 2017 by [Tim Gebauer][vaypron].
Patching, updating and picking cherries by [d-rez][d-rez]


This project is licensed under the MIT license, please see the file **LICENSE** for more information.


Razer is a trademark and/or a registered trademark of Razer USA Ltd.  
All other trademarks are property of their respective owners.


[vaypron]: https://github.com/Vaypron
[d-rez]: https://github.com/d-rez
[rzdev]: http://developer.razerzone.com/chroma
[mit]: https://github.com/nlohmann/json/blob/develop/LICENSE.MIT
[insider]: https://insider.razerzone.com/index.php?threads/beta-release-chromapy-python-extension-for-the-chroma-sdk-windows.18938
