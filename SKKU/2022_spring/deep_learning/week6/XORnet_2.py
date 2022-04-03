from cv2 import moments
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

from XORnet import X_train

class XORnet(nn.Module) :
    def __init__(
        self,
        n_hid,     # number of hidden layers
        hid_nodes, # number of nodes in hidden layers
        device = "cpu"
    ) -> None:
        super(XORnet, self).__init__()

        def addHiddenLayer(n_hid, hid_nodes) :
            """
            generator that generates  hidden
            nn.Linear()
            """
            for i in range(n_hid) :
                yield nn.Linear(hid_nodes, hid_nodes)
                yield nn.LeakyReLU()
                #yield nn.Sigmoid()

        layers = [
            nn.Linear(2, 10),
            nn.Sigmoid()
        ] + list(addHiddenLayer(n_hid, hid_nodes)) + [
            nn.Linear(10, 1),
            nn.Sigmoid()
        ]

        self.my_layer = nn.Sequential(*layers).to(device)

    def forward(self, X) :
        return self.my_layer(X)


def getDevice() :
    return 'cuda' if torch.cuda.is_available() else 'cpu'


def getData(device) :
    X_train = torch.FloatTensor(
        [-1, 0, 0, 1, 1, 0, 1, 1]
    ).view(-1, 2).to(device)

    y_train = torch.FloatTensor(
        [0, 1, 1, 0]
    ).view(-1, 1).to(device)

    return X_train, y_train


def train(
    model,
    X_train,
    y_train,
    criterion    = nn.BCELoss,
    optimizer    = optim.Adam,
    lr           = 1e-1,
    epochs       = 100000,
    logging_freq = 5000,
    device       = "cpu"
) :
    criterion_ = criterion().to(device)
    optimizer_ = optimizer(model.parameters(), lr=lr)
    for epoch in range(epochs) :
        # calculate H(x)
        prediction = model(X_train)

        # calculate cost (= loss)
        cost = criterion_(prediction, y_train)

        # clear optimizer's grad
        # because optimizer accumulates grad.
        optimizer_.zero_grad()

        # update grad of modle's parameter tensors
        cost.backward()

        # update model's parameter
        optimizer_.step()

        if epoch % logging_freq == 0 :
            print(f"epoch:{epoch}/{epochs}\t\tcost:{cost.item()}")


def evaluate(model, X, y) :
    with torch.no_grad() :
        hypothesis = model(X)
        predicted = (hypothesis > 0.5).float()
        accuracy = (predicted == y).float().mean()

        print(f"model output : {hypothesis.tolist()}")
        print(f"prediction   : {predicted.tolist()}")
        print(f"ground truth : {y.tolist()}")
        print(f"accuracy     : {accuracy.item()}")
