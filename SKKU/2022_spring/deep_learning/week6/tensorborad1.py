import math
import torch
from tensorboradX import SummaryWriter

writer = SummarayWriter(logdir="scalar/sin&cos")

for step in range(-360, 360) :
    angle_rad = step * math.pi / 180
    writer.add_scalars("sin and cos", {"sin": math.sin(angle_rad), "cos": math.cos(angle_rad)})

writer.close()

        