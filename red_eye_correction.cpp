#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;
CascadeClassifier eyes_cascade("C:/Opencv3/install/etc/haarcascades/haarcascade_eye.xml");
int main() {
	Mat img = imread("e:/red_eye.jpg", CV_LOAD_IMAGE_COLOR);
	Mat eyeOut=img.clone();
	Mat imgOut = img.clone();
	std::vector<Rect> eyes;
	imshow("asd", img);
	eyes_cascade.detectMultiScale(img, eyes, 1.3, 4, 0 | CASCADE_SCALE_IMAGE, Size(100, 100));
	for (size_t i = 0; i < eyes.size(); i++)
	{
		Mat eye = img(eyes[i]);
		vector<Mat>bgr(3);
		split(eye, bgr);
		for (int a = 0;a < eye.rows;a++) {
			for (int b = 0;b < eye.cols;b++)
			{
				if (bgr[0].at<uchar>(a,b) + bgr[1].at<uchar>(a, b) <= bgr[2].at<uchar>(a, b))
					bgr[2].at<uchar>(a, b) = bgr[0].at<uchar>(a, b)/2 + bgr[1].at<uchar>(a, b)/2;
			}
		}
		merge(bgr,eyeOut);
		Mat element = getStructuringElement(MORPH_RECT,
			Size(3,  3),
			Point(-1, -1));

		//
		//dilate(eyeOut,eyeOut,element);
//		imshow("eye", eye);
		//Mat mask = (bgr[2] > 150) &amp; (bgr[2] & gt; (bgr[1] + bgr[0]));
		eyeOut.copyTo(imgOut(eyes[i]));
	}
	imshow("Result",imgOut);
	waitKey(1000);
	imwrite("e:/result.jpg", imgOut);

	return 0;
}