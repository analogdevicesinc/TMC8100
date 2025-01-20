################################################################################
# Copyright © 2024 Analog Devices Inc. All Rights Reserved.
# This software is proprietary to Analog Devices, Inc. and its licensors.
################################################################################

#!/usr/bin/env python3

from tkinter import *
import tkinter as tk
import re
from tkinter.font import Font
from tkinter import messagebox
from tkinter import filedialog
import time
import serial
from intelhex import IntelHex

import random
import math

def open_port(index):
    ser.baudrate = 115200
    ser.port = str(ports[index]).split()[0]
    ser.open()

def GetVersion():
    ser.write(b"\x01\x88\x00\x00\x00\x00\x00\x00\x89")
    reply = ser.read(9)
    print(f"LB version string: {reply[1:8]}")
    
def SpiReadCommand(spi_data):
    # use UFDRV 1,0,<spi_data> command
    # write
    data = b"\x01\x91\x01\x00"
    data += bytes([spi_data[0]])
    data += bytes([spi_data[1]])
    data += bytes([spi_data[2]])
    data += bytes([spi_data[3]])
    checksum = (0x01 + 0x91 + +0x01 + spi_data[0] + spi_data[1] + spi_data[2] + spi_data[3]) & 0xff
    data += bytes([checksum])
    #print(f"Command: {data[0]:02x} {data[1]:02x} {data[2]:02x} {data[3]:02x} {data[4]:02x} {data[5]:02x} {data[6]:02x} {data[7]:02x} {data[8]:02x}")
    ser.write(data)
    # read
    reply = ser.read(9)
    #print(f"Reply: {reply[0]:02x} {reply[1]:02x} {reply[2]:02x} {reply[3]:02x} {reply[4]:02x} {reply[5]:02x} {reply[6]:02x} {reply[7]:02x} {reply[8]:02x}")
    return [reply[4], reply[5], reply[6], reply[7]] # return 32bit data from 
    
def SpiWriteCommand(spi_data):
    # use UFDRV 0,0,<spi_data> command
    # write
    data = b"\x01\x91\x00\x00"
    data += bytes([spi_data[0]])
    data += bytes([spi_data[1]])
    data += bytes([spi_data[2]])
    data += bytes([spi_data[3]])
    checksum = (0x01 + 0x91 + +0x00 + spi_data[0] + spi_data[1] + spi_data[2] + spi_data[3]) & 0xff
    data += bytes([checksum])
    #print(f"Command: {data[0]:02x} {data[1]:02x} {data[2]:02x} {data[3]:02x} {data[4]:02x} {data[5]:02x} {data[6]:02x} {data[7]:02x} {data[8]:02x}")
    ser.write(data)
    # read
    reply = ser.read(9)
    #print(f"Reply: {reply[0]:02x} {reply[1]:02x} {reply[2]:02x} {reply[3]:02x} {reply[4]:02x} {reply[5]:02x} {reply[6]:02x} {reply[7]:02x} {reply[8]:02x}")
    return [reply[4], reply[5], reply[6], reply[7]] # return 32bit data from 

def SetReset(level):
    # use UFDRV 3/4,0,0 command
    # write
    data = b"\x01\x91"
    checksum = 0x01+0x91
    if level == 0:
        data += b"\x03"
        checksum += 0x03
    else:
        data += b"\x04"
        checksum += 0x04
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += bytes([checksum])
    #print(f"Command: {data[0]:02x} {data[1]:02x} {data[2]:02x} {data[3]:02x} {data[4]:02x} {data[5]:02x} {data[6]:02x} {data[7]:02x} {data[8]:02x}")
    ser.write(data)
    # read
    reply = ser.read(9)
    #print(f"Reply: {reply[0]:02x} {reply[1]:02x} {reply[2]:02x} {reply[3]:02x} {reply[4]:02x} {reply[5]:02x} {reply[6]:02x} {reply[7]:02x} {reply[8]:02x}")
    return [reply[4], reply[5], reply[6], reply[7]]

def WaitForGPIO6():
    # use UFDRV 2,0,0 command
    # write
    data = b"\x01\x91\x02\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x94" # checksum
    #print(f"Command: {data[0]:02x} {data[1]:02x} {data[2]:02x} {data[3]:02x} {data[4]:02x} {data[5]:02x} {data[6]:02x} {data[7]:02x} {data[8]:02x}")
    result = 0
    while result == 0:
        ser.write(data)
        # read
        reply = ser.read(9)
        # print(f"Reply: {reply[0]:02x} {reply[1]:02x} {reply[2]:02x} {reply[3]:02x} {reply[4]:02x} {reply[5]:02x} {reply[6]:02x} {reply[7]:02x} {reply[8]:02x}")
        result = reply[7]
    # print(f"Reply: {reply[0]:02x} {reply[1]:02x} {reply[2]:02x} {reply[3]:02x} {reply[4]:02x} {reply[5]:02x} {reply[6]:02x} {reply[7]:02x} {reply[8]:02x}")
    #return [reply[4], reply[5], reply[6], reply[7]]
    return
    
def GetGPIO6():
    # use UFDRV 2,0,0 command
    # write
    data = b"\x01\x91\x02\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x94" # checksum
    ser.write(data)
    # read
    reply = ser.read(9)
    return reply[7]

def SetI2C(level):
    # use UFDRV 5/6,0,0 command
    # write
    data = b"\x01\x91"
    checksum = 0x01+0x91
    if level == 0:
        data += b"\x05"
        checksum += 0x05
    else:
        data += b"\x06"
        checksum += 0x06
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += bytes([checksum])
    #print(f"Command: {data[0]:02x} {data[1]:02x} {data[2]:02x} {data[3]:02x} {data[4]:02x} {data[5]:02x} {data[6]:02x} {data[7]:02x} {data[8]:02x}")
    ser.write(data)
    # read
    reply = ser.read(9)
    #print(f"Reply: {reply[0]:02x} {reply[1]:02x} {reply[2]:02x} {reply[3]:02x} {reply[4]:02x} {reply[5]:02x} {reply[6]:02x} {reply[7]:02x} {reply[8]:02x}")
    return [reply[4], reply[5], reply[6], reply[7]]

def SetUART(level):
    # use UFDRV 5/6,0,0 command
    # write
    data = b"\x01\x91"
    checksum = 0x01+0x91
    if level == 0:
        data += b"\x07"
        checksum += 0x07
    else:
        data += b"\x08"
        checksum += 0x08
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += b"\x00"
    data += bytes([checksum])
    #print(f"Command: {data[0]:02x} {data[1]:02x} {data[2]:02x} {data[3]:02x} {data[4]:02x} {data[5]:02x} {data[6]:02x} {data[7]:02x} {data[8]:02x}")
    ser.write(data)
    # read
    reply = ser.read(9)
    #print(f"Reply: {reply[0]:02x} {reply[1]:02x} {reply[2]:02x} {reply[3]:02x} {reply[4]:02x} {reply[5]:02x} {reply[6]:02x} {reply[7]:02x} {reply[8]:02x}")
    return [reply[4], reply[5], reply[6], reply[7]]

def close_port():
    ser.close()

ser = serial.Serial()

# COM port select box
import serial.tools.list_ports
ports = serial.tools.list_ports.comports()
number_of_ports = len(ports)

# select port
print("Available ports:")
port_index = 0
while port_index < number_of_ports:
    print(str(port_index) + " - " + str(ports[port_index]))
    port_index += 1
selection = input("Select port: ")
port_index = int(selection)
open_port(port_index)

GetVersion()
#SpiCommand([0x01, 0x02, 0x03, 0x04])


win = tk.Tk()
win.title("TMC8100-EVAL Tamagawa T-Format Demo")
logo = PhotoImage(file="pelican.png")
win.tk.call('wm', 'iconphoto', win._w, logo)


##
## spi get bootloader version
##

def spi_get_bootloader_version():
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    value = SpiReadCommand([0x00, 0x00, 0x00, 0x00])
    print(f"TMC8100 bootloader version: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")

##
## spi get chip id
##

def spi_get_chip_id():
    value = SpiWriteCommand([0xb0, 0x00, 0x00, 0x00])
    value = SpiReadCommand([0xb0, 0x00, 0x00, 0x00])
    print(f"TMC8100 chip ID: {value[0]:c} {value[1]:c} {value[2]:c} {value[3]:c}")

##
## spi get chip revision
##

def spi_get_chip_revision():
    value = SpiWriteCommand([0xb8, 0x00, 0x00, 0x00])
    value = SpiReadCommand([0xb8, 0x00, 0x00, 0x00])
    print(f"TMC8100 chip revision: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")

print("** Reset TMC8100 **")
SetReset(0x00)
SetI2C(0x00)
SetReset(0x01)
spi_get_bootloader_version()
spi_get_chip_id()
spi_get_chip_revision()
 
def spi_select_file():
    file_path = tk.filedialog.askopenfilename(title="Open HEX file", filetypes=(("hex files","*.hex"),("All files","*.*")), initialdir=".")
    file_path_text.set(file_path)

def spi_load_exec_file():
    # reset TMC8100
    print("** Reset TMC8100 **")
    SetReset(0x00)
    SetReset(0x01)
    spi_get_chip_id()
    time.sleep(0.1)
    # load file
    hexFile = IntelHex()
    hexFile.fromfile(file_path_text.get(),format='hex')
    startAddr = hexFile.minaddr()
    endAddr = hexFile.maxaddr()
    print("Loading Hex File: " + file_path_text.get())
    print(f"Start Address: 0x{startAddr:04x}, End Address: 0x{endAddr:04x}, Size: " + str(endAddr - startAddr + 1) + " Bytes")
    #print(hex(hexFile[0]) + " " + hex(hexFile[1]))
    lbl_load_file_status.configure(text="File loaded", bg="green")
    # download to TM02
    print("Downloading Hex File ...")
    address = startAddr
    index = startAddr
    while address < endAddr:
        address_low = address & 0xff
        address_high = (address >> 8) & 0x07
        address_high += 0x08
        data_low = hexFile[index]
        index += 1
        data_high = hexFile[index]
        index += 1
        SpiWriteCommand([address_high, address_low, data_high, data_low])
        address += 1
    # verify download
    print("Verification ...")
    address = startAddr
    address_low = address & 0xff
    address_high = (address >> 8) & 0x07
    address_high += 0x88
    index = address
    address_last = address
    while address < endAddr:
        address_low = address & 0xff
        address_high = (address >> 8) & 0x07
        address_high += 0x88
        data_low = hexFile[index]
        index += 1
        data_high = hexFile[index]
        index += 1
        value = SpiReadCommand([address_high, address_low, 0x00, 0x00])
        if (data_high != value[2]) or (data_low != value[3]):
            print(f"ERROR @address 0x{address_last:04x}: expected: 0x{data_high:02x}{data_low:02x}, read-out: 0x{value[2]:02x}{value[3]:02x})")
            return
        address_last = address
        address += 1
    print("Verification successful: contents of program memory and hex-file are equal!")
    print("Start program in TMC8100 program memory ...")
    SpiWriteCommand([0x10, 0x00, 0x00, 0x00])

fm_file_select = tk.LabelFrame(text="Select Input File")
file_path_text = tk.StringVar()
ent_file_path = tk.Entry(master=fm_file_select, textvariable=file_path_text, width=80); ent_file_path.grid(row = 0, column = 1)
btn_select_file = tk.Button(fm_file_select, text="...", command=spi_select_file); btn_select_file.grid(row = 0,column = 2)
btn_load_exec_file = tk.Button(fm_file_select, text="Load + Execute", command=spi_load_exec_file); btn_load_exec_file.grid(row = 0,column = 3)
lbl_load_file_status = tk.Label(fm_file_select, text="No File", bg="red", fg="white"); lbl_load_file_status.grid(row = 0,column = 4, padx = 10, pady = 10)

# ABS value
def spi_tamagawa_id0():
    # get ABS value
    value = SpiWriteCommand([0x80, 0x00, 0x00, 0x00])
    WaitForGPIO6()
    # get ABS value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID0: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    absolute = value[1] + 256*value[2] + 65536*value[3]
    encoder_abs_text.set(absolute)
    # get CRC + SF value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID0: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_status_text.set(value[1])
    encoder_crc_received_text.set(value[2])
    encoder_crc_calculated_text.set(value[3])

# ABM value
def spi_tamagawa_id1():
    value = SpiWriteCommand([0x81, 0x00, 0x00, 0x00])
    WaitForGPIO6()
    # get ABM value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID1: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    multi_turn = value[1] + 256*value[2] + 65536*value[3]
    encoder_abm_text.set(multi_turn)
    # get CRC + SF value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID1: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_status_text.set(value[1])
    encoder_crc_received_text.set(value[2])
    encoder_crc_calculated_text.set(value[3])

# ENID
def spi_tamagawa_id2():
    value = SpiWriteCommand([0x82, 0x00, 0x00, 0x00])
    WaitForGPIO6()
    # get ENID value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID2: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_id_text.set(value[3])
    # get CRC + SF value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID2: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_status_text.set(value[1])
    encoder_crc_received_text.set(value[2])
    encoder_crc_calculated_text.set(value[3])

# ABS + ENID + ABM + ALMC
def spi_tamagawa_id3():
    # get ABS value
    value = SpiWriteCommand([0x83, 0x00, 0x00, 0x00])
    WaitForGPIO6()
    # get ABS value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID3 - ABS: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    absolute = value[1] + 256*value[2] + 65536*value[3]
    encoder_abs_text.set(absolute)
    # get ENID value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID3 - ENID: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_id_text.set(value[3])
    # get ABM value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID3 - ABM: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    multi_turn = value[1] + 256*value[2] + 65536*value[3]
    encoder_abm_text.set(multi_turn)
    # get ALMC value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID3 - ALMC: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_almc_text.set(value[3])
    # get CRC + SF value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID3 - CRC: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_status_text.set(value[1])
    encoder_crc_received_text.set(value[2])
    encoder_crc_calculated_text.set(value[3])

# reset latched error flags
def spi_tamagawa_id7():
    for x in range(1, 11):
        print(f"count {x}: ID7 - reset latched error flags")
        value = SpiWriteCommand([0x87, 0x00, 0x00, 0x00])
        WaitForGPIO6()
        # get ABS value
        value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
        print(f"ID7: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
        absolute = value[1] + 256*value[2] + 65536*value[3]
        encoder_abs_text.set(absolute)
        # get CRC + SF value
        value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
        print(f"ID7: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
        encoder_status_text.set(value[1])
        encoder_crc_received_text.set(value[2])
        encoder_crc_calculated_text.set(value[3])
        time.sleep(0.1)

# reset encoder abs position counter
def spi_tamagawa_id8():
    for x in range(1, 11):
        print(f"count {x}: ID8 - reset encoder absolute position counter")
        value = SpiWriteCommand([0x88, 0x00, 0x00, 0x00])
        WaitForGPIO6()
        # get ABS value
        value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
        print(f"ID8: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
        absolute = value[1] + 256*value[2] + 65536*value[3]
        encoder_abs_text.set(absolute)
        # get CRC + SF value
        value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
        print(f"ID8: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
        encoder_status_text.set(value[1])
        encoder_crc_received_text.set(value[2])
        encoder_crc_calculated_text.set(value[3])
        time.sleep(0.1)

# reset encoder multi-turn counter
def spi_tamagawa_idc():
    for x in range(1, 11):
        print(f"count {x}: IDC - reset encoder multi-turn counter")
        value = SpiWriteCommand([0x8c, 0x00, 0x00, 0x00])
        WaitForGPIO6()
        # get ABS value
        value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
        print(f"IDC: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
        absolute = value[1] + 256*value[2] + 65536*value[3]
        encoder_abs_text.set(absolute)
        # get CRC + SF value
        value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
        print(f"IDC: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
        encoder_status_text.set(value[1])
        encoder_crc_received_text.set(value[2])
        encoder_crc_calculated_text.set(value[3])
        time.sleep(0.1)

# write 8bit of user data
def spi_tamagawa_id6():
    # get address + data
    addr_value = int(encoder_addr_sent_text.get())
    data_value = int(encoder_data_sent_text.get())
    # write LSB of data to address
    value = SpiWriteCommand([0x86, 0x00, data_value & 0xff, addr_value])
    WaitForGPIO6()
    # get reply address + data LSB value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID6: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_data_received_text.set(value[2])
    encoder_addr_received_text.set(value[3])
    # get reply CRC value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ID6: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_crc_received_text.set(value[2])
    encoder_crc_calculated_text.set(value[3])

# read 8bit of user data
def spi_tamagawa_idd():
    # get address
    addr_value = int(encoder_addr_sent_text.get())
    # read 8bit of data LSB from address
    value = SpiWriteCommand([0x8d, 0x00, 0x00, addr_value])
    WaitForGPIO6()
    # get address + data LSB value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"IDD: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    data_value=value[2]
    encoder_data_received_text.set(data_value)
    encoder_addr_received_text.set(value[3])
    # get CRC + SF value
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"IDD: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_crc_received_text.set(value[2])
    encoder_crc_calculated_text.set(value[3])
   
def spi_tamagawa_fw_version():
    # get firmware version
    value = SpiWriteCommand([0xFF, 0x00, 0x00, 0x00])
    #WaitForGPIO6()
    # get firmware version
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"Version: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    print(f"Firmware Version: {value[2]}.{value[3]}")
    fw_version_text.set(str(value[2]) + "." + str(value[3]))
   
def spi_tamagawa_protocol():
    # get firmware version
    value = SpiWriteCommand([0xFE, 0x00, 0x00, 0x00])
    #WaitForGPIO6()
    # get firmware version
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"Protocol: {value[0]}{value[1]}{value[2]}{value[3]}")
    fw_protocol_text.set(chr(value[0])+chr(value[1])+chr(value[2])+chr(value[3]))
    
    
##
## Tamagawa fm_tamagawa
##
fm_tamagawa = tk.LabelFrame(text="Tamagawa T-Format")
btn_tamagawa_id0 = tk.Button(master=fm_tamagawa, text="ID0", command=spi_tamagawa_id0); btn_tamagawa_id0.grid(row = 0,column = 0)
btn_tamagawa_id1 = tk.Button(master=fm_tamagawa, text="ID1", command=spi_tamagawa_id1); btn_tamagawa_id1.grid(row = 1,column = 0)
btn_tamagawa_id2 = tk.Button(master=fm_tamagawa, text="ID2", command=spi_tamagawa_id2); btn_tamagawa_id2.grid(row = 2,column = 0)
btn_tamagawa_id3 = tk.Button(master=fm_tamagawa, text="ID3", command=spi_tamagawa_id3); btn_tamagawa_id3.grid(row = 3,column = 0)
btn_tamagawa_id6 = tk.Button(master=fm_tamagawa, text="ID6", command=spi_tamagawa_id6); btn_tamagawa_id6.grid(row = 4,column = 0)
btn_tamagawa_id7 = tk.Button(master=fm_tamagawa, text="ID7", command=spi_tamagawa_id7); btn_tamagawa_id7.grid(row = 5,column = 0)
btn_tamagawa_id8 = tk.Button(master=fm_tamagawa, text="ID8", command=spi_tamagawa_id8); btn_tamagawa_id8.grid(row = 6,column = 0)
btn_tamagawa_idc = tk.Button(master=fm_tamagawa, text="IDC", command=spi_tamagawa_idc); btn_tamagawa_idc.grid(row = 7,column = 0)
btn_tamagawa_idd = tk.Button(master=fm_tamagawa, text="IDD", command=spi_tamagawa_idd); btn_tamagawa_idd.grid(row = 8,column = 0)

lbl_encoder_abs = tk.Label(master=fm_tamagawa, text="ABS"); lbl_encoder_abs.grid(row=0, column=1)
encoder_abs_text = tk.StringVar()
ent_encoder_abs = tk.Entry(master=fm_tamagawa, textvariable=encoder_abs_text, width=7); ent_encoder_abs.grid(row=0, column=2)
encoder_abs_text.set("0")

lbl_encoder_abm = tk.Label(master=fm_tamagawa, text="ABM"); lbl_encoder_abm.grid(row=1, column=1)
encoder_abm_text = tk.StringVar()
ent_encoder_abm = tk.Entry(master=fm_tamagawa, textvariable=encoder_abm_text, width=7); ent_encoder_abm.grid(row=1, column=2)
encoder_abm_text.set("0")

lbl_encoder_status = tk.Label(master=fm_tamagawa, text="SF"); lbl_encoder_status.grid(row=2, column=1)
encoder_status_text = tk.StringVar()
ent_encoder_status = tk.Entry(master=fm_tamagawa, textvariable=encoder_status_text, width=7); ent_encoder_status.grid(row=2, column=2)
encoder_status_text.set("0")

lbl_encoder_id = tk.Label(master=fm_tamagawa, text="ENID"); lbl_encoder_id.grid(row=3, column=1)
encoder_id_text = tk.StringVar()
ent_encoder_id = tk.Entry(master=fm_tamagawa, textvariable=encoder_id_text, width=7); ent_encoder_id.grid(row=3, column=2)
encoder_id_text.set("0")

lbl_encoder_almc = tk.Label(master=fm_tamagawa, text="ALMC"); lbl_encoder_almc.grid(row=4, column=1)
encoder_almc_text = tk.StringVar()
ent_encoder_almc = tk.Entry(master=fm_tamagawa, textvariable=encoder_almc_text, width=7); ent_encoder_almc.grid(row=4, column=2)
encoder_almc_text.set("0")

lbl_encoder_crc_calculated = tk.Label(master=fm_tamagawa, text="CRC calculated"); lbl_encoder_crc_calculated.grid(row=5, column=1)
encoder_crc_calculated_text = tk.StringVar()
ent_encoder_crc_calculated = tk.Entry(master=fm_tamagawa, textvariable=encoder_crc_calculated_text, width=7); ent_encoder_crc_calculated.grid(row=5, column=2)
encoder_crc_calculated_text.set("0")

lbl_encoder_crc_received = tk.Label(master=fm_tamagawa, text="CRC received"); lbl_encoder_crc_received.grid(row=6, column=1)
encoder_crc_received_text = tk.StringVar()
ent_encoder_crc_received = tk.Entry(master=fm_tamagawa, textvariable=encoder_crc_received_text, width=7); ent_encoder_crc_received.grid(row=6, column=2)
encoder_crc_received_text.set("0")

lbl_encoder_addr_sent = tk.Label(master=fm_tamagawa, text="Address sent"); lbl_encoder_addr_sent.grid(row=0, column=3)
encoder_addr_sent_text = tk.StringVar()
ent_encoder_addr_sent = tk.Entry(master=fm_tamagawa, textvariable=encoder_addr_sent_text, width=7); ent_encoder_addr_sent.grid(row=0, column=4)
encoder_addr_sent_text.set("0")

lbl_encoder_data_sent = tk.Label(master=fm_tamagawa, text="Data sent"); lbl_encoder_data_sent.grid(row=0, column=5)
encoder_data_sent_text = tk.StringVar()
ent_encoder_data_sent = tk.Entry(master=fm_tamagawa, textvariable=encoder_data_sent_text, width=7); ent_encoder_data_sent.grid(row=0, column=6)
encoder_data_sent_text.set("0")

lbl_encoder_addr_received = tk.Label(master=fm_tamagawa, text="Address received"); lbl_encoder_addr_received.grid(row=1, column=3)
encoder_addr_received_text = tk.StringVar()
ent_encoder_addr_received = tk.Entry(master=fm_tamagawa, textvariable=encoder_addr_received_text, width=7); ent_encoder_addr_received.grid(row=1, column=4)
encoder_addr_received_text.set("0")

lbl_encoder_data_received = tk.Label(master=fm_tamagawa, text="Data received"); lbl_encoder_data_received.grid(row=1, column=5)
encoder_data_received_text = tk.StringVar()
ent_encoder_data_received = tk.Entry(master=fm_tamagawa, textvariable=encoder_data_received_text, width=7); ent_encoder_data_received.grid(row=1, column=6)
encoder_data_received_text.set("0")

fm_firmware_version = tk.LabelFrame(text="FW Version")
btn_get_firmware_version = tk.Button(master=fm_firmware_version, text="FW Version", command=spi_tamagawa_fw_version); btn_get_firmware_version.grid(row = 0,column = 0)
btn_get_protocol = tk.Button(master=fm_firmware_version, text="Get Protocol", command=spi_tamagawa_protocol); btn_get_protocol.grid(row = 1,column = 0)

fw_version_text = tk.StringVar()
ent_fw_version = tk.Entry(master=fm_firmware_version, textvariable=fw_version_text, width=7); ent_fw_version.grid(row=0, column=1)
fw_version_text.set("0.0")

fw_protocol_text = tk.StringVar()
ent_protocol = tk.Entry(master=fm_firmware_version, textvariable=fw_protocol_text, width=7); ent_protocol.grid(row=1, column=1)
fw_protocol_text.set("0")

fm_file_select.grid(sticky="W", row=1, column=0)
fm_tamagawa.grid(sticky="W", row=2, column=0)
fm_firmware_version.grid(sticky="W", row=3, column=0)

win.mainloop()
close_port()

 
