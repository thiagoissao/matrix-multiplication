from matplotlib import lines
import matplotlib.pyplot as plt

# tempo de execução para tamanhos 256, 512, 1024, 2048
sequencial = [0.04598, 0.3588, 3.35, 39.68]
x1Thread = [0.04792, 0.43714, 3.55, 44.35]
x2Threads = [0.02775, 0.18846, 1.84, 22.84]
x4threads = [0.01715, 0.11668, 1.11, 12.54]
x8threads = [0.0191, 0.11922, 1.04, 12.23]

y256 = [
    sequencial[0] / x1Thread[0],
    sequencial[0] / x2Threads[0],
    sequencial[0] / x4threads[0],
    sequencial[0] / x8threads[0],
]

y512 = [
    sequencial[1] / x1Thread[1],
    sequencial[1] / x2Threads[1],
    sequencial[1] / x4threads[1],
    sequencial[1] / x8threads[1],
]

y1024 = [
    sequencial[2] / x1Thread[2],
    sequencial[2] / x2Threads[2],
    sequencial[2] / x4threads[2],
    sequencial[2] / x8threads[2],
]

y2048 = [
    sequencial[3] / x1Thread[3],
    sequencial[3] / x2Threads[3],
    sequencial[3] / x4threads[3],
    sequencial[3] / x8threads[3],
]

points = [1, 2, 4, 8]
plt.plot(points, points, label="ideal")
plt.plot(points, y256, label="256", linestyle='dashed', marker='.')
plt.plot(points, y512, label="512", linestyle='dashed', marker='.')
plt.plot(points, y1024, label="1024", linestyle='dashed', marker='.')
plt.plot(points, y2048, label="2048", linestyle='dashed', marker='.')

plt.xlabel('Number of Threads')
plt.ylabel('Speedup')

plt.title('Matrix Multiplication')

plt.legend()

plt.show()
