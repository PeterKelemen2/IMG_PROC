#include "FilterHandler.hh"

int main()
{

	//cv::Mat I = cv::imread("test.jpg", 1);

	FilterHandler filterHandler;
	filterHandler.demoBoxFilter();
	// filterHandler.demoGaussianFilter();
	// filterHandler.demoMedianFilter();
	// filterHandler.demoHistoEqualize();
	// filterHandler.demoRGBHistoEqualize();
	return 0;
}