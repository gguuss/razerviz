#Razer Keyboard Winamp Visualizer#

This is my attempt to create a Winamp visualization that works with
the Razer Deathstriker Ultimate keyboard.

It's based upon the [Tiny3D Winamp visualization](tiny3d) framework and
is in a state where it is rather... unstable. The project renders
the graphic equalizer to the keyboard screen and has hooks for using
media keys to control Winamp.

See the demo in action: 
- http://youtu.be/ivSlJcQnS0o 
- http://youtu.be/bgFM_8KSgmM
- http://youtu.be/Z_O2et62Ivo
- http://youtu.be/3S0_FtytXCk

##Usage##

###Playback###
I'm not certain of this but you most likely will need to have the Razer SwitchBlade SDK
to begin. Please comment if the plugin works for you without the SDK.

**Warning** This plugin will invariably crash Winamp and is tempermental. Learn how
to recover WinAmp by removing plugins or setting Winamp to safe mode before you try
running the plugin.

  1. Copy RazerVizDemo.dll into your Winamp Plugins
  2. Open Winamp
  3. Select Options -> Visualization -> Select Plugin
  4. Return to your media library and select a song before enabling the plugin
  5. Start playing back the song
  6. Cross your fingers
  7. Either press Ctrl+Shift+k or select Options -> Visualization -> Start / Stop Plugin

### Compiling ###

#### Prerequisites ####
1. Register for the Razer developer program here:
    http://developer.razerzone.com/forum/register.php
2. Download the SDK from here:
    http://developer.razerzone.com/forum/showthread.php?12-Razer-SDK-download
3. Put the following binaries in the local ./lib directory from the SDK lib folder:
    RzSwitchbladeSDK2.lib
4. Put the following binaries in the local ./include directory from the SDK include folder:
    - SwitchBlade.h
    - SwitchBladeSdk.h
    - SwitchBladeSdk_defines.h
    - SwitchBladeSdk_errors.h
    - SwitchBladeSdk_types.h

#### Build steps ####

  1. Clone the project.
  2. Open the solution file, RazerVizDemo.sln, from the project folder.
  3. Make sure the project is set to release.
  3. Click the Build button or press Ctrl+Shift+B
  4. The project will compile and, if it builds successfully, the plugin will be copied to your winamp plugins directory.

#### Troubleshooting ####
  1. If you're having trouble during the Linker steps, try this: Right click on the project -> Properties, select Configuration Properties -> Linker -> Input and set it to: `kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)`


Changes:
=========
**05.07.2014**
Check out the experimental branch. Now testing out more granular visualization bars as well as tri-color gradients.

**05.04.2014**
- Determined wasn't allocating sufficient memory for track shifts, fixed!
- Added debug color spectrums for visualizer above viz loop
- DK1 through DK5 (the LCD keys on the bottom) switch plugin colors
- [See YouTube demo of keyboard / trackpad working](YTDemo3)

**05.01.2014**

- Updated to skeleton project

**0.1**

Initial creation


[tiny3d]: https://github.com/icebreaker/tiny3d/
[YTDemo3]: http://youtu.be/3S0_FtytXCk
