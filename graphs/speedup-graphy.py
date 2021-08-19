import matplotlib.pyplot as plt

# tempo de execução para tamanhos 512, 1024, 2048, 4096
sequencial = [0.31258, 2.76, 39.68, 460.61]
x1Thread = [0.36267, 3.36, 43.47, 515.87]
x2Threads = [0.201, 1.67, 19.34, 331.41]
x3Threads = [0.160, 1.35, 14.09, 253.62]
x4threads = [0.12685, 1.07, 10.32, 184.91]

y512 = [
    sequencial[0] / x1Thread[0],
    sequencial[0] / x2Threads[0],
    sequencial[0] / x3Threads[0],
    sequencial[0] / x4threads[0],
]

y1024 = [
    sequencial[1] / x1Thread[1],
    sequencial[1] / x2Threads[1],
    sequencial[1] / x3Threads[1],
    sequencial[1] / x4threads[1],
]

y2048 = [
    sequencial[2] / x1Thread[2],
    sequencial[2] / x2Threads[2],
    sequencial[2] / x3Threads[2],
    sequencial[2] / x4threads[2],
]

y4096 = [
    sequencial[3] / x1Thread[3],
    sequencial[3] / x2Threads[3],
    sequencial[3] / x3Threads[3],
    sequencial[3] / x4threads[3],
]

points = list(range(1, 5))
plt.plot(points, points, label="ideal")
plt.plot(points, y512, label="512")
plt.plot(points, y1024, label="1024")
plt.plot(points, y2048, label="2048")
plt.plot(points, y4096, label="4096")

plt.xlabel('Quantidade de Threads')
plt.ylabel('Speedup')

plt.title('Matrix Multiplication')

plt.legend()

plt.show()
