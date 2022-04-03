import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

X_train = torch.FloatTensor(
    [0, 0, 0, 1, 1, 0, 1, 1]
).view(-1, 2)

y_train = torch.FloatTensor(
    [0, 1, 1, 0]
).view(-1, 1)

class XORnet(nn.Module) :
    def __init__(
        self,
        n_hid,     # number of hidden layers
        hid_nodes  # number of nodes in hidden layers
    ) -> None:
        super(XORnet, self).__init__()

        def addHiddenLayer(n_hid, hid_nodes) :
            """
            generator that generates  hidden
            nn.Linear()
            """
            for i in range(n_hid) :
                yield nn.Linear(hid_nodes, hid_nodes)
                yield nn.Sigmoid()

        layers = [
            nn.Linear(2, 10),
            nn.Sigmoid()
        ] + list(addHiddenLayer(n_hid, hid_nodes)) + [
            nn.Linear(10, 1),
            nn.Sigmoid()
        ]

        self.my_layer = nn.Sequential(*layers)

    def forward(self, X) :
        return self.my_layer(X)


def train(
    model,
    X_train,
    y_train,
    criterion    = nn.BCELoss(),
    optimizer    = optim.SGD,
    lr           = 1e-1,
    epochs       = 100000,
    logging_freq = 5000
) :
    optimizer_ = optimizer(model.parameters(), lr=lr)
    for epoch in range(epochs) :
        # calculate H(x)
        prediction = model(X_train)

        # calculate cost (= loss)
        cost = criterion(prediction, y_train)

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
