#  Raspberry Pi Master for Arduino Slave
#  i2c_master_pi.py
#  Connects to Arduino via I2C

#  DroneBot Workshop 2019
#  https://dronebotworkshop.com

from smbus import SMBus

addr = 0x8 # bus address
bus = SMBus(1) # indicates /dev/ic2-1

numb = 1

print ("Enter 1 for ON or 0 for OFF, 2 to read the last value")
while numb == 1:
        ledstate = input(">>>>   ")
        if ledstate == "1":
                bus.write_byte(addr, 1) # switch it ON
        elif ledstate == "0":
                bus.write_byte(addr, 0) # switch it OFF
        elif ledstate == "2":
                b = bus.read_byte(addr)
                print (b)
        else:
                numb = 0