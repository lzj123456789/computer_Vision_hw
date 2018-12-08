#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace cv;
bool recordVideo = false;
bool isDrawing = false;
Mat frame;
Point p,pt;
std::vector<Point> v,vt;

static void onMouse(int event, int x, int y, int ,void *){
	
	if(event==EVENT_LBUTTONUP){
		isDrawing = false;
		v.push_back(p);
		vt.push_back(pt);
	}else if(event == EVENT_LBUTTONDOWN){
		isDrawing = true;
		p = Point(x,y);
	}else if(event == EVENT_MOUSEMOVE){
		if(isDrawing){
			pt = Point(x,y);
			line(frame,p,pt,Scalar(0,0,255),2,5,0);
			//p = pt;
			imshow("frame",frame);
		}
	}
	//imshow("frame",frame);
	printf("%d %d %d\n",event,x,y );
}

int main(int argc, char const *argv[])
{
	VideoCapture cap(0);
	if(!cap.isOpened()){
		printf("Can not open!\n");
		return -1;
	}
	int videoNum = 0;
	while(1){
		cap>>frame;
		namedWindow("frame");
		setMouseCallback("frame",onMouse,0);
		for(unsigned int i = 0;i<v.size();i++){
			line(frame,v[i],vt[i],Scalar(0,0,255),2,5,0);
		}
		imshow("frame",frame);
		int key = waitKey(20);
		if(key==32) recordVideo = true;
		if(recordVideo){
			videoNum++;
			string videoName = "video" + to_string(videoNum)+".avi";
			double fps = 25;
			CvSize frame_size = frame.size();
			bool isColor = true;
			cout<<videoName<<" recording"<<endl;
			VideoWriter vw = VideoWriter(videoName,CV_FOURCC('M','J','P','G'),fps,frame_size,isColor);
			if(!vw.isOpened()){
				printf("VideoWriter open failed\n");
				recordVideo = false;
				continue;
			}
			while(1){
				cap>>frame;
				for(unsigned int i=0;i<v.size();i++){
					line(frame,v[i],vt[i],Scalar(0,0,255),2,5,0);
				}
				imshow("frame",frame);
				vw.write(frame);
				int tmp = waitKey(20);
				if(tmp == 32){
					break;
				}
			}
			cout<<videoName<<" finished!"<<endl;
			recordVideo = false;
		}
		//if(key>=0) printf("%d\n", key);
		if(key==27) break;
	}
	return 0;
}