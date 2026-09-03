An answer to a very specific problem I was having...

When I use my PC, I do not like having the taskbar up while I am doing activities, as I find it personally distracting. However, having it down means that I cannot tell the time, especially if I have my phone down elsewhere. Therefore, I made this ESP32 WiFi-connected Clock.

This project pulls time from the NTP database and synchronises it with the internal ESP32 clock to provide accurate time. To reduce battery usage and to make sure the device is not getting too hot, it is updated every 10 seconds. Ensuring that the clock is always in time.

**03/09/26:**
  
Added further functionality with a timer when started up for the first time that tracks how long the clock has been on for since the last launch. This helps keep track of how long I have been on my computer for... good for when I know I need to touch grass.

Also centred the text for the clock and uptime, so much better.

**Proposed additions:**
  
Button to turn off the display; it will still keep counting. When pressed again, it will turn the display back on.
Another button to cycle different clock fronts, from the current size to just the clock or a larger size. I have not decided on this feature yet!
