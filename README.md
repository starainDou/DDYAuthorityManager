# [DDYAuthManager](https://github.com/RainOpen/DDYAuthManager)

![DDYAuthManager.png](https://github.com/starainDou/DDYDemoImage/blob/master/DDYAuthManager.png)  ![DDYAuthManager2.png](https://github.com/starainDou/DDYDemoImage/blob/master/DDYAuthManager2.png)

* 各种权限验证管理，麦克风权限，相机权限，相册，日历，备忘录，联网权限，推送通知权限，定位权限，语音识别权限等等

* 各种权限申请(有的不支持二次申请，比如联网权限，在国行版iOS10+一个bundleID只会询问一次)

* 只有有权限才能下一步操作


> # 集成

* CocoaPods方式 

  1.pod 'DDYAuthManager', '~> 1.0.0' 
 
  2.#import <DDYAuthManager.h>

* 文件夹拖入工程方式
  
  1.下载工程解压后将'DDYAuthManager'文件夹拖到工程中

  2.#import "DDYAuthManager.h"



> # 使用

### 录音(麦克风)权限

* 鉴定权限和请求权限统一

```
[DDYAuthManager ddy_AudioAuthAlertShow:YES success:^{ } fail:^(AVAuthorizationStatus authStatus) {}];

// 也可以用 [[AVAudioSession sharedInstance] requestRecordPermission:^(BOOL granted) { }];请求录音权限
```


### 相机(摄像头)权限

* 鉴定权限和请求权限统一


```
[DDYAuthManager ddy_CameraAuthAlertShow:YES success:^{ } fail:^(AVAuthorizationStatus authStatus) {}];

// 可以先检查摄像头可用性 [DDYAuthManager isCameraAvailable]
```


### 图片(相册)权限

* 鉴定权限和请求权限统一

```
[DDYAuthManager ddy_AlbumAuthAlertShow:YES success:^{} fail:^(PHAuthorizationStatus authStatus) {}];
```


### 通讯录(联系人)权限

* 鉴定权限和请求权限统一

```
[DDYAuthManager ddy_ContactsAuthAlertShow:YES success:^{} fail:^(DDYContactsAuthStatus authStatus) {}];
```


### 事件(日历)权限

* 鉴定权限和请求权限统一

```
[DDYAuthManager ddy_EventAuthAlertShow:YES success:^{} fail:^(EKAuthorizationStatus authStatus) {}];
```


### 备忘录权限

* 鉴定权限和请求权限统一

```
[DDYAuthManager ddy_ReminderAuthAlertShow:YES success:^{} fail:^(EKAuthorizationStatus authStatus) {}];
```


### 通知(推送)权限


* 请求权限(注册通知)

```
if (@available(iOS 10.0, *)) {
  UNUserNotificationCenter *currentNotificationCenter = [UNUserNotificationCenter currentNotificationCenter];
  UNAuthorizationOptions options = UNAuthorizationOptionAlert | UNAuthorizationOptionSound | UNAuthorizationOptionBadge;
  [currentNotificationCenter requestAuthorizationWithOptions:options completionHandler:^(BOOL granted, NSError * _Nullable error) {
    dispatch_async(dispatch_get_main_queue(), ^{
      if (!error) [[UIApplication sharedApplication] registerForRemoteNotifications]; // 注册获得device Token
    });
  }];
} else {
    UIUserNotificationType types = UIUserNotificationTypeBadge | UIUserNotificationTypeAlert | UIUserNotificationTypeSound;
    UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes:types categories:nil];
    [[UIApplication sharedApplication] registerUserNotificationSettings:settings];
    [[UIApplication sharedApplication] registerForRemoteNotifications]; // 注册获得device Token
}
```

* 鉴定权限

```
[DDYAuthManager ddy_PushNotificationAuthAlertShow:YES success:^{} fail:^{}];
```


### 位置(定位)权限

* 请求权限

```
// CLLocationManager实例必须是全局的变量，否则授权提示弹框可能不会一直显示。
@property (nonatomic, strong) CLLocationManager *locationManager;

if ([CLLocationManager locationServicesEnabled]) {
  _locationManager = [[CLLocationManager alloc] init];
  [_locationManager requestWhenInUseAuthorization];
}
```

* 鉴定权限

```
// 先判断服务是否可用 [CLLocationManager locationServicesEnabled]
[DDYAuthManager ddy_LocationAuthType:DDYCLLocationTypeInUse alertShow:YES success:^{} fail:^(CLAuthorizationStatus authStatus) {}];
```


### 语音识别(语音转文字)权限

* 鉴定权限和请求权限统一

```
if (@available(iOS 10.0, *)) {
  [DDYAuthManager ddy_SpeechAuthAlertShow:YES success:^{} fail:^(SFSpeechRecognizerAuthorizationStatus authStatus) {}]; 
}
```


### 联网权限

* 请求权限


```
// 可以采用主动请求一次网络的形式触发
[DDYAuthManager ddy_GetNetAuthWithURL:nil];
// 如果弹窗不出现，请参照网上方案 [0](https://github.com/Zuikyo/ZIKCellularAuthorization) [1](https://www.jianshu.com/p/244c0774b1fb) [2](https://github.com/ziecho/ZYNetworkAccessibity)
```

* 鉴定权限

```
if (@available(iOS 10.0, *)) {
  [DDYAuthManager ddy_NetAuthAlertShow:YES success:^{} fail:^(CTCellularDataRestrictedState authStatus) {}];
}
```



附：
* 如果pod search DDYAuthManager搜索不到，可以尝试先执行 rm ~/Library/Caches/CocoaPods/search_index.json

* 联网权限不弹窗或者wifi下弹窗拒绝蜂窝网络问题 见https://github.com/Zuikyo/ZIKCellularAuthorization

* 本工程已经变更为Demo，请移步[DDYAuthManager](https://github.com/RainOpen/DDYAuthManager)下载源工程