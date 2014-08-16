#pragma once

#include <cv.h>
#include <iostream>
#include <video\tracking.hpp>
#include <highgui.h>
#include <queue>
#include <vector>

#include "CONSTANT.h"

using namespace std;
class cAnimation
{
public:
	cAnimation(void);
	~cAnimation(void);
	static vector<IplImage*> showMenu(CvSize);
	static IplImage* drawMenu(IplImage*, int CHOSEN_MENU);

	static vector<IplImage*> showColorTable(CvSize);
	static IplImage* drawColorTable(IplImage*, int CHOSEN_COLOR);

	static void display(IplImage* dest, vector<IplImage*> src, int rate);
	static void overlayImage(IplImage* src, IplImage* overlay, CvPoint location, CvScalar S, CvScalar D);

	static CvPoint2D32f trackColor(CvScalar color, IplImage* img);

	static void handleChooseAction(int ACTION, IplImage*);
};

