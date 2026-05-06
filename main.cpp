#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, dst;

void on_mouse(int event, int x, int y, int flags, void* userdata) {
    // 1. 왼쪽 버튼이 눌려 있는 상태(EVENT_FLAG_LBUTTON)에서 마우스가 움직일 때(EVENT_MOUSEMOVE)
    if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {

        // 점 5개를 찍을 위치를 배열로 만들어요 (중앙, 위, 아래, 왼쪽, 오른쪽)
        Point points[5] = {
            Point(x, y),         // 현재 마우스 위치
            Point(x, y - 1),     // 위
            Point(x, y + 1),     // 아래
            Point(x - 1, y),     // 왼쪽
            Point(x + 1, y)      // 오른쪽
        };

        for (int i = 0; i < 5; i++) {
            int cur_x = points[i].x;
            int cur_y = points[i].y;

            // 2. 사진 범위를 벗어나지 않는지 확인 (매우 중요!)
            if (cur_x >= 0 && cur_x < dst.cols && cur_y >= 0 && cur_y < dst.rows) {
                // 3. 해당 위치의 픽셀값을 100 증가 (saturate_cast로 안전하게!)
                dst.at<uchar>(cur_y, cur_x) = saturate_cast<uchar>(dst.at<uchar>(cur_y, cur_x) + 100);
            }
        }

        imshow("image", dst);
    }
}

int main() {
    src = imread("lenna.bmp", IMREAD_GRAYSCALE);
    if (src.empty()) { return -1; }

    dst = src.clone();
    namedWindow("image");
    setMouseCallback("image", on_mouse);

    imshow("image", dst);

    while (true) {
        if (waitKey(1) == 'q') break;
    }

    return 0;
}