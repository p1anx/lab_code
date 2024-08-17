
import serial
import numpy as np
import matplotlib.pyplot as plt
import scipy.fft as fft
import pandas as pd


port = '/dev/ttyUSB0'
baudrate = 115200
# fs = 2088 # 7200sps
# fs = 1184 # 1200sps
fs =  98
filePath = '/home/xwj/Documents/Research/Metlags_and_nichrome/'
img = '80cm1Hz_with_metglas.png'

def cal():
    rxflag = b'\x11'
    # port = 'COM7'
    # port = '/dev/ttyUSB1'
    # baudrate = 115200
    # fs = 1200 / 5.9 * 10 /97.4 * 100
    print(f'fs:{fs}Hz')
    n_point = 1024

    ser = serial.Serial(port, baudrate)

    voltage = np.zeros(n_point)
    i = 0
    try:
        while True:
            # print('waiting!!', end = '\r')
            # print(ser.read(1))

            if  rxflag == ser.read(1):
                data = ser.read(4)
                data_str = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]

                if data_str > 2**31:
                    data_str = 2**32 - data_str
                    data_str = -data_str
                print('data:', data_str, end= '\r')
                voltage[i] = data_str * 2.5  / (2**31)
                i = i + 1

                if i == n_point-1:
                    voltage = np.array(voltage)
                    v_buffer = voltage[0:1000]
                    ########################################################
                    df = pd.DataFrame(v_buffer)
                    filePath = '/home/xwj/Documents/Research/rotate0/'
                    df.to_csv(filePath+'cal.csv', index= False)
                    ########################################################


                    n_point  = len(v_buffer)


                    v = fft.fft(v_buffer)
                    # v = 20*np.log10(abs(v))
                    f = fft.fftfreq(n_point, 1/fs)
                    
                    plt.figure(1)
                    plt.subplot(211)
                    plt.plot(range(n_point), v_buffer)
                    plt.xlabel('t')
                    plt.ylabel('v')
                    # plt.xlim([0, 1000])

                    plt.subplot(212)
                    plt.plot(f, v)
                    plt.xlabel('f/Hz')
                    plt.ylabel('y/dB')
                    plt.xlim([0, fs/2])
                    
                    plt.tight_layout()

                    plt.savefig('/home/xwj/Documents/Research/500Hz_20mvpp.png', dpi = 300)
                    plt.show()
                    break
                
            else:
                print('waiting!!', end = '\r')
                
    except KeyboardInterrupt:
        ser.close()
        print("serial closed!\n")
def serialPlot():
    rxflag = b'\x11'
    # port = 'COM7'
    print(f'fs:{fs}Hz')
    n_point = 1024
    
    # file_path = filePath
    # cal_data = pd.read_csv(filePath + 'cal.csv')
    # data1 = cal_data['0']
    # caldata = np.array(data1)
    # print(data[0])
    # print(cal_data['0'])
    ser = serial.Serial(port, baudrate)

    voltage = np.zeros(n_point)
    i = 0
    try:
        while True:
            # print('waiting!!', end = '\r')
            # print(ser.read(1))

            if  rxflag == ser.read(1):
                data = ser.read(4)
                data_str = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]

                if data_str > 2**31:
                    data_str = 2**32 - data_str
                    data_str = -data_str
                print('data:', data_str, end= '\r')
                voltage[i] = data_str * 2.5  / (2**31)
                i = i + 1

                if i == n_point-1:
                    voltage = np.array(voltage)
                    # v_buffer = voltage[0:1000] - caldata
                    v_buffer = voltage[0:1000] 
                    n_point  = len(v_buffer)


                    v = fft.fft(v_buffer)
                    v = 20*np.log10(abs(v))
                    # v = abs(v)
                    f = fft.fftfreq(n_point, 1/fs)
                    
                    plt.figure(1)
                    plt.subplot(211)
                    plt.plot(range(n_point), v_buffer)
                    plt.xlabel('t')
                    plt.ylabel('v')
                    # plt.xlim([0, 1000])

                    plt.subplot(212)
                    plt.plot(f, v)
                    plt.xlabel('f/Hz')
                    plt.ylabel('y/dB')
                    plt.xlim([0, fs/2])
                    
                    plt.tight_layout()

                    plt.savefig(filePath+ img, dpi = 300)
                    plt.show()
                    break
                
            else:
                print('waiting!!', end = '\r')
                
    except KeyboardInterrupt:
        ser.close()
        print("serial closed!\n")

def serialRead():
    rxflag = b'\x11'
    port = 'COM7'
    baudrate = 115200

    ser = serial.Serial(port, baudrate)

    try:
        while True:
            # print('waiting!!', end = '\r')
            # print(ser.read(1))
            if  rxflag == ser.read(1):
                data = ser.read(4)
                data_str = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]

                if data_str > 2**31:
                    data_str = 2**32 - data_str
                    data_str = -data_str
                voltage = data_str * 2.5  / (2**31)
                print(f'data:{data_str}', end= '\r')
                # print('\n')
                print(f'voltage:{voltage} v', end= '\r')
            else:
                print('waiting!!', end = '\r')
                




    except KeyboardInterrupt:
        ser.close()
        print("serial closed!\n")
if __name__ == '__main__':
    # print('data:', 2**3)
    # print(b'0x11')
    # serialRead()
    # cal()
    serialPlot()