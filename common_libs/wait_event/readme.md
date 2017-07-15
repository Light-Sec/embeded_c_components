#一种自定义事件的异步回调处理框架



应用程序，有时会需要等待某种事件，当事件发生时需要对该事件执行具体动作。



- **实现功能**

- **实例代码**



-------------------



## 实现功能
应用程序可以在初始化时，创建一个自定义的等待事件wait_event。

当需要等待该事件触发时，应用程序可以注册一个带超时时间ms、事件发生时执行的具体动作回调cb、回调可带参数cb_data。

当事件发生时，执行该回调函数。如果超时时间达到内，该事件还没发生，则超时会自动注销该等待事件。


## 实例代码


详见：`event.c`实现。