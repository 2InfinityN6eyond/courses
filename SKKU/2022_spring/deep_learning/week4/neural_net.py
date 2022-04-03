import numpy as np

class NeuralNetwork :
    def __init__(self, weight_matricies:list) :
        self.weight_matricies = weight_matricies
        self.cache_h = [0] * (len(self.weight_matricies) + 1)
        self.dE_dnet = [0] * len(self.weight_matricies)
        self.dE_dW = [0] * len(self.weight_matricies)

    def sigmoid(self, x) :
        return 1 / (1 + np.exp(-x))

    def process(self, x:np.ndarray) :
        self.cache_h[0] = x.copy()
        for i, W in enumerate(self.weight_matricies) :
            net = np.matmul(W, self.cache_h[i])
            self.cache_h[i + 1] = self.sigmoid(net)
        return self.cache_h[-1][0]

    def backPropagate(self, y:np.ndarray, lr) :
        self.dE_dnet[-1] = self.cache_h[-1] * (1 - self.cache_h[-1]) * (self.cache_h[-1] - y)
        for i in range(len(self.weight_matricies) -2, -1, -1) :
            self.dE_dnet[i] = self.cache_h[i + 1] * (1 - self.cache_h[i + 1]) * \
                np.sum(self.weight_matricies[i + 1] * self.dE_dnet[i + 1], axis=0).reshape(-1, 1)
        
        self.dE_dW = list(map(lambda v1, v2: np.matmul(v1, v2.transpose()), self.dE_dnet, self.cache_h[:-1]))
        self.weight_matricies = list(map(lambda W, dE_dW : W - dE_dW * lr, self.weight_matricies, self.dE_dW))


if __name__ == "__main__" :
    weight_matricies = [
        np.array([[1]]),
        np.array([[1], [1]]),
        np.array([[1, 1]])
    ]
    x = np.array([[1]])
    y = np.array([[1]])
    nn = NeuralNetwork(weight_matricies=weight_matricies)
    nn.process(x)
    nn.backPropagate(y, 0.1)
    for weight_matrix in nn.weight_matricies :
        print(weight_matrix)