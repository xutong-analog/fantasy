#include <stdio.h>

#define SCL_h printf(" SCL h \r\n")
#define SCL_l printf(" SCL l ")
#define SDA_h printf("SDA h")
#define SDA_l printf("SDA l")

void IIC_Start(void);
void IIC_Stop(void);
//返回值是ACK信号，
//若是有ACK信号则返回0,若是没有ACK信号则返回1
u_int8_t IIC_Write(u_int8_t Data);
void IIC_DUT_W(u_int8_t DUT_ADDR,u_int8_t REG,u_int16_t Data);
u_int16_t IIC_DUT_R(u_int8_t DUT_ADDR);
u_int8_t IIC_Read(void);
u_int8_t R_SDA=0;

int main() {
    u_int8_t A;
    u_int16_t B=0x00;
    B=IIC_DUT_R(0x12);
    printf("%X\r\n",B);
    return 0;
}
void IIC_Start(void)
{
    SDA_h;
    SCL_h;
    SDA_l;
    printf("IIC/Start \r\n");
}
void  IIC_Stop(void)
{
    printf("IIC/Stop \r\n");
    SDA_l;
    SCL_h;
    SDA_h;

}
/*
 * IIC读取8bit数据
 */
u_int8_t IIC_Read(void)
{
    u_int8_t Data;
    for (int i = 0; i < 8; ++i) {
        Data<<=1;
        SCL_l;
        if(R_SDA==1)
            Data|=0X01;
        SCL_h;
    }
    // ACK Signal
    SCL_l;
    SDA_l;
    SCL_h;
    return Data;
}
/*
 * IIC 写8bit数据
 * 返回值ACK信号
 */
u_int8_t IIC_Write(u_int8_t Data)
{
    // 设置一个wait等待ack信号
    u_int8_t wait=0;
    printf("IIC Write Data\r\n");
    for (int i = 0; i < 8; ++i) {
        SCL_l;
        if((Data&0X80)==0X80)
            SDA_h;
        else
            SDA_l;
        //Data左移一位
        Data<<=1;
        SCL_h;
    }
    SCL_l;
    SDA_h;
    SCL_h;
    while(R_SDA)
    {
        wait++;
        if(wait==255)
        {
            //超时无应答关闭本次传输
            IIC_Stop();
            printf(" NACK\r\n");
            return 1;
        }
    }
    SCL_l;
    printf("ACK \r\n");
    return 0;
}
/*
 *  IIC_DUT_W(u_int8_t DUT_ADDR,u_int8_t REG,u_int16_t Data)
 *  DUT ADDR 代表器件的地址 IIC总线上会有很多器件，如何确定他的地址通过
 *  DUT_ADDR 来锁定器件地址
 *  REG 代表CSD203的寄存器地址
 *  Data 代表要写入寄存器的数据
 */
void IIC_DUT_W(u_int8_t DUT_ADDR,u_int8_t REG,u_int16_t Data)
{
    u_int8_t DataH,DataL;
    //将高8位向右移8位
    DataH=Data>>8;
    //屏蔽掉高8位只保留低8位
    DataL=Data&0X00ff;
    //将最后1个bit设置为0表示对
    //这个地址写数据
    DUT_ADDR=DUT_ADDR&0XFE;
    IIC_Start();
    IIC_Write(DUT_ADDR);
    IIC_Write(REG);
    IIC_Write(DataH);
    IIC_Write(DataL);
    IIC_Stop();
}
/*
 * IIC 根据地址读取16bit 数据
 */
u_int16_t IIC_DUT_R(u_int8_t DUT_ADDR)
{
    u_int16_t Data;
    //将最后1个bit设置为1表示对
    //这个地址读数据
    DUT_ADDR=DUT_ADDR|0X01;
    IIC_Start();
    //IIC_Write(DUT_ADDR);
    Data=IIC_Read();
    //将数据往上移8bit
    Data<<=8;
    Data=IIC_Read();
    IIC_Stop();
    return Data;
}