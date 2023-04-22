import torch.nn as nn
import torch
import matplotlib.pyplot as plt
class liner(nn.Module):
    def __init__(self):
        super(liner, self).__init__()
        self.lin=nn.Linear(1,1)
    def forward(self,x):
        y_pre=self.lin(x)
        return y_pre
model=liner()
model.eval()
cirt=nn.MSELoss()
x_data=torch.tensor([[1.0],[2.0],[3.0]])
y_data=torch.tensor([[2.0],[4.0],[6.0]])
oper=torch.optim.SGD(model.parameters(),lr=0.01)
for epoch in range(10000):
    print("test")
    y_pre=model(x_data)
    loss=cirt(y_data,y_pre)
    print(epoch,loss.item())
    oper.zero_grad()
    loss.backward()
    oper.step()
# print("w={}, b={}".format(model.lin.weight.item(),model.lin.bias.item()))

traced_model=torch.jit.trace(model,x_data)
traced_model.save("trace_model.pth")
print(model.lin.bias)
# plt.plot(x_data,model.lin.weight.item()*x_data+model.lin.bias.item(),color='b')
# plt.scatter(x_data,y_data,color='red')
# plt.show()

x_test=torch.tensor([1.0])
y=model(x_test)
print("y=",y)