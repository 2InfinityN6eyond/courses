import numpy as np

class Node :
    def __init__(self, weights, func, bias = None) :
        if not isinstance(weights, np.ndarray) :
            self.weights = np.array(weights)
        else :
            self.weights = weights
        if bias != None:
            self.bias = bias
            self.has_bias = True
        else :
            self.has_bias = False
        self.func = func

    def process(self, x) :
        result = np.sum(x * self.weights)
        if self.has_bias :
            result += self.bias
        result = self.func(result)

class NeuralNetwork :
    def __init__(self, learning_rate, self.) -> None:
        self.learning_rate = learning_rate

    @classmethod
    def sigmoid(x) :
        return 1 / (1 + np.exp(-x))
        
