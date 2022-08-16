#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void CaptureVideo() {

	VideoCapture cap(0);
	// OpenCV에서는 VideoCapture라는 클래스를 이용해 카메라 또는 동영상 파일로부터 정지 영상 프레임을 받아 올 수 있음
	// 동영상 파일을 불러올 때는 "파일 이름" 을 인자로 넣고, 파일이 다른 폴더에 있으면 절대경로 또는 상대경로 추가함
	// 카메라 장치를 열 때에는 카메라 장치 id 번호를 정수 값으로 전달. 0으로 해서 안되면 1, 2 시도

	if (!cap.isOpened()) {	// 예외처리
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	// get() 함수로 카메라 또는 동영상 파일로부터 여러 정보를 받아 올 수 있음. 매개변수는 열거형 상수 Properties 가 들어감

	cout << "Width : " << w << endl;
	cout << "Height : " << h << endl;

	Mat frame1, frame2;
	cap >> frame1;		// 1st frame
	cap.read(frame2);	// 2nd frame
	// >>() 연산자 재정의 또는 read() 함수를 사용하여 카메라 또는 동영상 파일로부터 한 프레임의 정지 영상을 받아옴
	// 내부적으로 read()함수는 grab() 과 retrieve() 함수를 호출하는 형태

	imshow("img1", frame1);
	imshow("img2", frame2);

	waitKey(0); // 매개변수가 0이면 무한 대기
}

void cameraIn() {

	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	Mat frame, inversed;

	while (true) {

		cap >> frame;
		if (frame.empty())
			continue;
		inversed = ~frame;	// 반전

		//line(frame, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27)	// 10ms 동안 키보드 입력 대기, 키보드 입력고 있고 해당 키값이 ESC 면 루프 나감
			break;
	}
	destroyAllWindows();

	// cameraIn() 함수 종료 시 소멸자 호출되며 자동으로 cap 변수 소멸
}

void vedioIn() {

	VideoCapture cap("stopwatch.avi");
	// 동영상의 오디오는 출력하지 않음

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;

	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;
	int delay = cvRound(1000 / fps);
	// 동영상 파일의 FPS값을 이용하여 매 프레임 사이의 시간간격을 ms 단위로 구함
	// 초당 30프레임을 재생하는 동영상의 경우 딜레이는 33ms 가 됨


	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			continue;
		inversed = ~frame;	// 반전

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)	// ESC key delay 값을 10ms으로 줄이면 영상이 빨라짐
			break;
	}
	destroyAllWindows();

}

void camera_in_video_out() {

	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	//double fps = cap.get(CAP_PROP_FPS);		// 카메라 종류에 따라 지원하지 않는 경우도 있음. 그런 경우 30 대입
	double fps = 30;
	int delay = cvRound(1000 / fps);

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	// VideoWriter 생성자 또는 open()함수의 두 번째 인자인 fourcc는 4-문자 코드(four character code)의 약자로
	// 동영상 파일의 코덱을 표현하는 네 개의 문자를 묶어서 fourcc를 생성함

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));
	// 저장할 동영상 파일 생성

	if (!outputVideo.isOpened()) {
		cerr << "File open Failed!" << endl;
		return;
	}

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			continue;

		inversed = ~frame;	// 반전

		outputVideo << inversed;
		// 열려 있는 동영상 파일에 새 프레임을 추가하기 위해서는 << 연산자 재정의 또는 VideoWriter::write() 함수를 사용
		// 다만 새로 추가하는 프레임 크기는 동영상 파일을 생성할 때 지정한 프레임 크기와 같아야함
		// 또한 컬러로 설정된 동영상 파일에 그레이스케일 영상을 추가하면 정상적으로 저장되지 않으므로 주의


		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}
	destroyAllWindows();

}

void drawLines() {
	
	Mat im = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat img;
	cvtColor(im, img, COLOR_GRAY2BGR);
	//흑백영상 위에 그리면 원래 도형도 흑백으로 그려짐. 위 코드는 흑백 영상위에 컬러 도형을 그리는 방법 중 하나

	//Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));
	line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);
	line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);

	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
	line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
	line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);

	arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);
	arrowedLine(img, Point(50, 250), Point(350, 250), Scalar(255, 0, 255), 1);
	arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05);

	imshow("img", img);
	waitKey();

	drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);
	drawMarker(img, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS);
	drawMarker(img, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);
	drawMarker(img, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);
	drawMarker(img, Point(250, 350), Scalar(0, 0, 255), MARKER_SQUARE);
	drawMarker(img, Point(300, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_UP);
	drawMarker(img, Point(350, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_DOWN);

	imshow("img", img);

	waitKey();

	destroyAllWindows();

}

void drawPolys() {

	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2);
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1);

	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA);
	circle(img, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_AA);

	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), -1, LINE_AA);
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);

	vector<Point> pts;
	pts.push_back(Point(250, 250));
	pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300));
	pts.push_back(Point(350, 300));
	pts.push_back(Point(350, 350));
	pts.push_back(Point(250, 350));
	//polylines(img, pts, true, Scalar(255, 0, 255), 2);
	fillPoly(img, pts, Scalar(0, 255, 255));


	imshow("img", img);
	waitKey(0);
	destroyAllWindows();

}

void drawText1() {

	Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255));

	putText(img, "FONT_HERSHEY_SIMPLEX", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_PLAIN", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_DUPLEX", Point(20, 150), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX", Point(20, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_TRIPLEX", Point(20, 250), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_COMPLEX_SMALL", Point(20, 300), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_SCRIPT_SIMPLEX", Point(20, 350), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_SCRIPT_COMPLEX", Point(20, 400), FONT_HERSHEY_SCRIPT_COMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX | FONT_ITALIC", Point(20, 450), FONT_HERSHEY_COMPLEX | FONT_ITALIC, 1, Scalar(255, 0, 0));

	imshow("img", img);
	waitKey(0);

}

void drawText2() {

	Mat img(200, 640, CV_8UC3, Scalar(255, 255, 255));

	const String text = "Hello, OpenCV";
	int fontFace = FONT_HERSHEY_TRIPLEX;
	double fontScale = 2.0;
	int thickness = 1;
	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0);
	Size sizeImg = img.size();

	Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2);

	putText(img, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness);

	rectangle(img, org, org + Point(sizeText.width, -sizeText.height), Scalar(255, 0, 0), 1);
	

	imshow("img", img);
	waitKey(0);
}

void keyboard() {

	Mat img = imread("lenna.bmp");

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	namedWindow("img");
	imshow("img", img);

	while (true) {
		int keycode = waitKey();
		// 매개변수인 밀리초 단위로 대기하고 delay<=0 이면 무한히 기다림. 반환값은 눌려진 키 값

		if (keycode == 'i' || keycode == 'I')
		{
			img = ~img;
			imshow("img", img);
		}
		else if( keycode == 27 || keycode=='q'|| keycode == 'Q')
		{
			break;
		}
	}
}



// 전역으로 선언
Mat img;
Point ptOld;
Point ptNew;
int toggleFill=1;
void on_mouse(int event, int x, int y, int flags, void*);


void mouse() {	

	img = imread("lenna.bmp");

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	namedWindow("img");
	setMouseCallback("img", on_mouse); // 마우스 콜백 함수를 등록

	imshow("img", img);

	while (true) {
		int keycode = waitKey();

		if (keycode == 'c' || keycode == 'C')
		{
			img = imread("lenna.bmp");
			imshow("img", img);
		}else if (keycode == 'f' || keycode == 'F')
		{
			toggleFill = toggleFill > -1 ? -1 : 1;
		}
		else if (keycode == 27 || keycode == 'q' || keycode == 'Q')
		{
			break;
		}
	}
}

void on_mouse(int event, int x, int y, int flags, void*) {

	//cout << "PtNew: " << ptNew << endl;
	cout << "flags: " << flags << endl;
	
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);
		//cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl;
		break;
	case EVENT_LBUTTONUP:
		//cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl;
		if (ptNew.x != 0 && ptNew.y != 0) {
			rectangle(img, ptOld, ptNew, Scalar(255, 0, 0), toggleFill);
			imshow("img", img);
			ptNew = Point(0, 0);
		}
		//cout << "PtNew: " << ptNew << endl;
		break;
	case EVENT_MOUSEMOVE:
		if (flags == (EVENT_FLAG_LBUTTON | EVENT_FLAG_CTRLKEY)) {
			ptNew = Point(x, y);
			//cout << "ptOld: " << ptOld << endl;
			//cout << "flags: " << flags << endl;
		}else if (flags & EVENT_FLAG_LBUTTON) {
			line(img, ptOld, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", img);
			ptOld = Point(x, y);
		}
		break;
	default:
		break;
	}	
}


int main()
{
	//CaptureVideo();
	//cameraIn();
	//vedioIn();
	//camera_in_video_out();
	//drawLines();
	//drawPolys();
	//drawText1();
	//drawText2();
	//keyboard();
	mouse();

	return 0;
}
