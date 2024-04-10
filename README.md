# ESP32C3采集设备

adc采集：gpio4 对应 ADC_CHANNEL_4
`idf.py add-dependency "espressif/esp_websocket_client^1.2.3"`添加websocket依赖
## 墨水屏驱动

使用微雪驱动方案，移植微雪驱动到ESPIDF环境中

墨水屏使用2.13寸bc

目录结构：

- DEV_CONFIG：适配不同平台，例如延时，gpio，spi。配置gpio引脚
- FONT：字体库
- e-paper：spi与墨水屏通信
- EXAMPLE：驱动墨水屏示例
- GUI：控制绘图，调用spi

---



步骤：

1. gpio初始化：初始化DC，RST，BUSY gpio
2. spi初始化
3. 定义一个指针变量存储图像，通过GUI绘图保存在变量中 ，绘图完后调用e- paper中spi通信控制墨水屏

## websocket

>Flask：服务器开发，websocket等
>
>Vue：前端开发

前端：通过id连接设备，渲染数据

后端：

- 心跳机制
- 记录信息：id，ip，连接事件
- 建立连接，选择设备id转发至前端
- 认证信息
- 错误处理