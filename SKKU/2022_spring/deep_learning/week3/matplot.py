import matplotlib.pyplot as plt
import numpy as np

def sigmoid(x) :
    return 1 / (1 + np.exp(-x))


a = np.arange(-40, 40)
a /= 10

b = sigmoid(a)

fig, ax = plt.subplots()
ax.plot(a, b)

plt.plot()