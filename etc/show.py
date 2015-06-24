#!/usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    data = np.fromfile(file='data', dtype=int, sep=' ')
    plt.plot(data)
    plt.show()

