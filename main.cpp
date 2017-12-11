#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdint.h>

using namespace cv;

//img - grayscale 640x480
cv::Point getBritestPoint(const cv::Mat& img);
int32_t getDistanceToPoint(const cv::Point& brP);


int main(int argc, char **argv)
{
	namedWindow("stream",1);
	namedWindow("gray",1);
	VideoCapture cap(0); // open the default camera
	Mat frame;
	Mat grayframe;
	
	if(!cap.isOpened())  // check if we succeeded
		return -1;
	
	int width = 640;
	int height = 480;
	int fps = 60;
	
	cap.set(CV_CAP_PROP_FRAME_WIDTH,width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,height);
	cap.set(CV_CAP_PROP_FPS,fps);	
	
	
	cap >> frame; // get a new frame from camera
	if(frame.empty())
	{
		printf("Can' get any frame from source!\n");
		return 1;
	}
	
	printf("Resolution: %dx%d\n", frame.cols, frame.rows);
	
	for(;;)
	{		
		cap >> frame; // get a new frame from camera		
		
		cv::Mat BGR[3];
		cv::split(frame, BGR);
		//cv::cvtColor(frame, grayframe, CV_BGR2GRAY);
		cv::Point brP = getBritestPoint(BGR[2]);
		
		cv::Rect brRect(brP.x-4, brP.y-4, 8, 8);
		cv::rectangle(frame, brRect, cv::Scalar(0,255,0), -1);
		imshow("stream", frame);
		imshow("gray", BGR[2]);
		if(waitKey(12) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;	
	
}

cv::Point getBritestPoint(const cv::Mat& img)
{
	if(img.type() != CV_8UC1) return cv::Point(-1,-1);
	int maxI = 0;
	for(int i=0; i<img.cols*img.rows; i++)
	{
		if(img.data[i]>img.data[maxI])
		{
			maxI = i;
		}
	}
	
	return cv::Point(maxI%img.cols,maxI/img.cols);	
}

int32_t getDistanceToPoint(const cv::Point& brP)
{
	return 0;
}
