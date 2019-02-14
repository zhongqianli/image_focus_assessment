#include <opencv2/opencv.hpp>

double image_focus_assessment(const cv::Mat &src)
{
    cv::Mat gray;
    if(src.channels() == 3)
        cv::cvtColor( src, gray, CV_BGR2GRAY);
    else
        gray = src;

    cv::Mat kernel;
    cv::Point anchor;
    double delta;
    int ddepth;

    anchor = cv::Point( -1, -1 );
    delta = 0;
    ddepth = -1;

    // reference: How Iris Recognition Works. John Daugman. 2004
    float data[8][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1,  3,  3,  3,  3, -1, -1},
        {-1, -1,  3,  3,  3,  3, -1, -1},
        {-1, -1,  3,  3,  3,  3, -1, -1},
        {-1, -1,  3,  3,  3,  3, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}
    };
    kernel = cv::Mat(8, 8, CV_32F, data);

    cv::Mat src_32f;
    gray.convertTo(src_32f, CV_32F);
    cv::Mat dst;
    cv::filter2D(src_32f, dst, ddepth , kernel, anchor, delta, cv::BORDER_DEFAULT );

    double power = 0;
    double score = 0;
    for(int row = 0; row < dst.rows; ++row)
        for(int col = 0; col < dst.cols; ++col)
        {
            power += abs(dst.at<float>(row, col));
        }
    const int FOCUS_SCORE_50PERCENT = 60;
    score = (power * power) / (power * power + FOCUS_SCORE_50PERCENT * FOCUS_SCORE_50PERCENT) * 100.0f + 0.5f;

    return score;
}
