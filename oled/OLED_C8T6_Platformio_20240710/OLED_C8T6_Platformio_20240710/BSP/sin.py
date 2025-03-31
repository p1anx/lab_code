import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import math

if __name__ == '__main__':
    a = np.linspace(0, 2*np.pi, 128)
    b = (np.sin(a) + 1) / 2 * 64
    np.floor(b, b)
    print(b)

    plt.plot(a, b)
    plt.show()