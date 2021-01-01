from network import WLAN
from network import LoRa
import binascii

print()

lora = LoRa()
print("Device EUI (LoRa): %s" % (binascii.hexlify(lora.mac()).decode('ascii')))

wl = WLAN()
print("Device EUI (WLAN): {}".format(binascii.hexlify(wl.mac()[0])[:6] + 'fffe' + binascii.hexlify(wl.mac()[0])[6:]))
