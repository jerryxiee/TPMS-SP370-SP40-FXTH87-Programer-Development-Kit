# TPMS SP370 SP40 XTH87 Development Kit
For TPMS SP370 SP40 FXTH87 Programer Development Kit

## Introduce TPMS

Tire Pressure Monitoring System（TPMS），轮胎压力监测系统，TPMS的作用是在汽车行驶过程中对轮胎气压进行实时自动监测，并对轮胎漏气和低气压进行报警，以确保行车安全。


## 目前市场上主要有如下3种胎压方案

**SP370：** 
![SP370](https://img-blog.csdnimg.cn/20210305165313791.png#pic_center)
英飞凌SP370是市场上占用率最高(目前已停产，由SP40替代)，也是最早一颗集成气压、温度、加速度、电源管理、RF于一体的芯片。如此高的集成度，以至于实现了单芯片方案。
而在英飞凌SP370问世之前，胎压普遍采用2-3个主芯片（传感器+无线RF收发+电源管理）来组成一个具备完整功能PCBA，这样子导致了成本高，功耗高，元器件多以至于无法将体积做小等缺点

**FXTH87：**
![FXTH87](https://img-blog.csdnimg.cn/20210305165408275.png#pic_center)
 飞思卡尔的FXTH87是2014年推出的芯片，其基本性能都是针对SP370的特性做了一些提升，具备XZ双轴加速度（双轴加速度可做4轮定位），具备ADC采样，芯片单价略高与SP370与SP40。FXTH87我测试过程中，感觉发射性能略低于SP370与SP40，也可能是匹配没做好的缘故！

**SP40：** 
![SP40](https://img-blog.csdnimg.cn/20210305165339882.png#pic_center)
为SP370的升级款，体积更小，功耗更低，FLASH大小增大至12K，无线发射性能略优于SP370，而且芯片单价更低。

## The difference of the senser

<table>
	<tr>
		<th>系列</th>
		<th>Product</th>
		<th>Core</th>  
		<th>Pressure</th>
		<th>FLASH</th>
		<th>size</th>
		<th>accelerated</th>
		<th>Pressure pre,temperature pre,Standby current</th>
		<th>IDE</th>
	</tr >
	<tr >
		<td rowspan="3">SP370</td>
		<td>SP370-2510</td>
		<td rowspan="3">8051</td>
		<td>100~450Kpa</td>
		<th rowspan="3">6K</th>
		<th rowspan="3">9.24*11.09*3.9</th>
		<th rowspan="3">single Z</th>
		<th>±7Kpa,±7℃,700nA</th>
		<td rowspan="3">KEIL</td>
	</tr>
	<tr >
	    <td>SP370-2511</td>
	    <td>100~900Kpa</td>
	     <th>±14Kpa,±7℃,700nA</th>
	</tr>
		<tr >
	    <td>SP370-2315</td>
	    <td>100~1300Kpa</td>
	     <th>±23Kpa,±7℃,700nA</th>
	</tr>
<tr >
	    <td rowspan="3">SP40</td>
	    <td>SP40-11-01</td>
	    <td rowspan="3">8051</td>
	    <td>100~900Kpa</td>
	    <th>12K</th>
	     <th rowspan="3">8.9*5.4*3.4</th>
	     <th rowspan="3">single Z</th>
	      <th>±1.37Kpa,±3℃,245nA</th>
	      <td rowspan="3">KEIL</td>
	</tr>
	<tr >
	    <td>SP40-11-11</td>
	    <td>100~900Kpa</td>
	    <th rowspan="2">12+2K</th>
	     <th>±1.37Kpa,±3℃,245nA</th>
	</tr>
		<tr >
	    <td>SP40-15-11</td>
	    <td>100~1300Kpa</td>
	     <th>±1.37Kpa,±3℃,245nA</th>
	</tr>
	<tr >
		<td rowspan="3">FXTH87</td>
		<td>FXTH87</td>
		<td rowspan="3">S08</td>
		<td>100~900Kpa</td>
		<th>8K</th>
		<th rowspan="3">9.24*11.09*3.9</th>
		<th rowspan="3">double X、Z</th>
		<th>±10Kpa,±3℃,500nA</th>
		<td rowspan="3">CodeWarrior</td>
	</tr>
	<tr >
	    <td>FXTH8715</td>
	    <td>100~1500Kpa</td>
	    <th>8K</th>
	     <th>±20Kpa,±3℃,500nA</th>
	</tr>
		<tr >
	    <td>FXTH87E</td>
	    <td>100~900Kpa</td>
	    <th>8+8K</th>
	     <th>±5Kpa,±3℃,180nA</th>
	</tr>
</table>




## Development Kit Demo

<img src="https://img-blog.csdnimg.cn/20210306143526705.jpg" width="40%"> <img src="https://img-blog.csdnimg.cn/20210306143748122.jpg" width="56%">
<img src="https://img-blog.csdnimg.cn/20210306144015829.jpg" width="40%"> <img src="https://img-blog.csdnimg.cn/2021030614401498.jpg" width="40%">
<img src="https://img-blog.csdnimg.cn/20210306144245677.jpg" width="40%"> <img src="https://img-blog.csdnimg.cn/20210306144259580.jpg" width="40%">





# [Buy Development Kit](https://shop143472971.taobao.com/)

## Facebook: WaliTool



![在这里插入图片描述](https://img-blog.csdnimg.cn/20210305173123410.png#pic_center)





