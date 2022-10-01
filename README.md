![image](https://user-images.githubusercontent.com/29084184/193403886-5f05893c-74b2-404d-805e-b008ae43595b.png)


# 板球控制系統 BallPlate

2017年全国大学生电子设计竞赛B题 板球控制系統/滾球系統/BallPlate 赛题解析+源代码开源

此份代码基于stm32F407，开发板使用正点原子探索者，摄像头也是正点原子的OV2640摄像头，两路PWM。一个在PF9一个在PF7。频率50HZ，PID定时器中断20MS,进行了软件二值化，并用极其简单的算法提取质心。PID使用智能车常见的PD控制，参数还需要再仔细调整。摄像头帧率在27-28帧左右。舵机使用MG996R，很常见，驱动电压5.9v,采用大功率稳压器件。由锂电池稳压驱动舵机。锂电池11.4v 3S. 

## 核心任务

在边长为 65cm 光滑的正方形平板上均匀分布 着 9 个外径 3cm 的圆形区域，其编号分别为 1~9 号，位置如图 1 所示。设计一控制系统，通过控制 平板的倾斜，使直径不大于 2.5cm 的小球能够按照 指定的要求在平板上完成各种动作，并从动作开始 计时并显示，单位为秒。

![image](https://user-images.githubusercontent.com/29084184/193403930-e80f00b3-179f-4373-940c-1a745eaed47d.png)


# Overview

<table>
<tbody>
  <tr>
    <td>
      两个版本
    </td>
    <td>
      电阻屏版板球控制系统
    </td>
    <td>
      摄像头版板球控制系统
    </td>
  </tr>
  <tr>
    <td>
      成品展示
    </td>
    <td>
      <img src="https://user-images.githubusercontent.com/29084184/193402921-98679929-0995-46e7-80cb-f9826b0f1a7d.png" width="343"></img>
    </td>
    <td>
      <img src="https://user-images.githubusercontent.com/29084184/193403692-1cf53f38-1fd3-490b-b683-da388e7109c0.png" width="343"></img>
    </td>
  </tr>
  <tr>
    <td>
      演示视频链接
    </td>
    <td>
      <a href="https://tbm-auth.alicdn.com/e99361edd833010b/7HYn3NCygCNo85lnY2r/9JFMNxFTDipkILJFOG3_263176200462_hd_hq.mp4?auth_key=1664619498-0-0-b45ee0804955938d5325e6775070cce5&t=212c147016646167985924857ea681&b=video_plus&p=cloudvideo_http_seller_sucai_vod_publish" target="_blank"> 📹 mp4 </a>
    </td>
    <td>
      <a href="https://tbm-auth.alicdn.com/e99361edd833010b/7HYn3NCygCNo85lnY2r/4qZ7j7nqCNLWa4LhUfm_271671256315_hd_hq.mp4?auth_key=1664619524-0-0-45e8c25f226a35dd72b821c1119b2858&t=212c147016646168242006660ea681&b=video_plus&p=cloudvideo_http_seller_sucai_vod_publish" target="_blank"> 📹 mp4 </a>
    </td>
  </tr>
  <tr>
    <td>
      作品参数
    </td>
    <td>
        <img src="https://user-images.githubusercontent.com/29084184/193403434-f8e985dd-0df7-40a9-8085-c6de351fc3db.png" width="343" ></img>
    </td>
    <td>
        <img src="https://user-images.githubusercontent.com/29084184/193403704-c7fc1a01-c742-4419-bff3-361bcc89688a.png" width="343" ></img>
    </td>
  </tr>
</tbody>
</table>


# 声明
<b>此份代码纯属开源，抛砖引玉，请不要拿去做倒卖以及牟利工作。谢谢！</b>

此份代码基于stm32F407，开发板使用正点原子探索者，摄像头也是正点原子的OV2640摄像头，两路PWM。一个在PF9一个在PF7。频率50HZ，PID定时器中断20MS,进行了软件二值化，并用极其简单的算法提取质心。PID使用智能车常见的PD控制，参数还需要再仔细调整。摄像头帧率在27-28帧左右。舵机使用MG996R，很常见，驱动电压5.9v,采用大功率稳压器件。由锂电池稳压驱动舵机。锂电池11.4v 3S. 

打赏链接：用于群管理和扩充群

<!--START_SECTION:sponsors-->
<a href="https://charmve.github.io/sponsor.html" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-red.png" alt="Buy Me A Coffee" width="150" ></a>
<!--
<p align="center">
  <a href="https://cdn.jsdelivr.net/gh/YunYouJun/sponsors/public/sponsors.svg">
    <img src='https://cdn.jsdelivr.net/gh/YunYouJun/sponsors/public/sponsors.svg'/>
  </a>
</p>
<!--END_SECTION:sponsors-->

# 历届电赛题目开源项目

- 2019年：模拟电磁曲射炮（H题）https://github.com/Charmve/SimElectronicGun
- 2017年：板球控制系统（B题）https://github.com/Charmve/BallPlate
- 2015年：风力摆控制系统（B题）https://github.com/Charmve/Wind-Pendulum-Controlling-System

其他嵌入式系统设计开源项目：

- 3D 全彩高阶光立方 [[EmotionCube](https://github.com/Charmve/EmotionCube)] | [[LightCube](https://github.com/Charmve/LightCube)]
- 电子信息、自动化、电子工程等专业课程设计/大作业 https://github.com/Charmve/Practicum4ECE

