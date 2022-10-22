#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


int main()
{
    cv::Mat kep = cv::imread("test.jpg");
    cv::imshow("teszt", kep);
    cv::waitKey();

    return 0; 
}
