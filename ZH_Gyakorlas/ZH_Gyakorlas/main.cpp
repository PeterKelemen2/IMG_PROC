#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void Elso()
{
	cv::Mat img = cv::imread("C:\\Users\\Administrator\\source\\repos\\ZH_Gyakorlas\\book.jpg", 1);
	cv::Mat filtered;
	cv::Mat hsv, mask, masked;
	cv::Mat splitted[3], tempmask[3], finalmask, result;

	cv::GaussianBlur(img, filtered, cv::Size(5, 5), 0.5);
	cv::medianBlur(img, filtered, 3);

	cv::cvtColor(filtered, hsv, cv::COLOR_RGB2HSV);
	unsigned char n = 0; // default: 0

	std::cout << "Enter value to be filtered by: ";
	std::cin >> n;
	cv::split(hsv, splitted);
	cv::threshold(splitted[0], mask, n, 255, cv::THRESH_BINARY);

	for (int i = 0; i < 3; ++i)
		tempmask[i] = mask.clone();

	cv::merge(tempmask, 3, finalmask);
	cv::bitwise_and(img, finalmask, masked);

	cv::cvtColor(masked, hsv, cv::COLOR_RGB2HSV);
	unsigned char hue = 0, sat = 0, value = 0; // default: 0,0,0
	std::cout << "Enter Hue value: ";
	std::cin >> hue;
	std::cout << "Enter Saturation value: ";
	std::cin >> sat;
	std::cout << "Enter Value value: ";
	std::cin >> value;

	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			cv::Vec3b pixelGroup = hsv.at<cv::Vec3b>(i, j);
			pixelGroup[0] += hue;
			pixelGroup[1] += sat;
			pixelGroup[2] += value;

			hsv.at<cv::Vec3b>(i, j) = pixelGroup;
		}
	}

	cv::cvtColor(hsv, result, cv::COLOR_HSV2RGB);

	std::vector<int> formatParameters_jpg;
	formatParameters_jpg.push_back(cv::IMWRITE_JPEG_QUALITY);
	formatParameters_jpg.push_back(92);
	cv::imwrite("out.jpg", result, formatParameters_jpg);

	cv::imshow("img", img);
	cv::imshow("result", result);
	cv::waitKey();
}

void Masodik()
{
	std::string path;
	path = "C:\\Users\\Administrator\\source\\repos\\ZH_Gyakorlas\\book.jpg";
	// std::cout << "Enter path to image: "; 
	// std::cin >> path;

	cv::Mat img = cv::imread(path);
	cv::Mat mask, hsv, splitted[3];

	unsigned char thresholdValue = 0;
	std::cout << "Enter threshold value: ";
	std::cin >> thresholdValue;
	cv::cvtColor(img, hsv, cv::COLOR_RGB2HSV);
	cv::split(hsv, splitted);
	cv::threshold(splitted[0], mask, thresholdValue, 255, cv::THRESH_BINARY);
	//inicializaljuk az eredmenymatrixot
	//a legegyszerubb ha a beepitett Point osztalyt hasznaljuk a koordinatak tarolalasa vectorban
	cv::Mat masked(hsv.size(), CV_8UC3);
	std::vector<cv::Point> indexes;
	cv::imshow("mask", mask);
	cv::waitKey();
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			//ahol a mask pixel nem nulla ott szurunk tovabbi belso if-fel
			//a belso ifben kulon sorba vannak a feltetelek csatornankent
			if (mask.at<uchar>(i, j)) {
				cv::Vec3b pixelgroup = hsv.at<cv::Vec3b>(i, j);
				if (pixelgroup[0] <= thresholdValue * 2 &&
					(pixelgroup[1] >= 50 && pixelgroup[1] <= 170) &&
					(pixelgroup[2] >= 100 && pixelgroup[2] <= 200)
					) {
					masked.at<cv::Vec3b>(i, j) = pixelgroup;
					indexes.push_back(cv::Point(i, j));
				}

			}
		}
	}

	//veletlenszeru torles es morfologia
	cv::Mat structElement = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));

	//itt sokfajta megoldas is van a vector bejarasara, ez a fapados verzio
	for (int i = 0; i < indexes.size(); ++i) {
		float n = std::rand() / RAND_MAX;

		//itt a vector adott elemet erjuk el a begin a legelso elem lesz mig az i hogy hanyadik elemnel jarunk
		if (n > 0.5) indexes.erase(indexes.begin() + i);
	}

	cv::Mat mask2(mask.size(), CV_8UC1);

	for (int i = 0; i < indexes.size(); ++i) {
		mask2.at<uchar>(indexes.at(i).x, indexes.at(i).y) = 255;
	}

	cv::Mat opened;
	cv::Mat eroded;
	cv::Mat tempMask[3], finalMask;
	cv::Mat hsv_result;

	cv::erode(mask2, eroded, structElement);
	cv::dilate(eroded, opened, structElement);

	for (int i = 0; i < 3; ++i)
		tempMask[i] = opened.clone();

	cv::merge(tempMask, 3, finalMask);
	cv::bitwise_and(hsv, finalMask, hsv_result);

	cv::imshow("finalMask", finalMask);
	cv::imshow("hsv_result", hsv_result);
	cv::waitKey();

	unsigned char hue = 20, sat = 60, val = 120; // default: 0,0,0
	/*
	std::cout << "Enter Hue value: "; 
	std::cin >> hue;
	std::cout << "Enter Saturation value: "; // 50 - 170
	std::cin >> sat;
	std::cout << "Enter Value value: "; // 100 - 200
	std::cin >> val;
	*/
	for (int i = 0; i < hsv_result.rows; ++i) {
		for (int j = 0; j < hsv_result.cols; ++j) {
			cv::Vec3b pixelGroup = hsv_result.at<cv::Vec3b>(i, j);
			if (pixelGroup == cv::Vec3b(0, 0, 0))
				pixelGroup = cv::Vec3b(hue, sat, val);
			hsv_result.at<cv::Vec3b>(i, j) = pixelGroup;
		}
	}

	cv::Mat result;
	cv::cvtColor(hsv_result, result, cv::COLOR_HSV2RGB);

	cv::imshow("result", result);
	cv::waitKey();
}


int main()
{

	Elso();

	Masodik();

    return 0; 
}
