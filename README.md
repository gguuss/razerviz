#Razer Keyboard Winamp Visualizer#

This is my attempt to create a Winamp visualization that works with
the Razer Deathstriker Ultimate keyboard.

It's based upon the [Tiny3D Winamp visualization](tiny3d) framework and 
is in a state where it is rather... unstable. The project renders
the graphic equalizer to the keyboard screen and has hooks for using
media keys to control Winamp.

##Usage##

###Playback###

  1. Copy RazerVizDemo.dll into your Winamp Plugins 
  2. Open Winamp
  3. Select Options -> Visualization -> Select Plugin
  4. Return to your media library and select a song before enabling the plugin
  5. Start playing back the song
  6. Cross your fingers
  7. Either press Ctrl+Shift+k or select Options -> Visualization -> Start / Stop Plugin

### Compiling ###

  1. Clone the project.
  2. Open the solution file, RazerVizDemo.sln, from the project folder.
  3. Make sure the project is set to release.
  3. Click the Build button or press Ctrl+Shift+B
  4. The project will compile and, if it builds successfully, the plugin will be copied to your winamp plugins directory.
  
### Troubleshooting ###
  1. If you're having trouble during the Linker steps, try this: Right click on the project -> Properties, select Configuration Properties -> Linker -> Input and set it to: `kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)`
  

Changes:
=========

**05.01.2014**

- Updated to skeleton project

**0.1**

Initial creation


[tiny3d]: https://github.com/icebreaker/tiny3d/
