# EZOpenAPP-Linux
基于 [萤石云 Server SDK](https://open.ys7.com/lazydownload.html) 的 Linux Server 版本录制程序。

开发环境：

* Linux；
* g++；
* cmake；
* EZOpenSDK v1.3.0 20180829；

## 0x01 为啥搞这个？

使用萤石的监控，在某些场景下，仅需要出问题的时候，去看一下当时的回放。但是内置 SD 卡上的回放视频，不一定所有场景都能抓取到。

所以这时候，要么需要改进 SD 卡的录制算法，要么需要全量的视频，在发现问题时，找到对应时间段，进行详细视频的查看。

改进 SD 卡的录制算法，明显是不能控制的，所以只能退而选其次，录取所有时间段的视频。

但是只为了一个摄像头的视频录制，要开一台电脑，长期来看，是很不合算的（需要购买低功耗电脑，且要长期开启）。现在例如说树莓派、Intel Edison 这种简单的板子，很适合来做这种视频录制的工作。

## 0x02 开撸

萤石云提供的 Server SDK 是基于 CentOS，在其他 Linux 平台理论上也是可以编译运行的。

由于官方 `libezviz_streamclient.so` 文件的 ELF 头中，缺少部分引用到的 so 文件说明，需要手动添加一下，才能在其他平台良好的运行。

1. 安装 [patchelf](https://nixos.org/patchelf.html) 工具;

2. 修改 `libezviz_streamclient.so` 文件：

   ``` sh
   patchelf --add-needed libprotobuf.so libezviz_streamclient.so
   patchelf --add-needed libys_net.so libezviz_streamclient.so
   patchelf --add-needed libssl.so.1.0.0 libezviz_streamclient.so
   patchelf --add-needed libopensslwrap.so libezviz_streamclient.so
   ```

3. 编译：

   ``` sh
   cmake CMakeLists.txt;
   make;
   ```

## 0x03 开跑

设置链接 so 位置：

``` sh
export LD_LIBRARY_PATH=thirdparty/EZServerOpenSDK/libs
```

命令行参数：

``` shell
Usage:
  ./EZOpenApp-Linux --channel INTEGER32 --platform STRING --app_key STRING --serial STRING --safe_key STRING --token STRING
```

| 参数     | 含义             | 说明                                                         | 是否必填 |
| -------- | ---------------- | ------------------------------------------------------------ | -------- |
| channel  | 设备通道号       | 1                                                            | 否       |
| platform | 开放平台后台地址 | 国内默认地址为：`https://open.ys7.com`，海外默认地址为：`https://open.ezvizlife.com` | 是       |
| app_key  | 产品唯一标识     | 开发者应当在开放平台申请                                     | 是       |
| serial   | 摄像机序列号     | 在摄像机说明书或者摄像机上注明                               | 是       |
| safe_key | 摄像机验证码     | 在摄像机说明书或者摄像机上注明                               | 是       |
| token    | 访问令牌         | 用于校验接口访问/调用是否有权限，有效期为7天，有效期内不需要重复申请，可以重复使用 | 是       |



