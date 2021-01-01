#!/usr/bin/env python
#
# Copyright (c) 2019, Pycom Limited.
#
# This software is licensed under the GNU GPL version 3 or any
# later version, with permitted additional terms. For more information
# see the Pycom Licence v1.0 document supplied with this file, or
# available at https://www.pycom.io/opensource/licensing
#

from network import LoRa
import socket
import binascii
import struct
import time
#import config

# for US915
LORA_FREQUENCY = 903900000 #canal 0
LORA_GW_DR = "SF7BW125" #"SF10BW125" # DR_0
LORA_NODE_DR = 3
# DR 0 igual que el nano-gw.
# DR 3 como el gw en RPi Zero (tutorial Adafruit)
# La tabla de valores se encuentra en la especificación
# "Regional Parameters" de LoRa Alliance

# initialize LoRa in LORAWAN mode.
# Please pick the region that matches where you are using the device:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Europe = LoRa.EU868
# United States = LoRa.US915
lora = LoRa(mode=LoRa.LORAWAN, region=LoRa.US915)

# create an ABP authentication params
dev_addr = struct.unpack(">l", binascii.unhexlify('26021F07'))[0]
nwk_swkey = binascii.unhexlify('D50035AADA10B55887711E2F58DCDCA5')
app_swkey = binascii.unhexlify('C591987ADED105268DBB564F4EDA4485')

# remove all the non-default channels
# default (3,16) algunos packets no se reciben
# si se remueven todos los canales (0,72) se reciben todos los packets
for i in range(0, 72): 
    lora.remove_channel(i)

# set the 3 default channels to the same frequency
# default dr_max = 5 genera error, valor maximo permitido 4
# no parece tener efecto en el envio de packets
lora.add_channel(0, frequency=LORA_FREQUENCY, dr_min=0, dr_max=4) #5
#lora.add_channel(1, frequency=LORA_FREQUENCY, dr_min=0, dr_max=4) #5
#lora.add_channel(2, frequency=LORA_FREQUENCY, dr_min=0, dr_max=4) #5

# join a network using ABP (Activation By Personalization)
lora.join(activation=LoRa.ABP, auth=(dev_addr, nwk_swkey, app_swkey))

# create a LoRa socket
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)

# set the LoRaWAN data rate
s.setsockopt(socket.SOL_LORA, socket.SO_DR, LORA_NODE_DR)

# make the socket non-blocking
s.setblocking(False)

for i in range (200):
    pkt = b'PKT #' + bytes([i])
    print('Sending:', pkt)
    s.send(pkt)
    time.sleep(5)
    rx, port = s.recvfrom(256)
    if rx:
        print('Received: {}, on port: {}'.format(rx, port))
    time.sleep(6)
