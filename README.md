    Copyright (c) 2012 Gotaly (gotawork@gmail.com)
    License: GNU GPLv3

    WhatHadHappend (W2H) 
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.  See the GNU General Public License 
    for more details.

#使用C实现的一个轻量级，调试级的日志系统

* 将文件IO单独出一个进程处理，减轻对宿主程序的压力，尽量减少宿主程序在日志
系统上的时间花费
* 通过两套配置链表和一个监视线程实现了对运行中的系统 提供热切换配置文件的可能
* 使用Lua作配置文件，借鉴CSS控制的概念，使得配置文件灵活，易书写 
* 日志接口做到了线程安全

##使用test
在test目录下运行scons编译example（需要安装Scons，替代了Makefile）

在代码中如test里面一样，一次调用
	w2h_init(config);
	w2h_log("class_name","id_name","your messages \n");
	w2h_finish();
便可以使用。init 和finish只需在开始和结尾处调用，而在想生成日志的时候调用log。

## 配置文件
配置文件采用lua文件提供，借鉴了CSS的控制理论。采用Class配合ID的方法。
一条日志可以属于多个classes，但是用唯一的id进行标识。其继承机制也类似
于CSS,出现在后面的class将会覆盖出现在前面的class,id的配置将会覆盖classes的配置。
一个示例：

	class.debug = {
		logfile_name = "$T.log",
		tag = "debug",
		time = "%y-%M-%d",
		app_name = "example0",
		data = "$t $T  $m",
	}

	id.debug_0 = {
		tag = "debug_0",
	}	
配置文件中class用class.class_name 的形式 表示名为class_name的class。用id.id_na
me 的形式表示名为id_name的ID。使用的时候，在程序中调用

	w2h_log("debug","debug_0","have a bug in file %s,line %d \n",__FILE__,__LINE__); 

便会生成名为 20xxxxxx.log 的日志文件。内容类似下面：

	2012-09-18 debug_0  have a bug in file example0.c,line 8 
可以看到根据配置文件成的日志内容。下面介绍日志中的占位符：

###tag
用来表示日志的tag

###app_name
用来表示应用的名称

### logfile_name 
要生成的日志文件的文件名，可以携带路径。

这里有个占位符，如上面示例的"$T",表示在生成的日志文件中，用时间 "年月日"来替换“$T”
如"test_$T.log"有可能会生成 test_20121223.log的21012年12月23日的日志文件

###time
表示日志文件中时间的格式
	
	%y 年
	%M 月
	%d 月中的莫一天
	%h 一天中的时
	%m 一个小时中的分钟
	%m 分钟中的秒
如 上面的"%y-%M-%d" 在日志中产生了 “ 2012-09-18”

### data
表示日志记录内容的格式

	%t 加入时间
	%T 加入Tag
	%a 加入app_name
	%m 加入用户调用w2h_log时给定的msg

如上面的 “data = "$t $T  $m” 产生了 "2012-09-18 debug_0  have a bug in file example0.c,line 8"


从上面可以看到，使用debug类控制了所有debug的日志属性，而具体的某条debug有可以用id来设置
他特有的属性值，如这里的tag。
