# 项目: Linux 4G短信猫
## 项目流程图
![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/%E9%A1%B9%E7%9B%AE%E6%B5%81%E7%A8%8B%E5%9B%BE.png)



## 项目介绍
### 逻辑介绍
树莓派连接EC20 4G模块，编写程序实现PPP智能拨号上网控制和短信猫功能，该程序采用多线程编程模型
实现相应模块功能控制。其中这些模块包括：
(1)PPP拨号上网模块，该模块实现实时监测以太网、WiFi网卡的联网情况，如果上述网络断线则自动切换到
4G拨号上网；一旦以太网、WiFi联网后就自动断开4G连接；
(2)网络Socket模块，该模块采用libevent库监听socket相应端口，等待网络客户端的连接并进行登录认证。
身份认证成功后，客户端可以通过网络socket与服务器进行长连接通信实现短信的收发功能；其中网络
socket客户端与服务器之间的通信采用JSON格式，登录验证时，用户名与密码的报文采用MD5进行加密；
(3)SMS模块，该模块分为两个子模块，分别是与串口进行通信的AT指令收发模块以及PDU编解码模块；两个
子模块在底层均进行了多层的封装调用，最终在上层实现短信的发送与获取以及4G模块使用情况的监测等
功能。


## 运行截图
### SMS线程
#### 客户端用户发送的短信(PDU)：
![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/%E6%A8%A1%E5%9D%97%E5%8F%91%E9%80%81%E7%9F%AD%E4%BF%A11.png)

![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/%E6%A8%A1%E5%9D%97%E5%8F%91%E9%80%81%E7%9F%AD%E4%BF%A12.png)

#### 手机接收短信:
![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/%E6%89%8B%E6%9C%BA%E6%8E%A5%E6%94%B6.png)

#### 手机发送短信:
![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/%E6%89%8B%E6%9C%BA%E5%8F%91%E9%80%81.png)

#### 模块接收短信（TEXT,PDU）：
![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/%E6%A8%A1%E5%9D%97%E6%8E%A5%E6%94%B61.png)

![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/%E6%A8%A1%E5%9D%97%E6%8E%A5%E6%94%B62.png)

-
-
-
-
### PPP拨号线程

#### 未运行PPP拨号脚本，只有默认网卡
![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/%E7%A8%8B%E5%BA%8F%E8%BF%90%E8%A1%8C%E5%89%8D%E6%9C%AA%E4%BD%BF%E7%94%A8ppp%E6%8B%A8%E5%8F%B7.png)

#### PPP拨号后，出现ppp0网卡
![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/ppp%E6%8B%A8%E5%8F%B7%E5%90%8E%E6%9C%89ppp0%E7%BD%91%E5%8D%A1.png)

#### ping命令测试ppp0网卡，通过丢包率判断网卡可用性
![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/ppp%E6%8B%A8%E5%8F%B7%E4%B8%A2%E5%8C%85.png)

#### 网卡可用
![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/ppp0%E5%8F%AF%E7%94%A8.png)

#### PPP拨号脚本截图
![image](https://github.com/luxiaoyang666/G4_SMS_CAT/blob/master/pro_pic/ppp%E6%8B%A8%E5%8F%B7%E8%BF%90%E8%A1%8C%E8%84%9A%E6%9C%AC.png)





