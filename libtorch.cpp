#include <torch/torch.h>
#include<torch/script.h>
#include<iostream>
#include<vector>
#include<memory>
using namespace std;

int main(int argc,char *argv[]) {
    // torch::Tensor tensor = torch::rand({2, 3});
    // std::cout << tensor << std::endl;

    const bool use_cuda=false;
    
    // auto input=3.0;
    const string model = "trace_model.pth";
    vector<torch::jit::IValue> inputs;//注意数据类型
    // inputs.push_back(torch::ones({1}));
    inputs.push_back(torch::tensor({20.0}));//数据必须为tensor
    torch::jit::Module module=torch::jit::load(argv[1]);//在make编译成功后，执行./libtorch ../trace_model.pth
    cout<<"ok\n";

    // const string model = "trace_model.pth";
    // auto model_out=torch::jit::load(model);
    // auto input1= toTensor(input);
    auto output = module.forward(inputs).toTensor();//
    //cout<<output<<endl;
    cout<<output<<endl;
    return 0;
}