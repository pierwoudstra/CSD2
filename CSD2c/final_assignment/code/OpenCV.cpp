#include "opencv2/opencv.hpp"
#include <stdint.h>

using namespace cv;
using namespace std;

const int fps = 20;

int main() 
{
    Mat frame;

    VideoCapture vid(0);

    if (!vid.isOpened())
    {
        return -1;
    }

    while (vid.read(frame))
    {
        // Convert frame to grayscale
        Mat grayFrame;
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        // Calculate average brightness
        Scalar avgPixelIntensity = mean(grayFrame);
        double brightness = avgPixelIntensity[0]; // The brightness value

        cout << "Brightness: " << brightness << endl;

        imshow("Webcam", frame);

        if (waitKey(1000 / fps) >= 0)
            break;
    }

    return 1;
}
