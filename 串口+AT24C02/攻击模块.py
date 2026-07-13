import struct,serial,time

ser=serial.Serial(port="COM9",baudrate=4800,timeout=1)

def ser_read():
    ser.reset_input_buffer()
    ser.write(b'READ\n')
    time.sleep(1.5)

    if ser.in_waiting:
        data=ser.read(ser.in_waiting)
        print("Raw data:", data)
        data=data[4::]
        print("Raw data:", data)
        return data.decode('ascii')
    return None

def ser_write(num_list):
    ser.write(b'SET\n')
    time.sleep(1.5)
    for i in num_list:
        ser.write(bytes([i]))
        time.sleep(0.05)

num_list=[0x09,0x09,0x09,0x09]
print("之前数值：",ser_read())
ser_write(num_list)
print("改动后数值：",ser_read())
ser.close()