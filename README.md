# 项目: Linux 4G短信猫
## 项目流程图
![image](https://github.com/xxx/xx.png)



## 项目介绍
### 逻辑介绍
程序运行，解析命令行参数与配置文件，根据配置文件要求判断线程的使能与否执行相应线程.
PPP拨号线程通过配置文件传入的检测网卡进行树莓派联网检测，若wifi/以太网联网则使用，否则进行PPP拨号4G上网，模块会轮询检测wifi/以太网的联网状况，若恢复则使用wifi/以太网上网。
SMS线程使用libevent库实现多客户端的并发访问，可以接收多客户的连接并在验证通过后为其发送短信，也可以查询客户端绑定的电话号码的短信.
其中，两个线程在执行时都会实时监测sim卡的使用情况，若sim卡不可用则程序退出，并记录日志.


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
