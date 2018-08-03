<table float="center">
  <tr>
    <td align="center" width=33%>
      <h1>v^SPEED Vario mini</h1>
      <h3><a href="https://www.ebay.com/usr/glydrfreak">Shop</a></h3>
      <h2>Contents:</h2>
      <a href="#about">About</a></br>
      <a href="#start-here">Start Here</a> </br>
      <a href="#custom-settings">Custom Settings</a></br>
      <a href="#bluetooth-operation">Bluetooth Operation</a> </br>
      <a href="#firmware-updates">Firmware Updates</a> </br>
    </td>
    <td>
      <img src="https://github.com/glydrfreak/vSpeed-Vario/blob/master/Images/vSpeedMini3D.JPG" width=350>
    </td>
    <td align="center" width=33%> 
      <h3>DIY Paragliding Variometer</h3>
      <img src="https://github.com/glydrfreak/vSpeed-Vario/blob/master/Images/logo.jpg" width=116> 
      <h6>(Vertical Speed Indicator)</h6>
    </td>
  </tr>
</table>


### ABOUT
This is an open source project, with all public files available at <a href="https://github.com/glydrfreak/vSpeed-Vario">the vSpeed-Vario repository</a>. The v^SPEED mini is based on PROTOTYPE6, which is found within that same repository. This variometer was designed to be compatible with the Arduino IDE for advanced usage, which allows users to modify the existing source code to their pleasure. Here, in the repository you are currently viewing, you will find the most up-to-date source code for use in the Arduino IDE. The hardware is based on another open source product: <a href="https://learn.adafruit.com/adafruit-feather-m0-bluefruit-le/downloads">Adafruit's Bluefruit Feather M0</a>. The v^SPEED mini is basically just a Bluefruit Feather M0 development board, but without the header pins broken out, and with the added variometer circuitry.

<table>
  <tr>
    <td width=33% vAlign="top" align="center">
      <h2>v^SPEED VARIO mini</h2>
      <h3>$99</h3>
      <img src="https://github.com/glydrfreak/vSpeed-Vario/blob/master/Images/vspeedMini2.jpg" width=250>
      <h2><a href="https://www.ebay.com/usr/glydrfreak">BUY NOW</a></h2></br>
    </td>
    <td width=66%> 
      <ul>
        <h3>SPECS:</h3>
        <li>Ultra-high precision barometric pressure sensor detects altitude changes as small as 10cm</li>
        <li>Lowest priced Bluetooth Variometer on the market</li>
        <li>iPhone users: Fully compatible with <a href="#flyskyhy">FlySkyHy</a> app</li>
        <li>Android users: <a href="#vspeed-vario">v^SPEED</a> app new in Google Play Store</li>
        <li>Fully compatiple with Arduino IDE to easily change custom settings</li>
          (Micro USB cable included)
        <li>Mounts on risers with velcro</li>
          (Leash, and velcro for both riser and vario included)
        <li>Tiny Size: 68x25x10mm (about the size of a man's thumb)</li>
        <li>3D printed cover screws onto circuit board </li>
          (Comes in black, or upon special request, White, yellow, or light blue)
        <li>Power switch, and volume buttons</li>
        <li>150mAh lipo battery with microUSB charging port</li>
        <li>10hr battery life while streaming bluetooth data</li>
        <li>1.5hr charging time</li>
        <li>Sale price: $99 each (subject to change)</li>
      </ul>
    </td>
  </tr>
</table>


### START HERE
#### Congrats on receiving your new v^SPEED Vario mini!
- Install <a href="https://www.arduino.cc/en/Main/Software">Arduino IDE</a>
- Download and extract the <a href="https://github.com/glydrfreak/vSpeedVario-mini/archive/master.zip" raw=true>files</a> in this repository
- Open the `vSpeed_mini.ino` file, which should open with the Arduino IDE
- Tools -> Boards Manager -> Search for: Arduino SAMD Boards -> Install
- Tools -> Boards Manager -> Search for: Adafruit SAMD Boards -> Install
- Tools -> Board -> Select: Adafruit Feather M0
- Connect your v^SPEED mini to your computer
  - The vario must be switched on
  - The usb cable must not be a "charge only" cable
- Tools -> Port -> Select any port for now
- Sketch -> Upload
- Anytime you power on your vario, or upload a new sketch, you will hear two sequences of beeps:
  - The first beep(s) indicates the bluetooth mode.
    - No beep: Bluetooth disabled
    - One beep: Android mode
    - Two beeps: iPhone mode
  - The second series of beeps indicates the battery level.
    - Ascending: Battery is at least 66%
    - Steady: Battery is at least 33%
    - Descending: Battery is below 33%
- <b>You're ready to fly!</b>


### CUSTOM SETTINGS
- Open the `vSpeed_mini.ino` file, which should open with the Arduino IDE
- Open the `DEFAULT_SETTINGS.h` tab
- Change any of the following values according to your preference:
  - `ENABLE_BEEP`= <b>1</b>; [1]YES, [0]NO
  - `START_UP_VOLUME`= <b>10</b>; (0 TO 31)
  - `BEEP_TYPE`= <b>1</b>; Default [1]BASED_ON_VELOCITY, [2]BUFFERED_INCREMENTS (Experimental)
  - `CLIMB_BEEP_TRIGGER`= <b>1.0</b>; (Default: One beep for every 1.0 foot of altitude increase)
  - `SINK_BEEP_TRIGGER`= <b>-1.0</b>; (Default: Constant beep if sinking more than -1.0 ft/s)
  - `CLIMB_PITCH_MAX`= <b>600.0</b>; (Default: 600.0 Hz when climbing at ten ft/s)
  - `CLIMB_PITCH_MIN`= <b>400.0</b>; (Default: 400.0 Hz when climbing at one ft/s)
  - `SINK_PITCH_MAX`= <b>250.0</b>; (Default: 250.0 Hz when sinking at `SINK_BEEP_TRIGGER` ft/s)
  - `SINK_PITCH_MIN`= <b>150.0</b>; (Default: 150.0 Hz when sinking at ten ft/s less than `SINK_BEEP_TRIGGER` ft/s)
  - `MEASURE_BATTERY`= <b>1</b>; [1]YES, [0]NO
  - `BLUETOOTH_MODE`= <b>0</b>; Default [0]DISABLE, [1]VSPEED_ANDROID, [2]FLYSKYHY_IOS
  - `ALTITUDE_UNITS`= <b>1</b>; Default [1]FEET, [2]METERS
  - `VELOCITY_UNITS`= <b>1</b>; Default [1]FEET_PER_SECOND, [2]METERS_PER_SECOND, [3] FEET_PER_MINUTE
- Tools -> Board -> Select: Adafruit Feather M0
- Connect your v^SPEED mini to your computer
  - The vario must be switched on
  - The usb cable must not be a "charge only" cable
- Tools -> Port -> Select the correct port
- Sketch -> Upload


### BLUETOOTH OPERATION
- v^SPEED mini is compatible with both Android and iPhone.
- You may change the bluetooth mode at startup:
  - Hold the volume down button while powering on the vario until it beeps to boot up into Android mode.
    - After two minutes of no connection, the bluetooth transmission will be disabled to preserve battery and sample rate.
  - Hold the volume up button while powering on the vario until it beeps to boot up into iPhone mode.
  - If no volume buttons are held down at startup, the default will be to disable the bluetooth transmission.
    - You may change the default startup bluetooth mode by changing the `BLUETOOTH_START_UP_MODE` in `DEFAULT_SETTINGS.h` so you don't need to hold down a volume button each time you switch on the vario.

#### Android Users--
- Download the <a href="https://play.google.com/store/apps/details?id=com.braedin.butler.vspeed.vario&hl=en_US">v^SPEED Vario app</a> from Google Play Store.
<table>
  <tr>
    <td width=33% vAlign="top" align="center">
      <h2>v^SPEED Vario</h2>
      <img src="https://github.com/glydrfreak/vSpeed-Vario/blob/master/Images/ANDROID.png" width=250>
    </td>
    <td width="66%"> 
      <ul>
        <h3>Android App--</h3>
        This is a modified version of Adafruit's open source "Bluefruit LE Connect" for Android. The source code can be found in the Android folder of <a href="https://github.com/glydrfreak/vSpeed-Vario">the vSpeed-Vario repository</a>. Now published to Google Play! </br>
  </br>
        This app will give you a better image of what your v^SPEED Vario is doing as it transmits live bluetooth data of barometric altitude, vertical speed, and battery level. Other features include implemented GPS for GPS altitude, ground speed, and heading. The implemented Audio beeps are helpful for listening to each foot of climb as well as a variable sink tone. An implemented accelerometer is for keeping track of max G-force during a hard turn or spiral. The visual display includes a line chart of vertical speed, as well as scrolling altitude numbers so you can see your precise vertical velocity. The climb and sink thresholds are adjustable within the app, which also change the thresholds on the external vario automatically.
      </ul>
    </td>
  </tr>
</table>

#### iPhone Users--
- Download <a href="https://itunes.apple.com/us/app/flyskyhy/id516879039?mt=8">Flyskyhy</a> from the App Store.
- While selecting the external vario model, choose `Skydrop` for the time being.
<table>
  <tr>
    <td width=33% vAlign="top" align="center">
      <h2>Flyskyhy</h2>
      <img src="https://github.com/glydrfreak/vSpeed-Vario/blob/master/Images/fsh2.jpg" width=250>
    </td>
    <td width=66%> 
      <ul>
        <h3>iOS App by Renevision--</h3>
        v^SPEED Vario is now compatible with the World's most popular Paragliding app! Flyskyhy is an unbeatable iPhone application when it comes to flying. v^Speed Vario is currently using the same protocol as SkyDrop variometers, so in the app when selecting your device, you must choose SkyDrop for the time being.  
      </ul>
    </td>
  </tr>
</table>


### FIRMWARE UPDATES
#### Source code last updated: `8/2/2018`
- For the most up-to-date source code for your v^SPEED mini, download and extract the <a href="https://github.com/glydrfreak/vSpeedVario-mini/archive/master.zip" raw=true>files</a> in this repository and replace the existing files in your `vSpeed_mini` folder. 
- You may want to keep your existing `DEFAULT_SETTINGS.h` file if you have made changes to it.
- To see the most recent date that your existing code was updated, see the first line of code in `vSpeed_mini.ino`.
- a `changeLog.txt` is provided in the `vSpeed_mini` folder.


### QUESTIONS / CONCERNS / ASSISTANCE
Email vSpeedVario@gmail.com </br>
