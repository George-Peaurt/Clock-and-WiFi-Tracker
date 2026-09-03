An answer to a very specific problem I was having...

When I use my PC, I do not like having the taskbar up while I am doing activities, as I find it personally distracting. However, having it down means that I cannot tell the time, especially if I have my phone down elsewhere. Therefore, I made this ESP32 WiFi-connected Clock.

This project pulls time from the NTP database and synchronises it with the internal ESP32 clock to provide accurate time. To reduce battery usage and to make sure the device is not getting too hot, it is updated every 10 seconds. Ensuring that the clock is always in time.

**03/09/26:**
  
Added further functionality with a timer when started up for the first time that tracks how long the clock has been on for since the last launch. This helps keep track of how long I have been on my computer for... good for when I know I need to touch grass.

Also centred the text for the clock and uptime, so much better.

**Proposed additions:**
  
Button to turn on a different mode: a timer. Where a button press increases the timer by 5 minutes, like a Pomodoro timer. Then press another button to accept. Would be a very interesting addition! some kind of speaker module to alert that the time is up.

3D printing a shell. Will use Fusion360 to make the design and then print. Very excited!
