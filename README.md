# MBED-TOOLS

## HY_UART_DBUG_V10A
![正面](https://github.com/xxxlzjxxx/MBED-TOOLS/blob/master/DOC/HY_UART_DBUG_V10A-TOP.png)
![背面](https://github.com/xxxlzjxxx/MBED-TOOLS/blob/master/DOC/HY_UART_DBUG_V10A-BOTTOM.png)

### 使用说明
1. 安装USB转串口芯片驱动。根据操作系统下载对应的驱动程序：[https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers](CP210x USB to UART Bridge VCP Drivers)。
2. 使用方头USB type B插头连接PCB。J1跳线使用self powered模式，同时F2焊接/F1不焊。此时所有器件功率均来自USB总线。
![驱动安装成功图示](https://github.com/xxxlzjxxx/MBED-TOOLS/blob/master/DOC/LAN9514-CP2105.png)
3. 设备管理器中所示Enhanced COM Port和Standard COM Port与PCB上丝印所示一一对应。其中Standard COM Port提供TTL电平的串口通信排针与DB9公头插座的232电平的串口通信插座。Enhanced COM Port提供RS485通信插座。LAN9512/LAN9514 USB 2.0 to Ethernet 10/100 Adapter为标准百兆以太网接口。同时PCB提供3个USB2.0速率的接口。
4. 通用串行总线interface features：
Standard COM Port：
数据格式 | 8位数据位，1位停止位 
校验     | 奇、偶、无校验       
波特率   | 2400 bps - 921600 bps
缓冲大小 | 288 Byte             
Enhanced COM Port：
数据格式 | 5、6、7、8位数据位，1、1.5、2位停止位 
校验     | 奇、偶、标记、空格、无校验            
波特率   | 300bps - 2Mbps                        
缓冲大小 | 320 Byte              
5. _备注_ 。如果外设功耗过高，需要对PCB修改为DC插座供电，将J1切换为bus powered，F2不焊/F1焊接。DC电源输入电压范围为5V-18V。