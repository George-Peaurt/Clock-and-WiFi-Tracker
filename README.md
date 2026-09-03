An answer to a very specific problem I was having...

When I use my PC, I do not like having the taskbar up while I am doing activities, as I find it personally distracting. However, having it down means that I cannot tell the time, especially if I have my phone down elsewhere. Therefore, I made this ESP32 WiFi-connected Clock.

This project works by pulling from the NTP database and uses that time in synchronisation with the internal ESP32 clock to give me an accurate time. To reduce battery usage and to make sure the device is not getting too hot, it is updated every 10 seconds. Ensuring that the clock is always in time.

I plan to add a further feature, as I am quite interested in the WiFi functionality with a WiFi monitor, displaying the current uptime, ping, and upload / download speed.

Also, just an awesome low-power, small-scale clock that I plan on creating a shell for so I can stick it to the bottom of my monitor cool little gimmick.
