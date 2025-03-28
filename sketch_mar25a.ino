#include <Servo.h>

// 定義接腳
const int switchPin = 2;  // 微動開關連接到 2 號腳位
const int servoPin = 9;   // 伺服馬達信號線連接到 9 號腳位

// 定義伺服馬達的搖擺角度範圍
const int minAngle = 0;   // 最小角度
const int maxAngle = 180; // 最大角度

Servo myServo;  // 創建伺服馬達對象

// 變量來追蹤伺服馬達的狀態
bool isSwinging = false;  // 是否正在搖擺
int currentAngle = minAngle; // 當前角度
int direction = 1; // 1 表示正向，-1 表示反向

// 變量來追蹤開關的狀態
int lastSwitchState = HIGH; // 上一次的開關狀態

void setup() {
  // 初始化伺服馬達
  myServo.attach(servoPin);
  
  // 初始化微動開關的接腳
  pinMode(switchPin, INPUT_PULLUP); // 使用內部上拉電阻
  
  // 將伺服馬達設置到初始位置（0 度）
  myServo.write(minAngle);
}

void loop() {
  // 讀取微動開關的當前狀態
  int switchState = digitalRead(switchPin);
  
  // 檢測開關是否被按下（從 HIGH 變為 LOW）
  if (switchState == LOW && lastSwitchState == HIGH) {
    // 切換伺服馬達的搖擺狀態
    isSwinging = !isSwinging;
    delay(1); // 延遲 50 毫秒以避免開關抖動
  }
  
  // 更新上一次的開關狀態
  lastSwitchState = switchState;
  
  // 如果伺服馬達應該搖擺
  if (isSwinging) {
    // 更新角度
    currentAngle += direction;
    if (currentAngle >= maxAngle) {
      direction = -1; // 達到最大角度，改變方向
    } else if (currentAngle <= minAngle) {
      direction = 1; // 達到最小角度，改變方向
    }
    myServo.write(currentAngle); // 移動伺服馬達
    delay(1); // 控制搖動速度
  } else {
    // 如果不搖擺，保持在最小角度
    myServo.write(minAngle);
    currentAngle = minAngle; // 重置當前角度
    direction = 1; // 重置方向為正向
  }
}