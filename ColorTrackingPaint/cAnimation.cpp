#include "cAnimation.h"


cAnimation::cAnimation(void)
{
}


cAnimation::~cAnimation(void)
{
}

void cAnimation::overlayImage(IplImage* src, IplImage* overlay, CvPoint location, CvScalar S, CvScalar D) {
	for(int x=0;x < overlay->width;x++)
    {
        if(x+location.x>=src->width) continue;
        for(int y=0;y < overlay->height;y++)
        {
            if(y+location.y>=src->height) continue;
			CvScalar source = cvGet2D(src, y+location.y, x+location.x);
            CvScalar over = cvGet2D(overlay, y, x);
			
			CvScalar merged;
			if (over.val[0] == 255 && over.val[1] == 255 && over.val[2] == 255) {
				for(int i=0;i<4;i++)
					merged.val[i] = source.val[i];
			}
			else {
				for(int i=0;i<4;i++)
					merged.val[i] = (S.val[i]*source.val[i]+D.val[i]*over.val[i]);
			}
			cvSet2D(src, y+location.y, x+location.x, merged);
        }
    }
}

vector<IplImage*> cAnimation::showColorTable(CvSize size) {
	vector<IplImage*> ani;
	IplImage * frame;
	for (int i = 0; i < 30; i++) {
		frame = cvCreateImage(size, IPL_DEPTH_32F, 3);
		cvRectangle(frame, cvPoint(0,0), cvPoint(size.width, size.height), cvScalar(255,255,255), CV_FILLED);
		cvRectangle(frame, cvPoint(0,0), cvPoint(size.width, i*(size.height/29)), cvScalar(0,0,0), 2);
		ani.push_back(frame);
	}

	return ani;
}

IplImage* cAnimation::drawMenu(IplImage* src, int CHOSEN_MENU) {
	IplImage * frame;
	frame = cvCreateImage(cvSize(750, 150), IPL_DEPTH_32F, 3);
	cvRectangle(frame, cvPoint(0,0), cvPoint(750, 150), cvScalar(255,255,255), CV_FILLED);

	IplImage * menu = cvLoadImage("image/pen.jpg",1);
	overlayImage(frame, menu,  cvPoint(0,0), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);
	
	menu = cvLoadImage("image/brush.jpg", 1);
	overlayImage(frame, menu,  cvPoint(150,0), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);

	menu = cvLoadImage("image/rect.jpg", 1);
	overlayImage(frame, menu,  cvPoint(300,0), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);

	menu = cvLoadImage("image/circle.jpg", 1);
	overlayImage(frame, menu,  cvPoint(450,0), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);

	menu = cvLoadImage("image/eraser.jpg", 1);
	overlayImage(frame, menu,  cvPoint(600,0), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);

	CvPoint p1,p2;
	switch (CHOSEN_MENU) {
	case CONSTANT::CURSOR_PEN:
		p1.x = 0;
		p1.y = 0;
		p2.x = 150;
		p2.y = 150;
		break;
	case CONSTANT::CURSOR_BRUSH:
		p1.x = 150;
		p1.y = 0;
		p2.x = 300;
		p2.y = 150;
		break;
	case CONSTANT::CURSOR_RECT:
		p1.x = 300;
		p1.y = 0;
		p2.x = 450;
		p2.y = 150;
		break;
	case CONSTANT::CURSOR_CIR:
		p1.x = 450;
		p1.y = 0;
		p2.x = 600;
		p2.y = 150;
		break;
	default:
		break;
	}
	cvRectangle(frame, p1,p2, cvScalar(0,0,255), 5);

	overlayImage(src, frame, cvPoint(200, 0), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	
	cvReleaseImage(&frame);

	return src;
}
vector<IplImage*> cAnimation::showMenu(CvSize size) {
	vector<IplImage*> ani;
	
	return ani;
}

IplImage* cAnimation::drawColorTable(IplImage* src, int CHOSEN_COLOR) {
	IplImage * frame;
	frame = cvCreateImage(cvSize(200, 450), IPL_DEPTH_32F, 3);
	cvRectangle(frame, cvPoint(0,0), cvPoint(200, 450), cvScalar(255,255,255), CV_FILLED);

	IplImage * menu = cvLoadImage("image/color_red.png",1);
	overlayImage(frame, menu,  cvPoint(0,0), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);
	
	menu = cvLoadImage("image/color_yellow.png",1);
	overlayImage(frame, menu,  cvPoint(0,70), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);

	menu = cvLoadImage("image/color_blue.png",1);
	overlayImage(frame, menu,  cvPoint(0,140), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);

	menu = cvLoadImage("image/color_green.png",1);
	overlayImage(frame, menu,  cvPoint(0,210), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);
	
	menu = cvLoadImage("image/color_purple.png",1);
	overlayImage(frame, menu,  cvPoint(0,280), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);
	
	menu = cvLoadImage("image/color_custom.png",1);
	overlayImage(frame, menu,  cvPoint(0,350), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&menu);

	CvPoint p1,p2;
	switch(CHOSEN_COLOR) {
	case CONSTANT::COLOR_RED:
		p1.x = 0;
		p1.y = 0;
		p2.x = 200;
		p2.y = 70;
		break;
	case CONSTANT::COLOR_YELLOW:
		p1.x = 0;
		p1.y = 70;
		p2.x = 200;
		p2.y = 140;
		break;
	case CONSTANT::COLOR_BLUE:
		p1.x = 0;
		p1.y = 140;
		p2.x = 200;
		p2.y = 210;
		break;
	case CONSTANT::COLOR_GREEN:
		p1.x = 0;
		p1.y = 210;
		p2.x = 200;
		p2.y = 280;
		break;
	case CONSTANT::COLOR_PURPLE:
		p1.x = 0;
		p1.y = 280;
		p2.x = 200;
		p2.y = 350;
		break;
	case CONSTANT::COLOR_CUSTOM:
		p1.x = 0;
		p1.y = 350;
		p2.x = 200;
		p2.y = 450;
		break;
	default:
		break;
	}
	cvRectangle(frame, p1,p2, cvScalar(0,0,255), 3);
	overlayImage(src, frame, cvPoint(0, 150), cvScalar(0,0,0,0), cvScalar(1,1,1,1));
	cvReleaseImage(&frame);
		
	return src;
}
void cAnimation::display(IplImage* dest, vector<IplImage*> src, int rate) {
	for(int i = 0; i < src.size(); i ++) {
		overlayImage(dest, src[i], cvPoint(0,0), cvScalar(0.5,0.5,0.5,0.5), cvScalar(0.5,0.5,0.5,0.5));
		cvShowImage("window", dest);	
		cvWaitKey(1000/30);
	}
}

CvPoint2D32f cAnimation::trackColor(CvScalar color, IplImage* frame) {
	CvPoint2D32f pos;

	IplImage* imgThreshed;
	IplImage* imgHSV;

	imgHSV = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
	cvCvtColor(frame, imgHSV,CV_BGR2HSV_FULL);
		
	//thresh hold
	imgThreshed = cvCreateImage(cvGetSize(frame), frame->depth, 1);
	cvInRangeS(imgHSV, cvScalar(color.val[0] - 10, color.val[1] - 30, 100), cvScalar(color.val[0] +10, 255,255), imgThreshed);

	//Erode to reduce noise
	cvErode(imgThreshed, imgThreshed, NULL, 4);
	cvDilate(imgThreshed, imgThreshed, NULL, 4);

	//Estimate the position of the object using moment
	CvMoments *moment = new CvMoments();
	cvMoments(imgThreshed, moment, 1);

	double moment10 = cvGetSpatialMoment(moment, 1, 0);
	double moment01 = cvGetSpatialMoment(moment, 0, 1);
	double moment00 = cvGetCentralMoment(moment, 0, 0);

	if (moment00 > 30) {
		pos.x = moment10/moment00;
		pos.y = moment01/moment00;
	} else {
		pos.x = -1;
		pos.y = -1;
	}
	
	cvReleaseImage(&imgThreshed);
	cvReleaseImage(&imgHSV);
	delete moment;

	return pos;
}
void cAnimation::handleChooseAction(int ACTION, IplImage* frame) {
	CvPoint p1, p2;
	switch (ACTION) {
	case CONSTANT::ACTION_CHOOSE_PEN:
		p1.x = 200;
		p1.y = 0;
		p2.x = 350;
		p2.y = 150;
		break;
	case CONSTANT::ACTION_CHOOSE_BRUSH:
		p1.x = 350;
		p1.y = 0;
		p2.x = 500;
		p2.y = 150;
		break;
	case CONSTANT::ACTION_CHOOSE_RECT:
		p1.x = 500;
		p1.y = 0;
		p2.x = 650;
		p2.y = 150;
		break;
	case CONSTANT::ACTION_CHOOSE_CIR:
		p1.x = 650;
		p1.y = 0;
		p2.x = 800;
		p2.y = 150;
		break;
	case CONSTANT::ACTION_CHOOSE_COLOR_RED:
		p1.x = 0;
		p1.y = 150;
		p2.x = 200;
		p2.y = 220;
		break;
	case CONSTANT::ACTION_CHOOSE_COLOR_YELLOW:
		p1.x = 0;
		p1.y = 220;
		p2.x = 200;
		p2.y = 290;
		break;
	case CONSTANT::ACTION_CHOOSE_COLOR_BLUE:
		p1.x = 0;
		p1.y = 290;
		p2.x = 200;
		p2.y = 360;
		break;
	case CONSTANT::ACTION_CHOOSE_COLOR_GREEN:
		p1.x = 0;
		p1.y = 360;
		p2.x = 200;
		p2.y = 430;
		break;
	case CONSTANT::ACTION_CHOOSE_COLOR_PURPLE:
		p1.x = 0;
		p1.y = 430;
		p2.x = 200;
		p2.y = 500;
		break;
	case CONSTANT::ACTION_CHOOSE_COLOR_CUSTOM:
		p1.x = 0;
		p1.y = 500;
		p2.x = 200;
		p2.y = 600;
		break;
	}
	cvRectangle(frame, p1, p1, cvScalar(255,127,39), 3);
}