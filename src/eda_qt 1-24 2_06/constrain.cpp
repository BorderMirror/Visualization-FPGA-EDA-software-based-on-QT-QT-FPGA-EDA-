#include "constrain.h"

constrain::constrain()
{

}

constrain::constrain(QString name,int inputPorts,int outputPorts,int inOutPorts)
{
    this->name = name;
    this->latestNum = 0;
    for(int i = 0;i<inputPorts;i++,this->latestNum++)
    {
        this->ports.push_back(Port("p"+QString::number(this->latestNum),INPUT,0,1,this->latestNum));
    }
    for(int i = 0;i<outputPorts;i++,this->latestNum++)
    {
        this->ports.push_back(Port("p"+QString::number(this->latestNum),OUTPUT,0,1,this->latestNum));
    }
    for(int i = 0;i<inOutPorts;i++,this->latestNum++)
    {
        this->ports.push_back(Port("p"+QString::number(this->latestNum),INOUT,0,1,this->latestNum));
    }
}

Port constrain::getSelectedPort(int portNum)
{
    for(unsigned long i = 0;i<this->ports.size();i++){
        if(this->ports.at(i).getPortNum()==portNum)
            return this->ports.at(i);
    }
    return Port();
}

void constrain::addPort()
{
    this->ports.push_back(Port("p"+QString::number(this->latestNum),INPUT,0,1,this->latestNum));
}

void constrain::deletePort(int portNum)
{

    if(this->ports[portNum].getPortType()==INPUT){
       this->inputPorts--;
    }else if(this->ports[portNum].getPortType()==OUTPUT) {
       this->outputPorts--;
    }else{
        this->inOutPorts--;
    }
    for(unsigned long i = 0;i<this->ports.size();i++){
        if(this->ports.at(i).getPortNum()==portNum)
            this->ports.erase(this->ports.begin()+i);
    }
}

void constrain::setCode(QString code)
{
    this->code = code;
}

QString constrain::getCode()
{
    return this->code;
}

QString constrain::generateCodeAltera()//生成约束文件代码；还没研究完
//生成的是Altera芯片在Quartus下的
{

    QString generateCodes;
    generateCodes = "#This code is generated by :\n#Pin Assignment for Altera FPGA with Software Quartus.\n";

    for(unsigned long i = 0;i<this->ports.size();i++){
        generateCodes = generateCodes + "set_location_assignment PIN_" + this->ports.at(i).getName() +" -to" + "所包含的module连接的端口\n";
    }

    return generateCodes;
}

QString constrain::generateCodeXilinx()//生成约束文件代码；还没研究完
//生成的是Xilinx芯片在Vivado下的
{
    QString generateCodes;
    generateCodes = "#This code is generated by :\n#Pin Assignment for Xilinx FPGA with Software Vivado.\n";
    for (unsigned long i = 0;i<this->ports.size();i++) {
        generateCodes = generateCodes + "set_property PACKAGE_PIN " + this->ports.at(i).getName() + " [get_ports 所包含的module连接的端口\n]";
        generateCodes = generateCodes + "set_property IOSTANDARD LVCMOS33 [get_ports 所包含的module连接的端口\n]";
    }
    return generateCodes;
}