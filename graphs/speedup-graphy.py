import matplotlib.pyplot as plt

x = [2, 4, 8, 16]
ySequencialTime = [1.42, 6.83, 42.62, 460.61]

# tempo de execução para tamanhos 512, 1024, 2048, 4096
x2Threads = [0.201, 1.67, 19.34, 331.41]
x4threads = [0.190, 1.1, 11.32, 184.91]
x8Threads = [0.13553, 1.26, 20.11, 201.65]
x16Threads = [0.13909, 1.21, 12.92, 207.41]

y512 = [
    ySequencialTime[0] / x2Threads[0],
    ySequencialTime[0] / x4threads[0],
    ySequencialTime[0] / x8Threads[0],
    ySequencialTime[0] / x16Threads[0]
]

y1024 = [
    ySequencialTime[1] / x2Threads[1],
    ySequencialTime[1] / x4threads[1],
    ySequencialTime[1] / x8Threads[1],
    ySequencialTime[1] / x16Threads[1]
]

y2056 = [
    ySequencialTime[2] / x2Threads[2],
    ySequencialTime[2] / x4threads[2],
    ySequencialTime[2] / x8Threads[2],
    ySequencialTime[2] / x16Threads[2]
]

y4096 = [
    ySequencialTime[3] / x2Threads[3],
    ySequencialTime[3] / x4threads[3],
    ySequencialTime[3] / x8Threads[3],
    ySequencialTime[3] / x16Threads[3]
]

plt.plot(x, y512,
         label="512", marker='o', linestyle='dashed')
plt.plot(x, y1024,
         label="1024", marker='o', linestyle='dashed')
plt.plot(x, y2056,
         label="2048", marker='o', linestyle='dashed')
# plt.plot(x, y4096,
#          label="4096", marker='o', linestyle='dashed')

plt.xlabel('Quantidade de Threads')
plt.ylabel('Speedup')

plt.title('Matrix Multiplication')

plt.legend()

plt.show()
