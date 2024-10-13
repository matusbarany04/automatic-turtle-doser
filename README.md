AUTOMATIC TURTLE FEEDER
=========================
- 12-day worry free feeding for your turtle 
- able to edit feed time and current time
- settings for configuring alignment in case of offset error

<!-- ![turtle](/_images/turtle.jpg) -->
<img src="./_images/turtle.jpg" width="350" title="Very happy turtle">

## Loading the feeder 
This is how almost fully loaded feeder looks like 

![doser loaded](/_images/doser_loaded.jpg)


## Display with menu 
Display in the back with menu alloww for simple configuration
![display](/_images/display.jpg)


### How to build PlatformIO based project

1. [Install PlatformIO Core](https://docs.platformio.org/page/core.html)
2. Download [development platform with examples](https://github.com/platformio/platform-raspberrypi/archive/develop.zip)
3. Extract ZIP archive
4. Run these commands:

```shell
# Change directory to example
$ cd platform-raspberrypi/examples/arduino-blink

# Build project
$ pio run

# Upload firmware
$ pio run --target upload

# Clean build files
$ pio run --target clean
```
