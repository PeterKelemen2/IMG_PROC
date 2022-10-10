#include <iostream>

// meg kell adni az elérési útat, mert fogyatékot kap másképp
#include "C:\opencv\build\include\opencv2\core.hpp"
#include "C:\opencv\build\include\opencv2\imgproc.hpp"
#include "C:\opencv\build\include\opencv2\highgui.hpp"

void demoDilateErode() { // Diláció,Erózió
    cv::Mat Img = cv::imread("morp_test.png", 0);

    cv::Mat kernel = cv::Mat::ones(cv::Size(5, 5), CV_8UC1);
    cv::Mat dilated, eroded;
    cv::dilate(Img, dilated, kernel);
    cv::erode(Img, eroded, kernel);

    cv::imshow("dilated", dilated);
    cv::imshow("eroded", eroded);
    cv::waitKey();
}

void demoOpened() { // Nyitás
    cv::Mat Img = cv::imread("morp_test.png", 0);
    cv::Mat kernel = cv::Mat::ones(cv::Size(3, 3), CV_8UC1);
    cv::Mat eroded, opened;
    cv::erode(Img, eroded, kernel);
    cv::dilate(eroded, opened, kernel);

    cv::imshow("eroded", eroded);
    cv::imshow("opened", opened);
    cv::waitKey();
}

void demoClosed() { // Zárás
    cv::Mat Img = cv::imread("morp_test.png", 0);
    cv::Mat kernel = cv::Mat::ones(cv::Size(7, 7), CV_8UC1);
    cv::Mat dilated, closed;
    cv::dilate(Img, dilated, kernel);
    cv::erode(dilated, closed, kernel);

    cv::imshow("dilated", dilated);
    cv::imshow("closed", closed);
    cv::waitKey();
}

int main()
{
    demoDilateErode();
    demoOpened();
    demoClosed();
}
