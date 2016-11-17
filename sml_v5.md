#sml_v5 更新说明
此版本的升级是为后续可变主频的实现，

变成单步执行，未来会添加超时判断，

利用**windows api** 
``` C
    QueryPerformanceFrequency(&feq);//每秒跳动次数,windows下ns级精度
    QueryPerformanceCounter(&t1);//测前跳动次数
```
实现微秒级时钟性能查看，

* 添加了benchmark.sal性能测试代码。运行时间与理论分析大致相符。

winxos 2016-11-18