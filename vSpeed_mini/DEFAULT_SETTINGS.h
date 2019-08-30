/**
 * FEEL FREE TO CHANGE ANY OF THE VALUES BELOW TO YOUR PREFERENCE.
 */


#ifndef DEFAULT_SETTINGS_H
#define DEFAULT_SETTINGS_H

class Default{
  public:
  
    bool ENABLE_CLIMB_BEEP           = 1;    // [1]YES, [0]NO
    bool ENABLE_SINK_BEEP            = 0;    // [1]YES, [0]NO
    bool ENABLE_SINK_ALARM           = 1;    // [1]YES, [0]NO
    int START_UP_VOLUME             = 10;    // Default 10 (0 to 31)
    int BEEP_TYPE                    = 1;    // DEFAULT [1]BASED_ON_VELOCITY, [2]BUFFERED_INCREMENTS
    
    float CLIMB_BEEP_TRIGGER       = 1.0;    // (Default 1.0 ft)
    float SINK_BEEP_TRIGGER       = -1.0;    // (Default -1.0 ft/s)
    float SINK_ALARM_TRIGGER     = -20.0;    // (Default -20.0 ft/s)

    float CLIMB_PITCH_MAX        = 600.0;    // (Default 600.0 Hz)
    float CLIMB_PITCH_MIN        = 400.0;    // (Default 400.0 Hz)
    
    float SINK_PITCH_MAX         = 250.0;    // (Default 250.0 Hz)
    float SINK_PITCH_MIN         = 150.0;    // (Default 150.0 Hz)
    float SINK_ALARM_PITCH      = 1000.0;    // (Default 1000.0 Hz)

    int BLUETOOTH_MODE               = 2;    // [0]DISABLE, [1]VSPEED_ANDROID, [2]FLYSKYHY_IOS, [3]XCTRACK_ANDROID

    int ALTITUDE_UNITS               = 1;    // [1]FEET, [2]METERS
    int VELOCITY_UNITS               = 1;    // [1]FEET_PER_SECOND, [2]METERS_PER_SECOND, [3]FEET_PER_MINUTE
};
    
#endif

