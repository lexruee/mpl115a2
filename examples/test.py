import time
from tentacle_pi.MPL115A2 import MPL115A2
mpl = MPL115A2(0x60,"/dev/i2c-2")

for x in range(0,10):
    temperature, pressure = mpl.temperature(), mpl.pressure()
    print "temperature: %0.1f" % temperature
    print "pressure: %0.1f" % pressure
    print
    time.sleep(2)
