#include <M5Atom.h>
#include <Adafruit_NeoPixel.h>

#define PWM_PIN 25           // PWM信号を出力するピンの番号
#define PWM_CHANNEL 0        // PWMチャンネルの番号
#define PWM_RESOLUTION 8     // PWMの解像度（ビット数）
#define PWM_FREQUENCY 20000  // PWMの周波数（Hz）

#define NP_PIN 33     // NeoPixel信号端子
#define NUMPIXELS 12  // NeoPixelの数

// NeoPixel初期設定
Adafruit_NeoPixel pixels(NUMPIXELS, NP_PIN, NEO_GRB + NEO_KHZ800);
int change = 0;  //色指定用
int r = 0;       //LED色指定値格納用（赤）
int g = 0;       //LED色指定値格納用（緑）
int b = 0;       //LED色指定値格納用（青）
int cnt = 29;    //LED流れる光（2個）カウント用
// LEDベース色を指定。2次元配列（4色分のr,g,bの値を設定）
int rgb[4][3] = { { 5, 5, 5 }, { 10, 0, 1 }, { 0, 10, 1 }, { 2, 0, 10 } };


void setup() {
  M5.begin(true, false, false);
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(PWM_PIN, PWM_CHANNEL);

  pixels.begin();  //NeoPixel初期化
  pixels.clear();  //LED色指定クリア

  //初期点灯色指定
  r = rgb[change][0];                                //LEDベース色白用r（赤）の値格納。rgb[0][0]
  g = rgb[change][1];                                //LEDベース色白用g（緑）の値格納。rgb[0][1]
  b = rgb[change][2];                                //LEDベース色白用b（青）の値格納。rgb[0][2]
  for (int i = NUMPIXELS; i >= 0; i--) {             //LED番号59～0まで繰り返し
    pixels.setPixelColor(i, pixels.Color(r, g, b));  //全LED色指定（白）
    pixels.show();                                   //LED色出力
    delay(5);                                        //5ms間隔で色を変更していく
  }
}

void loop() {
  ledcWrite(PWM_CHANNEL, 0);
  delay(1500);

  change++;           //色指定用change+1
  if (change == 4) {  //changeが4なら
    change = 0;       //changeを0リセット
  }

  r = rgb[change][0];  //LEDのベース色の値(changeによる)をr,g,bへそれぞれ格納
  g = rgb[change][1];
  b = rgb[change][2];
  for (int i = NUMPIXELS - 1; i >= 0; i--) {  //LED番号59～0まで繰り返し
    //全LED色指定
    pixels.setPixelColor(i, pixels.Color(r, g, b));  //LED色指定
    pixels.show();                                   //LED色出力
    delay(5);                                        //5ms間隔で色を変更していく
  }

//  1段階目
  for (int dutyCycle = 20; dutyCycle <= 80; dutyCycle++) {
    if (dutyCycle < 60) {
      ledcWrite(PWM_CHANNEL, 155);
      delay(10);
    }
    ledcWrite(PWM_CHANNEL, dutyCycle);
    Serial.println(dutyCycle);

    // 流れる白い光x2（残光3、LED白とベース色を混ぜてだんだん暗く）
    pixels.setPixelColor(cnt - 3, pixels.Color(30, 30, 30));                                //LED白後半
    pixels.setPixelColor(cnt - 2, pixels.Color((20 + r) / 2, (20 + g) / 2, (20 + b) / 2));  //残光1
    pixels.setPixelColor(cnt - 1, pixels.Color((10 + r) / 2, (10 + g) / 2, (10 + b) / 2));  //残光2
    pixels.setPixelColor(cnt, pixels.Color((5 + r) / 2, (5 + g) / 2, (5 + b) / 2));         //残光3
    pixels.setPixelColor(cnt + 1, pixels.Color(r, g, b));                                   //LEDベース色

    pixels.setPixelColor(cnt + 27, pixels.Color(30, 30, 30));                                //LED白前半
    pixels.setPixelColor(cnt + 28, pixels.Color((20 + r) / 2, (20 + g) / 2, (20 + b) / 2));  //残光1
    pixels.setPixelColor(cnt + 29, pixels.Color((10 + r) / 2, (10 + g) / 2, (10 + b) / 2));  //残光2
    pixels.setPixelColor(cnt + 30, pixels.Color((5 + r) / 2, (5 + g) / 2, (5 + b) / 2));     //残光3
    pixels.setPixelColor(cnt + 31, pixels.Color(r, g, b));                                   //LEDベース色
    pixels.show();

    if (cnt == 0) {                                    //カウントが0なら
      pixels.setPixelColor(0, pixels.Color(r, g, b));  //LED0番をベース色に
      cnt = 30;                                        //カウントリセット
    }
    cnt--;  //カウント-1

    delay(200);
  }


  change++;           //色指定用change+1
  if (change == 4) {  //changeが4なら
    change = 0;       //changeを0リセット
  }

  r = rgb[change][0];  //LEDのベース色の値(changeによる)をr,g,bへそれぞれ格納
  g = rgb[change][1];
  b = rgb[change][2];
  for (int i = NUMPIXELS - 1; i >= 0; i--) {  //LED番号59～0まで繰り返し
    //全LED色指定
    pixels.setPixelColor(i, pixels.Color(r, g, b));  //LED色指定
    pixels.show();                                   //LED色出力
    delay(5);                                        //5ms間隔で色を変更していく
  }


//  2段階目
  for (int dutyCycle = 80; dutyCycle <= 110; dutyCycle++) {
    if (dutyCycle < 60) {
      ledcWrite(PWM_CHANNEL, 155);
      delay(10);
    }
    ledcWrite(PWM_CHANNEL, dutyCycle);
    Serial.println(dutyCycle);

    // 流れる白い光x2（残光3、LED白とベース色を混ぜてだんだん暗く）
    pixels.setPixelColor(cnt - 3, pixels.Color(30, 30, 30));                                //LED白後半
    pixels.setPixelColor(cnt - 2, pixels.Color((20 + r) / 2, (20 + g) / 2, (20 + b) / 2));  //残光1
    pixels.setPixelColor(cnt - 1, pixels.Color((10 + r) / 2, (10 + g) / 2, (10 + b) / 2));  //残光2
    pixels.setPixelColor(cnt, pixels.Color((5 + r) / 2, (5 + g) / 2, (5 + b) / 2));         //残光3
    pixels.setPixelColor(cnt + 1, pixels.Color(r, g, b));                                   //LEDベース色

    pixels.setPixelColor(cnt + 27, pixels.Color(30, 30, 30));                                //LED白前半
    pixels.setPixelColor(cnt + 28, pixels.Color((20 + r) / 2, (20 + g) / 2, (20 + b) / 2));  //残光1
    pixels.setPixelColor(cnt + 29, pixels.Color((10 + r) / 2, (10 + g) / 2, (10 + b) / 2));  //残光2
    pixels.setPixelColor(cnt + 30, pixels.Color((5 + r) / 2, (5 + g) / 2, (5 + b) / 2));     //残光3
    pixels.setPixelColor(cnt + 31, pixels.Color(r, g, b));                                   //LEDベース色
    pixels.show();

    if (cnt == 0) {                                    //カウントが0なら
      pixels.setPixelColor(0, pixels.Color(r, g, b));  //LED0番をベース色に
      cnt = 30;                                        //カウントリセット
    }
    cnt--;  //カウント-1

    delay(400);
  }


  change++;           //色指定用change+1
  if (change == 4) {  //changeが4なら
    change = 0;       //changeを0リセット
  }

  r = rgb[change][0];  //LEDのベース色の値(changeによる)をr,g,bへそれぞれ格納
  g = rgb[change][1];
  b = rgb[change][2];
  for (int i = NUMPIXELS - 1; i >= 0; i--) {  //LED番号59～0まで繰り返し
    //全LED色指定
    pixels.setPixelColor(i, pixels.Color(r, g, b));  //LED色指定
    pixels.show();                                   //LED色出力
    delay(5);                                        //5ms間隔で色を変更していく
  }

//  3段階目
  for (int dutyCycle = 110; dutyCycle >= 80; dutyCycle--) {
    ledcWrite(PWM_CHANNEL, dutyCycle);
    Serial.println(dutyCycle);

    // 流れる白い光x2（残光3、LED白とベース色を混ぜてだんだん暗く）
    pixels.setPixelColor(cnt - 3, pixels.Color(30, 30, 30));                                //LED白後半
    pixels.setPixelColor(cnt - 2, pixels.Color((20 + r) / 2, (20 + g) / 2, (20 + b) / 2));  //残光1
    pixels.setPixelColor(cnt - 1, pixels.Color((10 + r) / 2, (10 + g) / 2, (10 + b) / 2));  //残光2
    pixels.setPixelColor(cnt, pixels.Color((5 + r) / 2, (5 + g) / 2, (5 + b) / 2));         //残光3
    pixels.setPixelColor(cnt + 1, pixels.Color(r, g, b));                                   //LEDベース色

    pixels.setPixelColor(cnt + 27, pixels.Color(30, 30, 30));                                //LED白前半
    pixels.setPixelColor(cnt + 28, pixels.Color((20 + r) / 2, (20 + g) / 2, (20 + b) / 2));  //残光1
    pixels.setPixelColor(cnt + 29, pixels.Color((10 + r) / 2, (10 + g) / 2, (10 + b) / 2));  //残光2
    pixels.setPixelColor(cnt + 30, pixels.Color((5 + r) / 2, (5 + g) / 2, (5 + b) / 2));     //残光3
    pixels.setPixelColor(cnt + 31, pixels.Color(r, g, b));                                   //LEDベース色
    pixels.show();

    if (cnt == 0) {                                    //カウントが0なら
      pixels.setPixelColor(0, pixels.Color(r, g, b));  //LED0番をベース色に
      cnt = 30;                                        //カウントリセット
    }
    cnt--;  //カウント-1

    delay(400);
  }


//  4段階目
  for (int dutyCycle = 80; dutyCycle >= 20; dutyCycle--) {
    ledcWrite(PWM_CHANNEL, dutyCycle);
    Serial.println(dutyCycle);

    // 流れる白い光x2（残光3、LED白とベース色を混ぜてだんだん暗く）
    pixels.setPixelColor(cnt - 3, pixels.Color(30, 30, 30));                                //LED白後半
    pixels.setPixelColor(cnt - 2, pixels.Color((20 + r) / 2, (20 + g) / 2, (20 + b) / 2));  //残光1
    pixels.setPixelColor(cnt - 1, pixels.Color((10 + r) / 2, (10 + g) / 2, (10 + b) / 2));  //残光2
    pixels.setPixelColor(cnt, pixels.Color((5 + r) / 2, (5 + g) / 2, (5 + b) / 2));         //残光3
    pixels.setPixelColor(cnt + 1, pixels.Color(r, g, b));                                   //LEDベース色

    pixels.setPixelColor(cnt + 27, pixels.Color(30, 30, 30));                                //LED白前半
    pixels.setPixelColor(cnt + 28, pixels.Color((20 + r) / 2, (20 + g) / 2, (20 + b) / 2));  //残光1
    pixels.setPixelColor(cnt + 29, pixels.Color((10 + r) / 2, (10 + g) / 2, (10 + b) / 2));  //残光2
    pixels.setPixelColor(cnt + 30, pixels.Color((5 + r) / 2, (5 + g) / 2, (5 + b) / 2));     //残光3
    pixels.setPixelColor(cnt + 31, pixels.Color(r, g, b));                                   //LEDベース色
    pixels.show();

    if (cnt == 0) {                                    //カウントが0なら
      pixels.setPixelColor(0, pixels.Color(r, g, b));  //LED0番をベース色に
      cnt = 30;                                        //カウントリセット
    }
    cnt--;  //カウント-1

    delay(200);
  }
}
