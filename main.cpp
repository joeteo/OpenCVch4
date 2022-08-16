#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void CaptureVideo() {

	VideoCapture cap(0);
	// OpenCV������ VideoCapture��� Ŭ������ �̿��� ī�޶� �Ǵ� ������ ���Ϸκ��� ���� ���� �������� �޾� �� �� ����
	// ������ ������ �ҷ��� ���� "���� �̸�" �� ���ڷ� �ְ�, ������ �ٸ� ������ ������ ������ �Ǵ� ����� �߰���
	// ī�޶� ��ġ�� �� ������ ī�޶� ��ġ id ��ȣ�� ���� ������ ����. 0���� �ؼ� �ȵǸ� 1, 2 �õ�

	if (!cap.isOpened()) {	// ����ó��
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	// get() �Լ��� ī�޶� �Ǵ� ������ ���Ϸκ��� ���� ������ �޾� �� �� ����. �Ű������� ������ ��� Properties �� ��

	cout << "Width : " << w << endl;
	cout << "Height : " << h << endl;

	Mat frame1, frame2;
	cap >> frame1;		// 1st frame
	cap.read(frame2);	// 2nd frame
	// >>() ������ ������ �Ǵ� read() �Լ��� ����Ͽ� ī�޶� �Ǵ� ������ ���Ϸκ��� �� �������� ���� ������ �޾ƿ�
	// ���������� read()�Լ��� grab() �� retrieve() �Լ��� ȣ���ϴ� ����

	imshow("img1", frame1);
	imshow("img2", frame2);

	waitKey(0); // �Ű������� 0�̸� ���� ���
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
		inversed = ~frame;	// ����

		//line(frame, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27)	// 10ms ���� Ű���� �Է� ���, Ű���� �Է°� �ְ� �ش� Ű���� ESC �� ���� ����
			break;
	}
	destroyAllWindows();

	// cameraIn() �Լ� ���� �� �Ҹ��� ȣ��Ǹ� �ڵ����� cap ���� �Ҹ�
}

void vedioIn() {

	VideoCapture cap("stopwatch.avi");
	// �������� ������� ������� ����

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
	// ������ ������ FPS���� �̿��Ͽ� �� ������ ������ �ð������� ms ������ ����
	// �ʴ� 30�������� ����ϴ� �������� ��� �����̴� 33ms �� ��


	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			continue;
		inversed = ~frame;	// ����

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)	// ESC key delay ���� 10ms���� ���̸� ������ ������
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
	//double fps = cap.get(CAP_PROP_FPS);		// ī�޶� ������ ���� �������� �ʴ� ��쵵 ����. �׷� ��� 30 ����
	double fps = 30;
	int delay = cvRound(1000 / fps);

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	// VideoWriter ������ �Ǵ� open()�Լ��� �� ��° ������ fourcc�� 4-���� �ڵ�(four character code)�� ���ڷ�
	// ������ ������ �ڵ��� ǥ���ϴ� �� ���� ���ڸ� ��� fourcc�� ������

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));
	// ������ ������ ���� ����

	if (!outputVideo.isOpened()) {
		cerr << "File open Failed!" << endl;
		return;
	}

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			continue;

		inversed = ~frame;	// ����

		outputVideo << inversed;
		// ���� �ִ� ������ ���Ͽ� �� �������� �߰��ϱ� ���ؼ��� << ������ ������ �Ǵ� VideoWriter::write() �Լ��� ���
		// �ٸ� ���� �߰��ϴ� ������ ũ��� ������ ������ ������ �� ������ ������ ũ��� ���ƾ���
		// ���� �÷��� ������ ������ ���Ͽ� �׷��̽����� ������ �߰��ϸ� ���������� ������� �����Ƿ� ����


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
	//��鿵�� ���� �׸��� ���� ������ ������� �׷���. �� �ڵ�� ��� �������� �÷� ������ �׸��� ��� �� �ϳ�

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
		// �Ű������� �и��� ������ ����ϰ� delay<=0 �̸� ������ ��ٸ�. ��ȯ���� ������ Ű ��

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



// �������� ����
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
	setMouseCallback("img", on_mouse); // ���콺 �ݹ� �Լ��� ���

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
