import matplotlib.pyplot as plt

# time without pthread
xWithoutPThread = [512, 1024, 2056, 4096]
yWithoutPThread = [1.42, 6.83, 42.62, 460.61]

# time with pthread
xPThread = [512, 1024, 2056, 4096]
yPThread = [0.19009, 1.1, 11.32, 184.91]

plt.plot(xWithoutPThread, yWithoutPThread,
         label="Without 4 Threads", marker='o', linestyle='dashed')
plt.plot(xPThread, yPThread, label="Using Threads",
         marker='o', linestyle='dashed')

plt.xlabel('Matrix Dimensions')
plt.ylabel('Time - secs')

plt.title('Matrix Multiplication')

plt.legend()

plt.show()
