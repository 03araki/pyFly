#include "bfly.h"

bool initCamera(int iMode){
		Error error;
		unsigned int numCams;

		if(camStatus) return true;

		camStatus = false;
		error = busMgr.GetNumOfCameras(&numCams);
		if(error != PGRERROR_OK) return false;

		if(numCams == 0) return false;

		PGRGuid guid;
		busMgr.GetCameraFromIndex(0, &guid);
		error = cam.Connect(&guid);
		if(error != PGRERROR_OK) return false;

		// 画像読み込みモードの設定
		Format7Info fmt7Info;
		bool supported;
		switch(iMode){
				case 0:
						fmt7Info.mode = MODE_0;
						break;
				case 1:
						fmt7Info.mode = MODE_1;
						break;
				default:
						fmt7Info.mode = MODE_0;
						break;
		}
		error = cam.GetFormat7Info(&fmt7Info, &supported);
		if(error != PGRERROR_OK) return false;
		if(!supported) return false;
		
		Format7ImageSettings fmt7ImageSettings;
		fmt7ImageSettings.mode = fmt7Info.mode;
		fmt7ImageSettings.offsetX = 0;
		fmt7ImageSettings.offsetY = 0;
		fmt7ImageSettings.width = fmt7Info.maxWidth;
		fmt7ImageSettings.height = fmt7Info.maxHeight;
		fmt7ImageSettings.pixelFormat = PIXEL_FORMAT_RAW8;

		bool valid;
		Format7PacketInfo fmt7PacketInfo;
		error = cam.ValidateFormat7Settings(
						&fmt7ImageSettings, &valid, &fmt7PacketInfo);
		if(error != PGRERROR_OK) return false;
		if(!valid) return false;
		error = cam.SetFormat7Configuration(
						&fmt7ImageSettings, 
						fmt7PacketInfo.recommendedBytesPerPacket);
		if(error != PGRERROR_OK) return false;


		error = cam.StartCapture();
		if(error != PGRERROR_OK) return false;

		// 画像の読み込みテスト
		cam.RetrieveBuffer(&rawImage);
		rawImage.Convert(PIXEL_FORMAT_BGR, &convertedImage);
		imageData = convertedImage.GetData();
		imageWidth = convertedImage.GetCols();
		imageHeight = convertedImage.GetRows();

		camStatus = true;
		return true;
}


bool closeCamera(){
		if(!camStatus) return false;

		cam.StopCapture();
		cam.Disconnect();
		camStatus = false;

		return true;
}


bool isCameraOpen(){
		return camStatus;
}


int getWidth(){
		return imageWidth;
}


int getHeight(){
		return imageHeight;
}


unsigned char* getImage(){
		cam.RetrieveBuffer(&rawImage);
		rawImage.Convert(PIXEL_FORMAT_BGR, &convertedImage);
		imageData = convertedImage.GetData();

		return imageData;
}

