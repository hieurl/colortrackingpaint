#include <cv.h>
#include <iostream>
#include <video\tracking.hpp>
#include <highgui.h>
#include <queue>

#include "cAnimation.h"
#include "CONSTANT.h"

using namespace std;

struct hsvStruct{
	int H,S,V;
};

hsvStruct trainingColor(CvCapture* capture);
CvScalar trainingColorBGR(CvCapture* capture);

int main(int, char**) {
	hsvStruct hsv;
	hsv.H = 100;
	hsv.S = 100;
	hsv.V = 100;
		
	//Capture from camera
	//CvCapture * capture = cvCaptureFromFile(str);
	CvCapture * capture = cvCaptureFromCAM(-1);
	int fps = (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );

	hsv = trainingColor(capture);
	/*hsv.H = 222;
	hsv.S = 167;
	hsv.V = 181;*/

	cvWaitKey(1000);

	hsvStruct hsvRIGHT;
	hsvRIGHT = trainingColor(capture);
	/*hsvRIGHT.H = 108;
	hsvRIGHT.S = 190;
	hsvRIGHT.V = 160;*/


	IplImage* frame;
	IplImage* bgImg;
	hsvStruct hsvCustomColor;
	
	//cvNamedWindow("img", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("ori", CV_WINDOW_AUTOSIZE);
	cvNamedWindow ("camera");
	cvNamedWindow("window", CV_WINDOW_AUTOSIZE);

	CvPoint2D32f posLEFT;
	CvPoint2D32f posRIGHT;

	CvPoint2D32f previousPos;
	previousPos.x = -1;
	previousPos.y = -1;

	IplImage * drawField = cvCreateImage(cvSize(950, 700), 8, 3);
	cvRectangle(drawField, cvPoint(0,0), cvPoint(950, 700), cvScalar(255,255,255), CV_FILLED);

	IplImage* camFrame;
	IplImage* tempFrame;
	IplImage* tempFrameEllipse;

	//FLAG
	bool isCLICK = false;
	int ACTION = 0;
	int CURSOR = CONSTANT::CURSOR_PEN;
	CvScalar COLOR = cvScalar(0,0,255);
	int COLOR_CHOICE = CONSTANT::COLOR_RED;

	CvPoint pRect1, pRect2;
	pRect1.x = -1;
	pRect1.y = -1;
	pRect2.x = -1;
	pRect2.y = -1;

	CvPoint pEllipse1, pEllipse2;
	pEllipse1.x = -1;
	pEllipse1.y = -1;
	pEllipse2.x = -1;
	pEllipse2.y = -1;
	while(true) {
		CvFont font;
		frame = cvQueryFrame(capture);
		if (!frame)
			break;

		cvFlip(frame, frame, 1);

		bgImg = cvCreateImage(cvSize(950, 700), frame->depth, frame->nChannels);
		cvCopyImage(drawField, bgImg);

		cAnimation::drawMenu(bgImg, CURSOR);
		cAnimation::drawColorTable(bgImg, COLOR_CHOICE);
		cvShowImage("window",bgImg);
	
		//SHOW CAMERA
		camFrame = cvCreateImage(cvSize(frame->width/2, frame->height/2), frame->depth, frame->nChannels);
		cvResize(frame, camFrame);
		cvShowImage("camera", camFrame);
		cvReleaseImage(&camFrame);
		//TASK: TRACKING FIRST OBJECT!
		//convert img to hsv
		posLEFT = cAnimation::trackColor(cvScalar(hsv.H, hsv.S, hsv.V), frame);

		//TASK TRACKING SECOND OBJECT!
		isCLICK = false;
		posRIGHT = cAnimation::trackColor(cvScalar(hsvRIGHT.H, hsvRIGHT.S, hsv.V), frame);
		if (posRIGHT.x > 0 && posRIGHT.y > 0) {
			isCLICK = true;
		} 

		posLEFT.x = (posLEFT.x/frame->width)*bgImg->width;
		posLEFT.y = (posLEFT.y/frame->height)*bgImg->height;
		if (posLEFT.x > 0 || posLEFT.y >0)
			cvRectangle(bgImg, cvPoint(posLEFT.x-20, posLEFT.y+20), cvPoint(posLEFT.x+20, posLEFT.y-20), cvScalar(1, 1, 1) ,2);

		//TASK: DETECT ACTION
		if (posLEFT.x >= 0 && posLEFT.y >= 0 && isCLICK) {
			if (previousPos.x > 0 && previousPos.y > 0) {
				if (posLEFT.y < 150 && posLEFT.x > 200 && posLEFT.x < 350) {
					//ACTION = CONSTANT::ACTION_CHOOSE_PEN;
					CURSOR = CONSTANT::CURSOR_PEN;
				}
				else if (posLEFT.y < 150 && posLEFT.x > 350 && posLEFT.x < 500) {
					//ACTION = CONSTANT::ACTION_CHOOSE_BRUSH;
					CURSOR = CONSTANT::CURSOR_BRUSH;
				}
				else if (posLEFT.y < 150 && posLEFT.x > 500 && posLEFT.x < 650) {
					//ACTION = CONSTANT::ACTION_CHOOSE_RECT;
					CURSOR = CONSTANT::CURSOR_RECT;
				}
				else if (posLEFT.y < 150 && posLEFT.x > 650 && posLEFT.x < 800) {
					//ACTION = CONSTANT::ACTION_CHOOSE_CIR;
					CURSOR = CONSTANT::CURSOR_CIR;
				}
				else if (posLEFT.y < 150 && posLEFT.x > 800 && posLEFT.x < 950) {
					cvReleaseImage(&drawField);
					drawField = cvCreateImage(cvSize(950, 700), 8, 3);
					cvRectangle(drawField, cvPoint(0,0), cvPoint(950, 700), cvScalar(255,255,255), CV_FILLED);					
				}
				else if (posLEFT.y > 150 && posLEFT.y < 220 && posLEFT.x < 200) {
					//ACTION = CONSTANT::ACTION_CHOOSE_COLOR_RED;
					COLOR_CHOICE = CONSTANT::COLOR_RED;
					COLOR.val[0] = 0;
					COLOR.val[1] = 0;
					COLOR.val[2] = 255;
				}
				else if (posLEFT.y > 220 && posLEFT.y < 290 && posLEFT.x < 200) {
					//ACTION = CONSTANT::ACTION_CHOOSE_COLOR_YELLOW;
					COLOR.val[0] = 0;
					COLOR.val[1] = 242;
					COLOR.val[2] = 255;
					COLOR_CHOICE = CONSTANT::COLOR_YELLOW;
				}
				else if (posLEFT.y > 290 && posLEFT.y < 360 && posLEFT.x < 200) {
					//ACTION = CONSTANT::ACTION_CHOOSE_COLOR_BLUE;
					COLOR_CHOICE = CONSTANT::COLOR_BLUE;
					COLOR.val[0] = 255;
					COLOR.val[1] = 128;
					COLOR.val[2] = 0;
				}
				else if (posLEFT.y > 360 && posLEFT.y < 430 && posLEFT.x < 200) {
					//ACTION = CONSTANT::ACTION_CHOOSE_COLOR_GREEN;
					COLOR_CHOICE = CONSTANT::COLOR_GREEN;
					COLOR.val[0] = 64;
					COLOR.val[1] = 255;
					COLOR.val[2] = 0;
				}
				else if (posLEFT.y > 430 && posLEFT.y < 500 && posLEFT.x < 200) {
					//ACTION = CONSTANT::ACTION_CHOOSE_COLOR_PURPLE;
					COLOR_CHOICE = CONSTANT::COLOR_PURPLE;
					COLOR.val[0] = 187;
					COLOR.val[1] = 0;
					COLOR.val[2] = 187;
				}
				else if (posLEFT.y > 500 && posLEFT.y < 570 && posLEFT.x < 200) {
					ACTION = CONSTANT::ACTION_CHOOSE_COLOR_CUSTOM;
					COLOR_CHOICE = CONSTANT::COLOR_CUSTOM;
				}
				else if (posLEFT.y > 150 && posLEFT.y < 700 && posLEFT.x < 950 && posLEFT.x > 200) {
					ACTION = CONSTANT::ACTION_DRAW;
				}
			}
		} else if (posLEFT.x >= 0 && posLEFT.y >= 0 && !(isCLICK) && CURSOR == CONSTANT::CURSOR_RECT){
			ACTION = CONSTANT::ACTION_DRAW;
		}

		//DRAW
		int width = 1;
		if (ACTION == CONSTANT::ACTION_DRAW) {
			if (CURSOR == CONSTANT::CURSOR_BRUSH || (CURSOR == CONSTANT::CURSOR_PEN)) { 
				if (CURSOR == CONSTANT::CURSOR_BRUSH)
					width = 10;
				else if (CURSOR == CONSTANT::CURSOR_PEN) {
					width = 2;
				}
				if (previousPos.x > 0 && previousPos.y > 0)
					cvLine(drawField, cvPoint(previousPos.x, previousPos.y), cvPoint(posLEFT.x, posLEFT.y), COLOR, width);
				ACTION = 0;
			} else if (CURSOR == CONSTANT::CURSOR_RECT) {
				if ((pRect1.x < 0 && pRect1.y < 0) && isCLICK && posLEFT.x > 200 && posLEFT.y > 150 && posLEFT.x < 950 && posLEFT.y < 700) {
					pRect1.x = posLEFT.x;
					pRect1.y = posLEFT.y;
				} else if (isCLICK && pRect1.x > 0 && pRect1.y > 0) {
					if (pRect2.x > 0 || pRect2.y > 0) {
						cvReleaseImage(&tempFrame);
					}
					tempFrame = cvCreateImage(cvSize(abs(pRect1.x - posLEFT.x), abs(pRect1.y -posLEFT.y)), frame->depth, frame->nChannels);
					cvRectangle(tempFrame, cvPoint(0,0), cvPoint(abs(pRect1.x - posLEFT.x), abs(pRect1.y -posLEFT.y)), cvScalar(255,255,255), CV_FILLED);
					pRect2.x = posLEFT.x;
					pRect2.y = posLEFT.y;
					cvRectangle(tempFrame, cvPoint(0,0), cvPoint(abs(pRect1.x - posLEFT.x), abs(pRect1.y -posLEFT.y)), COLOR, 7); 
					cAnimation::overlayImage(bgImg, tempFrame, pRect1, cvScalar(0,0,0), cvScalar(1,1,1));
				} else if ((pRect2.x > 0 && pRect2.y && pRect1.x > 0 && pRect1.y) > 0 && !(isCLICK)) {
						cAnimation::overlayImage(drawField, tempFrame, pRect1, cvScalar(0,0,0), cvScalar(1,1,1));
						cvReleaseImage(&tempFrame);
						pRect1.x = -1;
						pRect1.y = -1;
						pRect2 = pRect1;
				}
			} else if (CURSOR == CONSTANT::CURSOR_CIR) {
				if (pEllipse1.x < 0 && pEllipse1.y < 0 && isCLICK && posLEFT.x > 200 && posLEFT.y > 150 && posLEFT.x < 950 && posLEFT.y < 700) {
					pEllipse1.x = posLEFT.x;
					pEllipse1.y = posLEFT.y;
				} else if (isCLICK && pEllipse1.x > 0 && pEllipse1.y > 0) {
					if (pEllipse2.x > 0 || pEllipse2.y > 0) {
						cvReleaseImage(&tempFrameEllipse);
					}
					tempFrameEllipse = cvCreateImage(cvSize(abs(pEllipse1.x - posLEFT.x), abs(pEllipse1.y -posLEFT.y)), frame->depth, frame->nChannels);
					CvPoint center;
					center.x = abs(pEllipse1.x - posLEFT.x)/2;
					center.y = abs(pEllipse1.y - posLEFT.y)/2;
					cvRectangle(tempFrameEllipse, cvPoint(0,0), cvPoint(abs(pEllipse1.x - posLEFT.x), abs(pEllipse1.y -posLEFT.y)), cvScalar(255,255,255), CV_FILLED);
					pEllipse2.x = posLEFT.x;
					pEllipse2.y = posLEFT.y;
					cvEllipse(tempFrameEllipse, center, cvSize(abs(pEllipse1.x - posLEFT.x)/2, abs(pEllipse1.y -posLEFT.y)/2), 0, 0, 360, COLOR, 4, 8, 0);
					//cvRectangle(tempFrameEllipse, cvPoint(0,0), cvPoint(abs(pEllipse1.x - posLEFT.x), abs(pEllipse1.y -posLEFT.y)), COLOR, 7); 
					cAnimation::overlayImage(bgImg, tempFrameEllipse, pEllipse1, cvScalar(0,0,0), cvScalar(1,1,1));
				} else if ((pEllipse1.x > 0 || pEllipse1.y > 0 || pEllipse2.x > 0 || pEllipse2.y > 0) && !(isCLICK)) {
					cAnimation::overlayImage(drawField, tempFrameEllipse, pEllipse1, cvScalar(0,0,0), cvScalar(1,1,1));
					cvReleaseImage(&tempFrameEllipse);
					pEllipse1.x = -1;
					pEllipse1.y = -1;
					pEllipse2 = pEllipse1;
				}
			}
		} else if (ACTION == CONSTANT::ACTION_CHOOSE_COLOR_CUSTOM) {
			COLOR = trainingColorBGR(capture);	
			ACTION = 0;
		}
		
		if (isCLICK)	
			previousPos = posLEFT;
		else {
			previousPos.x = -1;
			previousPos.y = -1;
		}

		cvShowImage("window",bgImg);

		cvWaitKey(1000/40);
		cvReleaseImage(&bgImg);		
		//cvReleaseImage(&frame);
	}
	

	return 0;
}

hsvStruct trainingColor(CvCapture* capture) {
	hsvStruct color;
	color.H = 0;
	color.S = 0;
	color.V = 0;

	cvNamedWindow("A");

	IplImage*frame;
	queue<IplImage*> fl;

	CvScalar meanScalar;
	CvScalar standardDev;

	bool finish;

	while(true) {
		finish = true;
		frame = cvQueryFrame(capture);
		cvFlip(frame, frame,1);
		cvCvtColor(frame, frame, CV_BGR2HSV_FULL);

		cvSetImageROI(frame, cvRect(frame->width/4, frame->height/4, frame->width/2, frame->height/2));
		fl.push(frame);
		if(fl.size() >60) {
			fl.pop();
			//break;
		}

		if(fl.size() >=60) {
			color.H = 0;
			color.S = 0;
			color.V = 0;
			for(int i = 0; i < fl.size(); i++) {
				cvAvgSdv(frame, &meanScalar, &standardDev);
				if (standardDev.val[0] > 15 ||	standardDev.val[1] > 15){
					finish = false;
					break;
				}
				else {
					if(i == 0) {
						color.H = meanScalar.val[0];
						color.S = meanScalar.val[1];
						color.V = meanScalar.val[2];
					}
					else {
						color.H = (color.H + meanScalar.val[0])/2;
						color.S = (color.S + meanScalar.val[1])/2;
						color.V = (color.V + meanScalar.val[2])/2;
					}
				}
			}
		}
		else {
			finish = false;
		}
		
		cvWaitKey(1000/30);
		cvResetImageROI(frame);
		cvCvtColor(frame, frame, CV_HSV2BGR_FULL);
		cvRectangle(frame, cvPoint(frame->width/4, frame->height/4), cvPoint(frame->width*3/4, frame->height*3/4), cvScalar(0,0,0));
		cvShowImage("A", frame);

		if (finish) {
			cvDestroyWindow("A");
			break;
		}
	}

	return color;
}

CvScalar trainingColorBGR(CvCapture* capture) {
	CvScalar color;
	color.val[0] = 0;
	color.val[1] = 0;
	color.val[2] = 0;

	cvNamedWindow("A");

	IplImage*frame;
	queue<IplImage*> fl;

	CvScalar meanScalar;
	CvScalar standardDev;

	bool finish;

	while(true) {
		finish = true;
		frame = cvQueryFrame(capture);	

		cvSetImageROI(frame, cvRect(frame->width/4, frame->height/4, frame->width/2, frame->height/2));
		fl.push(frame);
		if(fl.size() >60) {
			fl.pop();
			//break;
		}

		if(fl.size() >=60) {
			color.val[0] = 0;
			color.val[1] = 0;
			color.val[2] = 0;
			for(int i = 0; i < fl.size(); i++) {
				cvAvgSdv(frame, &meanScalar, &standardDev);
				if (standardDev.val[0] > 15 ||	standardDev.val[1] > 15){
					finish = false;
					break;
				}
				else {
					if(i == 0) {
						color.val[0] = meanScalar.val[0];
						color.val[1] = meanScalar.val[1];
						color.val[2] = meanScalar.val[2];
					}
					else {
						color.val[0] = (color.val[0] + meanScalar.val[0])/2;
						color.val[1] = (color.val[1] + meanScalar.val[1])/2;
						color.val[2] = (color.val[2] + meanScalar.val[2])/2;
					}
				}
			}
		}
		else {
			finish = false;
		}
		
		cvWaitKey(1000/40);
		cvResetImageROI(frame);
		cvFlip(frame, frame, 1);
		cvRectangle(frame, cvPoint(frame->width/4, frame->height/4), cvPoint(frame->width*3/4, frame->height*3/4), cvScalar(0,0,0));
		cvShowImage("A", frame);

		//cvReleaseImage(&frame);

		if (finish) {
			cvDestroyWindow("A");
			break;
		}
	}

	return color;
}