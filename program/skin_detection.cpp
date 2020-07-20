#include<opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>


using namespace std;
using namespace cv;

int main() {
	cv::Mat input = cv::imread("in/M-046-21.bmp");

	cv::Mat hsv;
	cv::cvtColor(input, hsv, COLOR_BGR2HSV);

	double scaleSatLower = 0.28;
	double scaleSatUpper = 0.68;
	//double scaleSatLower = 0.18; // maybe better
	//double scaleSatLower = 0.08; // maybe too much
	//double scaleSatUpper = 0.78;
	cv::Scalar lower = cv::Scalar(0, scaleSatLower * 255, 0);
	cv::Scalar upper = cv::Scalar(25, scaleSatUpper * 255, 255);

	cv::Mat result;
	cv::inRange(hsv, lower, upper, result);
	cv::imshow("result", result);
	

	for (int x = 0; x < input.rows; x++) {
		int non_skin_count = 0;

		for (int y = 0; y < input.cols; y++) {
			//x * input.cols + y
			int colour = result.at<uchar>(x, y);
			if (colour == 0) {
				non_skin_count = non_skin_count + 1;
			}
		}

		if (non_skin_count >= input.cols / 2) {
			for (int y = 0; y < input.cols; y++) {
				input.at<Vec3b>(x * input.cols + y) = Vec3b(255, 255, 255);
			}
		}
	}

	cv::imshow("input", input);
	cv::imwrite("out/M-046-21.bmp", input);
	cv::waitKey(0);
	return 0;
}