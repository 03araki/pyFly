#ifndef _BFLY_H_
#define _BFLY_H_
#include "FlyCapture2.h"

using namespace FlyCapture2;

static BusManager busMgr;
static Camera cam;
static Image rawImage, convertedImage;
static int imageWidth;
static int imageHeight;
static int videoMode;
static unsigned char* imageData;
static bool camStatus=false;

bool initCamera(int iMode);
bool closeCamera();
bool isCameraOpen();
int getWidth();
int getHeight();
unsigned char* getImage();
#endif
