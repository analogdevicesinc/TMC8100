################################################################################
# Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
# proprietary & confidential to Analog Devices, Inc. and its licensors.
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
win.title("TMC8100-EVAL SSI Demo")
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

# encoder value
def spi_get_encoder_value():
    # get encoder value command
    value = SpiWriteCommand([0x80, 0x00, 0x00, 0x00])
    WaitForGPIO6()
    # get ST value (raw / gray code value)
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ST (raw): {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    single_turn = 256*value[2] + value[3]
    encoder_single_turn_text.set(single_turn)
    # get ST value (binary value)
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ST (binary): {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    single_turn = 256*value[2] + value[3]
    encoder_single_turn_converted_text.set(single_turn)
    # limit value to 12bit
    #single_turn = (single_turn >> 4) & 4095
    #encoder_single_turn_limited_text.set(single_turn)
    # get error flags
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"ERR: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    encoder_error_text.set(value[1])
 
def spi_get_encoder_value_cont():
    # get encoder value command
    value = SpiWriteCommand([0x80, 0x00, 0x00, 0x00])
    read_every_second()

 
def spi_get_fw_version():
    # get firmware version
    value = SpiWriteCommand([0xFF, 0x00, 0x00, 0x00])
    #WaitForGPIO6()
    # get firmware version
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"Version: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
    print(f"Firmware Version: {value[2]}.{value[3]}")
    fw_version_text.set(str(value[2]) + "." + str(value[3]))
   
def spi_get_protocol():
    # get firmware version
    value = SpiWriteCommand([0xFE, 0x00, 0x00, 0x00])
    #WaitForGPIO6()
    # get firmware version
    value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
    print(f"Protocol: {value[0]}{value[1]}{value[2]}{value[3]}")
    fw_protocol_text.set(chr(value[0])+chr(value[1])+chr(value[2])+chr(value[3]))
    
    
##
## SSI fm_ssi
##
fm_ssi = tk.LabelFrame(text="SSI")
btn_get_encoder_value = tk.Button(master=fm_ssi, text="Read Encoder", command=spi_get_encoder_value); btn_get_encoder_value.grid(row = 0,column = 0)
btn_get_encoder_value_cont = tk.Button(master=fm_ssi, text="Read Encoder continuously", command=spi_get_encoder_value_cont); btn_get_encoder_value_cont.grid(row = 1,column = 0)

lbl_encoder_single_turn = tk.Label(master=fm_ssi, text="ST (raw / gray code / 16bit)"); lbl_encoder_single_turn.grid(row=0, column=1)
encoder_single_turn_text = tk.StringVar()
ent_encoder_single_turn = tk.Entry(master=fm_ssi, textvariable=encoder_single_turn_text, width=7); ent_encoder_single_turn.grid(row=0, column=2)
encoder_single_turn_text.set("0")

lbl_encoder_single_turn_converted = tk.Label(master=fm_ssi, text="ST (converted / binary / 16bit)"); lbl_encoder_single_turn_converted.grid(row=1, column=1)
encoder_single_turn_converted_text = tk.StringVar()
ent_encoder_single_turn_converted = tk.Entry(master=fm_ssi, textvariable=encoder_single_turn_converted_text, width=7); ent_encoder_single_turn_converted.grid(row=1, column=2)
encoder_single_turn_converted_text.set("0")

lbl_encoder_error = tk.Label(master=fm_ssi, text="Error"); lbl_encoder_error.grid(row=2, column=1)
encoder_error_text = tk.StringVar()
ent_encoder_error = tk.Entry(master=fm_ssi, textvariable=encoder_error_text, width=7); ent_encoder_error.grid(row=2, column=2)
encoder_error_text.set("0")

fm_firmware_version = tk.LabelFrame(text="FW Version")
btn_get_firmware_version = tk.Button(master=fm_firmware_version, text="FW Version", command=spi_get_fw_version); btn_get_firmware_version.grid(row = 0,column = 0)
btn_get_protocol = tk.Button(master=fm_firmware_version, text="Get Protocol", command=spi_get_protocol); btn_get_protocol.grid(row = 1,column = 0)

fw_version_text = tk.StringVar()
ent_fw_version = tk.Entry(master=fm_firmware_version, textvariable=fw_version_text, width=7); ent_fw_version.grid(row=0, column=1)
fw_version_text.set("0.0")

fw_protocol_text = tk.StringVar()
ent_protocol = tk.Entry(master=fm_firmware_version, textvariable=fw_protocol_text, width=7); ent_protocol.grid(row=1, column=1)
fw_protocol_text.set("0")

fm_file_select.grid(sticky="W", row=1, column=0)
fm_ssi.grid(sticky="W", row=2, column=0)
fm_firmware_version.grid(sticky="W", row=3, column=0)

tri_x0=100
tri_y0=100
tri_x1=100
tri_y1=100
tri_x2=100
tri_y2=100
g_value=0


def read_every_second():
    global tri_x0, tri_y0, tri_x1, tri_y1, tri_x2, tri_y2
    reply = GetGPIO6()
    if reply == 1: # reply in SPI transmit buffer
        # get encoder value command
        #value = SpiWriteCommand([0x80, 0x00, 0x00, 0x00])
        WaitForGPIO6()
        # get ST value (raw / gray code value)
        value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
        #print(f"ST (raw): {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
        single_turn = 256*value[2] + value[3]
        encoder_single_turn_text.set(single_turn)
        # get ST value (binary value)
        value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
        #print(f"ST (binary): {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
        single_turn = 256*value[2] + value[3]
        encoder_single_turn_converted_text.set(single_turn)
        # limit value to 12bit
        #single_turn = (single_turn >> 4) & 4095
        #encoder_single_turn_limited_text.set(single_turn)
        # get error flags
        value = SpiWriteCommand([0x00, 0x00, 0x00, 0x00])
        #print(f"ERR: {value[0]:02x} {value[1]:02x} {value[2]:02x} {value[3]:02x}")
        encoder_error_text.set(value[1])
        # use single turn 12bit value
        absolute_degree = single_turn / 65536 * 360
        points = [tri_x0, tri_y0, tri_x1, tri_y1, tri_x2, tri_y2]
        w.create_polygon(points, outline='white', fill='white', width=3)
        g_value= 360 - absolute_degree
        degree = 360 - g_value + 90
        radiant = math.radians(degree)
        tri_x0 = 100 + 80 * math.cos(radiant)
        tri_y0 = 100 - 80 * math.sin(radiant)
        degree = 360 - g_value + 90 + 10
        radiant = math.radians(degree)
        tri_x1 = 100 + 60 * math.cos(radiant)
        tri_y1 = 100 - 60 * math.sin(radiant)
        degree = 360 - g_value + 90 - 10
        radiant = math.radians(degree)
        tri_x2 = 100 + 60 * math.cos(radiant)
        tri_y2 = 100 - 60 * math.sin(radiant)
        points = [tri_x0, tri_y0, tri_x1, tri_y1, tri_x2, tri_y2]
        w.create_polygon(points, outline='red', fill='white', width=3)
        SpiWriteCommand([0x80, 0x00, 0x00, 0x00]) # next encoder fetch
        #print("***************")
    win.after(100, read_every_second)

w = Canvas(win, width = 200, height = 200)
w.grid(row = 3, column=0)
w.create_oval(10, 10, 190, 190, fill="white")
w.create_oval(15, 15, 185, 185)
for i in range(0, 360, 10):
    radiant = math.radians(i)
    x0 = 100 + 85 * math.cos(radiant)
    y0 = 100 - 85 * math.sin(radiant)
    x1 = 100 + 90 * math.cos(radiant)
    y1 = 100 - 90 * math.sin(radiant)
    w.create_line(x0, y0, x1, y1)

win.mainloop()
close_port()
