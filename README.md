# pyFly

pyFly は Blackfly などの FLIR (PointGrey) 製カメラを対象とした Flycapture2 SDK の Python 用ラッパーです．
公式 (pyCapture2) ではサポートされていない ARM 環境でも動作するため，NVIDIA の Jetson TX2/Nano などでも python からカメラの画像を取得することが可能となります．
(元々，Jetson TX2 で Blackfly BFLY-U3-13S2C-CS を python から利用するために作成したものです．）

## Requirements

- Ubuntu 16.04/18.04 amd64, arm64
- opencv-python
- flycapture2 (obtained from FLIR Web site)

## Installation

pyFly を使用するために，はじめに Flycapture2 SDK をインストールして下さい．
(インストール終了後，reboot すること．)
なお，現時点で flycapture2-2.13.3.31 で動作確認をしております．

- Ubuntu 18.04 amd64 の場合
```
tar xvzf flycapture2-2.13.3.31-amd64-pkg_Ubuntu18.04.tgz
cd flycapture2-2.13.3.31-amd64/
sudo apt install libraw1394-11 libavcodec57 libavformat57 libswscale4 libswresample2 libavutil55 libgtkmm-2.4-1v5 libglademm-2.4-1v5 libgtkglextmm-x11-1.2-0v5 libgtkmm-2.4-dev libglademm-2.4-dev libgtkglextmm-x11-1.2-dev libusb-1.0-0
sudo sh install_flycapture.sh
```

- Ubuntu 18.04 arm64 (for example Jetson Nano v43) の場合 (公式にはサポートされていないようですが，ubuntu16.04-arm64 で動作することを確認しています）
```
tar xvzv flycapture2-2.13.3.31_arm64_Ubuntu16.04.tar.gz
cd flycapture2-2.13.3.31_arm64/
sudo cp lib/libflycapture* /usr/lib
sudo mkdir /usr/include/flycapture
sudo cp -r include/* /usr/include/flycapture
sudo sh flycap2-conf
```

Flycapture2 SDK がインストールされた状態で，以下を実行することで pyFly が使用可能になります．

```
git clone https://github.com/03araki/pyFly.git
cd pyFly/
make clean
make
```
この操作で pyFly.so が生成されていればインストールは完了です．
この状態でカメラ (BFLY-U3-13S2C-CS のみ動作確認しております) を接続し，pyFlyTest.py を以下のように実行すると画像取得テストが行われます．('q' で終了)
```
python3 pyFlyTest.py
```


## Usage

pyFly/ 内の pyFly.so を import することで python からカメラ画像の取得が可能となります．
使用の際には pyFly.so を python のソースファイルと同じディレクトリ内にコピーして下さい．

例 (pyFlyTest.py)
```
import pyFly
import cv2
import numpy as np

if not pyFly.initCamera(0): # 初期化処理  引数: 0-全画素取得, 1-1/2サイズ
    print('camera is not detected')
    exit()

while(True):
    img = pyFly.getImage() # 画像データの取得 (cv2 の画像データ形式に変換済み)
    cv2.show('image', img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

pyFly.closeCamera() # 終了処理
```
