# GrowLightSensor
Created by Claudio Filho - Silicon Labs Staff FAE

I have been growing tomatoes from seeds and was trying to figure out which areas of my backyard would be the best to plant those tomatoes, given they like a lot of sun. So I have put this code together and thrown a couple of our Thunderboard Sense 2 dev boards on the backyard for a couple of days and figured out which areas effectively had more sun exposure.

I have used the Thunderboard Sense 2 Ambient Light and UV sensor (si1133) as the main source of data for this logger.

You can probe the UV Index characteristic (acaa4c6d-b154-4ec6-b082-0b55bb5a82b0) and Ambient Light characteristic (4d69ffd8-60fe-4cbf-9813-87fe126f4c92) on demand. I have also implemented a time service that allows you to setup the time. In order to use the Logging feature, the characteristic TriggerALS (77520c17-a015-40d3-939b-790699e3812a) needs to be written with 0x01 in order to trigger periodic measurements. The default is one measurement every 15min, for 12h and then in order to retrieve the data you need to look at BulkAls (2f44a9e6-6d42-4076-aa24-a962d2f3439c) and BulkUv(2f44a9e6-6d42-4076-aa24-a962d2f343aa), whenever those bulk measurements are read, the logging stops. There is also the startHour(9225bbf7-2762-4cf8-b447-e09ef14c9552) and startMinute (9225bbf7-2762-4cf8-b447-e09ef14c9553) characteristics that will store the initial measurement time.

I have also added a python script called sensorOutput.py, that will look at data.txt and parse the ALSdata that has to be manually added (using BGtool and an EFR32 as a NCP to read the Bulk Characteristics).

Bugs/Improvements:

- Power usage is relatively high (50uA), need to figure out why it is that high
- I want to use the Log Service characteristics in order to set how often and how long we are logging the data
- The data is being saved on RAM, I want to be able to use the SPI flash available on the TBs2 in case something happens


Tools and SDKs:

This was tested with:

Silicon Labs Bluetooth Stack 2.13.5.0

GNU GCC Compiler: arm-none-eabi-gcc GNU ARM 7.2.1

Development Board: Silicon Labs Thunderboard Sense 2

Usage:

Please clone this to where your Simplicity Studio Workspace is located.

Then to import it, please do:

File -> Import -> More Import Options -> General -> Existing Projects Into Workspace -> Select Workspace directory -> Select Project -> Finish
