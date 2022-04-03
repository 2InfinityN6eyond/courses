import numpy as np

class Perceptron :
    def __init__(self, weights:np.ndarray, bias = 0) -> None :
        self.weights = weights
        self.bias = bias

    def __str__(self) -> str :
        return "weight:" + str(self.weights) + f", bias:{self.bias}"

    def stepFunc(self, x) -> int :
        return int(x >= 0)

    def process(self, x:np.ndarray) -> int :
        return self.stepFunc(np.sum(self.weights * x) + self.bias )

class NeuralNetWork :
    def __init__(
        self,
        nodes_per_layers:list,
        weights_of_perceptrons = None,
        bias_of_perceptrons = None,
        input_size_of_perceptrons = None,
        have_bias = False
    ) -> None:
        self.layers = []
        idx = 0
        for num_nodes in nodes_per_layers :
            layer = []
            for j in range(num_nodes) :
                if input_size_of_perceptrons :
                    layer.append(self.generatePerceptron(input_size_of_perceptrons[idx], have_bias))
                else :
                    layer.append(Perceptron(weights_of_perceptrons[idx], bias_of_perceptrons[idx]))
                    idx += 1
            self.layers.append(layer)

    def __str__(self) -> str :
        result = ""
        for i, layer in enumerate(self.layers) :
            result += f"layer[{i + 1}] : "
            for j, node in enumerate(layer) :
                result += str(node) + " "
            result += "     "
        return result[:-1]

    def generatePerceptron(self, input_size, have_bias) :
        if have_bias :
            return Perceptron(
                weights = np.array([np.random.uniform(-2, 2) for _ in range(input_size)]),
                bias    = np.random.uniform(-2, 2)
            )
        return Perceptron(np.array([np.random.uniform(-2, 2) for _ in range(input_size)]))

    def process(self, x) -> int :
        output = x
        for layer in self.layers :
            output = np.array(list(map( lambda node : node.process(output) ,layer )))
        return output[0]

if __name__ == "__main__" :

    found = False
    while not found :
        nn = NeuralNetWork([2, 1], input_size_of_perceptrons = [2, 2, 2], have_bias = True)
        if (
            nn.process(np.array((1,1))) == 1 
            and nn.process(np.array((1, 0))) == 0
            and nn.process(np.array((0, 1))) == 0
            and nn.process(np.array((0, 0))) == 1) :
            found = True
            print(nn)    


            