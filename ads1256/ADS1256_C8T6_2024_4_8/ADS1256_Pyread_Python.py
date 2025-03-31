import numpy as np
import time
from tqdm import trange
import serial
import matplotlib.pyplot as plt
import threading
import queue


# rxData = np.zeros(3, dtype=np.uint8)


def serialThreading(ser, data_queue):
    try:
        rxFlag = b"\x19"
        while True:
            if ser.in_waiting > 0:
                if not ser.read(1) == rxFlag:
                    pass
                else:
                    rxData = ser.read(3)
                    data_queue.put(rxData)
    except KeyboardInterrupt:
        print("Serial Threading is closed")


def ADS1256_SerialThreadingRead():
    try:
        startTime = time.time()
        v = []
        dataSize = 1000
        data_queue = queue.Queue()
        ser = serial.Serial("COM7", 115200)
        if not ser.is_open:
            print("Serial port is not open.")
            ser.open()
        t = threading.Thread(target=serialThreading, args=(ser, data_queue))
        t.daemon = True
        t.start()
        start_whileTime = time.time()
        while True:
            # for i in trange(0, dataSize):
            if not data_queue.empty():
                rxData = data_queue.get()
                voltage = (
                    (rxData[0] << 16 | rxData[1] << 8 | rxData[2]) / (2**23 - 1) * 5.0
                )
                v.append(voltage)
                print("v=", voltage, end="\r", flush=True)
            # else:
            # time.sleep(0.1)  # 100ms避免空转
            if len(v) == dataSize:
                break
        end_whileTime = time.time()
        print(f"while time:{end_whileTime - start_whileTime}")
        x = range(0, dataSize)
        plt.plot(x, v, label="voltage")
        plt.xlabel("time")
        plt.ylabel("voltage")
        plt.legend()
        endTime = time.time()
        print(f"Runtime:{endTime - startTime}")
        plt.show()
    except KeyboardInterrupt:
        print("serial port is closed")
        # t.stop()  # 停止线程
        ser.close()

    # voltage = (rxData[0] << 16 | rxData[1] << 8 | rxData[2]) / (2**23 - 1) * 5.0
    # while True:
    #     print(voltage, end="\r", flush=True)


def ADS1256_SerialRead():
    startTime = time.time()
    port = "COM7"
    baudrate = 115200
    ser = serial.Serial(port, baudrate)
    if not ser.is_open:
        print("Serial port is not open.")
        ser.open()

    rxFlag = b"\x19"
    dataSize = 1000
    v = []
    # rxData = np.zeros(3, dtype=np.uint8)

    try:
        a = 0
        while True:
            # a = 1 + a
            # if a > 1000:
            #     break
            if ser.in_waiting > 0:
                if not ser.read(1) == rxFlag:
                    # print("in waiting:", time.time(), end="\r\n", flush=True)
                    pass
                else:
                    rxData = ser.read(3)
                    voltage = (
                        (rxData[0] << 16 | rxData[1] << 8 | rxData[2])
                        / (2**23 - 1)
                        * 5.0
                    )
                    v.append(voltage)
                    print(voltage, end="\r", flush=True)
            if len(v) == dataSize:
                break
        x = range(0, dataSize)
        plt.plot(x, v, label="voltage")
        plt.xlabel("time")
        plt.ylabel("voltage")
        plt.legend()
        endTime = time.time()
        print(f"Runtime:{endTime - startTime}")
        plt.show()

    except KeyboardInterrupt:
        print("serial port is closed")
        ser.close()


def test():
    try:
        while True:
            pass
    except KeyboardInterrupt:
        print("ok")


if __name__ == "__main__":
    print("Hello, World!")
    # ADS1256_SerialThreadingRead()
    ADS1256_SerialRead()
