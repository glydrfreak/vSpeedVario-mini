<table float="center">
  <tr>
    <td align="center" width=50%>
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
      <img src="https://github.com/glydrfreak/vSpeed-Vario/blob/master/Images/vspeedMini2.jpg" width=250>
    </td>
    <td align="center"> 
      <h3>DIY Paragliding Variometer</h3>
      <img src="https://github.com/glydrfreak/vSpeed-Vario/blob/master/Images/logo.jpg" width=116> 
      <h6>(Vertical Speed Indicator)</h6>
    </td>
  </tr>
</table>


### ABOUT
This is an open source project, with all public files available at <a href="https://github.com/glydrfreak/vSpeed-Vario">the vSpeed-Vario repository</a>. The v^SPEED mini is based on PROTOTYPE6, which is found within that same repository. This variometer was designed to be compatible with the Arduino IDE for advanced usage, which allows users to modify the existing source to their pleasure. Here, in the repository you are currently viewing, you will find the most up-to-date source code for use in the Arduino IDE. The hardware is based on another open source product: <a href="https://learn.adafruit.com/adafruit-feather-m0-bluefruit-le/downloads">Adafruit's Bluefruit Feather M0</a>. The v^SPEED mini is basically just a Bluefruit Feather M0 development board, but without the header pins broken out, and with the added variometer circuitry.


### START HERE
#### Congrats on receiving your new v^SPEED Vario mini!
- Install Arduino IDE
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
    - Ascending: Battery is at least 75%
    - Steady: Battery is at least 50%
    - Descending: Battery is below 25%


### CUSTOM SETTINGS
- Open the `vSpeed_mini.ino` file
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
  - `SINK_PITCH_MIN`= <b>150.0</b>; (Default: 150.0 Hz when sinking at negative ten ft/s)
  - `MEASURE_BATTERY`= <b>1</b>; [1]YES, [0]NO
  - `ENABLE_BLUETOOTH`= <b>1</b>; [1]YES, [0]NO
  - `START_UP_BLUETOOTH_MODE`= <b>0</b>; Default [0]DISABLE, [1]VSPEED_ANDROID, [2]FLYSKYHY_IOS
- Tools -> Board -> Select: Adafruit Feather M0
- Connect your v^SPEED mini to your computer
- Tools -> Port -> Select the correct port
- Sketch -> Upload


### BLUETOOTH OPERATION
- v^SPEED mini is compatible with both Android and iPhone.
- You may change the bluetooth mode at startup:
  - Hold the volume down button while powering on the vario to boot up into Android mode.
    - After two minutes of no connection, the bluetooth transmission will be disabled to preserve battery and sample rate.
  - Hold the volume up button while powering on the vario to boot up into iPhone mode.
  - If no volume buttons are held down at startup, the default will be to disable the bluetooth transmission.
    - You may change the default startup bluetooth mode by changing the `BLUETOOTH_START_UP_MODE` in `DEFAULT_SETTINGS.h`.
#### Android Users--
- Download the v^SPEED Vario app from Google Play Store.
#### iPhone Users--
- Download Flyskyhy from the App Store.
- While selecting the external vario model, choose `Skydrop` for the time being.


### FIRMWARE UPDATES
#### Source code last updated: `5/11/2018`
- For the most up-to-date source code for your v^SPEED mini, download and extract the files in this repository and replace the existing files in your `vSpeed_mini` folder. 
- You may want to keep your existing `DEFAULT_SETTINGS.h` file if you have made changes to it.
- To see the most recent date that your existing code was updated, see the first line of code in `vSpeed_mini.ino`.
- a `changeLog.txt` is provided in the `vSpeed_mini` folder.
