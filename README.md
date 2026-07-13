# 51-rtu-reg-tamper
基于C和python完成一些工控操作，供初学者参考
# 51 ICS EEPROM Tamper Demo

> 网安（嵌入式/工控方向）大二下暑假实践  
> 51 单片机 + AT24C02 模拟工控 RTU，串口 READ/SET 无鉴权 + LA 抓 I2C + Python 篡改

## 硬件
- 51 开发板（AT89C52 / 12MHz）
- AT24C02（I2C EEPROM，4 字节计数器存 0x00–0x03）
- CH340 串口
- 逻辑分析仪（24M 8ch）

## 目录
- `code/` — 51 源码（Keil5）
  - main.c：EEPROM 4B 读写 + 串口 READ/SET + 按键+1 + 超时判定
- `la/` — PulseView 截图（UART READ 4B 连续 / I2C 写帧解码）
- `scripts/` — Python 攻击脚本（pyserial + struct）

## 攻击链
1. 串口 `SET 1234` → EEPROM 被改（无鉴权）
2. LA 抓 I2C：`Device 0x50, Addr 0x00, Data 31 32 33 34`
3. 串口 `READ` → 回 4 字节（struct 解析）

## 对应工控场景
- PLC 保持寄存器未鉴权篡改
- 配置 EEPROM 离线提取（Stuxnet 类思路微型版）
- 调试口 UART shell 未鉴权

## 运行
