import enum
from copy import deepcopy
import random


class Node :
    def __init__(self, *parameters, input_size = None) -> None :
        if input_size :    # initialize parameter self.param with random values with size input_size
            self.params = [random.randint(0, 6) - 3 for i in range(input_size + 1)]
        else :             # initialize prameter by setting to passed arguement parameters
            self.params = parameters

    def __str__(self) -> str :
        result = ""
        for i, layer in enumerate(self.layers) :
            result += f"layer {i+1} : "
            for j , node in enumerate(layer) :
                result += str(node.params) + " "
        return result

    def stepFunc(self, x) -> int :
        return int(x >= 0)

    def proceed(self, *inputs_) -> int :
        inputs_ = list(inputs_)
        inputs_.append(1)
        if len(inputs_) != len(self.params) :
            return -1
        sum = 0
        for i in range(len(inputs_)) :
            sum += self.params[i] * inputs_[i]
        #print(f"inputs_:{inputs_}, params : {self.params}, sum : {sum}, ret:{self.stepFunc(sum)}")
        return self.stepFunc(sum)

class NeuralNetWork :
    def __init__(self, nodes_per_layers, paramss = None, input_size = None) :
        self.layers = []
        idx = 0
        for i, n in enumerate(nodes_per_layers) :
            layer = []
            for j in range(n) :
                if input_size :
                    layer.append(Node(input_size = input_size))
                else :
                    layer.append(Node(*paramss[idx]))
                idx += 1
            self.layers.append(layer)

    def __str__(self) -> str :
        result = ""
        for i, layer in enumerate(self.layers) :
            result += f"layer[{i + 1}] : "
            for j, node in enumerate(layer) :
                result += str(node.params) + " "
            result += "     "
        return result[:-1]

    def proceed(self, *inputs_) -> int :
        for layer in self.layers :
            output = []
            for node in layer :
                output.append(node.proceed(*inputs_))
            #print("inputs_ :", inputs_, " , outputs : ", output)
            inputs_ = deepcopy(output)
        return output[0]


if __name__ == "__main__" :

    found = False
    while not found :
        nn = NeuralNetWork([2, 1], input_size = 2)
        if (nn.proceed(1, 1) == 1 and nn.proceed(0, 1) == 0 and nn.proceed(1, 0) == 0 and nn.proceed(0, 0) == 1) :
            found = True
            print(nn)    