#include <iostream>
#include <opencv2/opencv.hpp>
#include <wiringSerial.h>
#include <unistd.h>
using namespace cv;
using namespace std;

#define x_max 410
#define x_min 390
#define y_max 310
#define y_min 290
int main()
{
    int fd;
    if ((fd = serialOpen("/dev/ttyAMA0", 115200)) < 0)
    {
        //fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        return 1;
    }
    VideoCapture cap;
    cap.open(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 800);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
    cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    cap.set(CAP_PROP_AUTO_EXPOSURE, 0.25);
    cap.set(CV_CAP_PROP_EXPOSURE, 0.008);
    Mat image;
    int SAVEIMAGE = 0, save_num = 0;
    while(SAVEIMAGE == 1)
    {
        cap >> image;
        if(waitKey(30) == 's')
        {
            imwrite("./" + to_string(save_num) + ".png", image);
            save_num++;
            cout << "saveimage" << endl;
        }
        imshow("image", image);
    }
    RNG rng(12345);
    vector<Vec3f>circles_small;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Mat canny_img;
    float center_x_sum = 0;
    float center_y_sum = 0;
    int center_x = 0, center_y = 0;
    Mat threshold_img;
    int a_flag = 0;
    int b_flag = 0;
    int c_flag = 0;
    int d_flag = 0;
    int abc_flag = 0;
    int fa_flag = 0, fb_flag = 0, fc_flag = 0;
    int find_ac_flag = 0;
    int find_a_flag = 0;
    int target_flag = 0;
    int find_flag = 0;
    int h_flag = 0;
    int x_flag = 0, y_flag = 0;
    while(serialGetchar(fd) != 121);
    char send_data[4] = {0};
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    double k = 0.04;
    vector<vector<Point>> contours_h;
    vector<Vec4i> hierarchy_h;

    Mat threshold_img_h, gray_img_h;
    //int receive_h_flag = 0;
    int frame_num = 0;
    while(1)
    {
        cap >> image;
        //cout << image.size() << endl;
        find_a_flag = 0;
        find_flag = 0;
        abc_flag = 0;
        find_ac_flag = 0;
        center_x = 0;
        center_y = 0;
        target_flag = 0;
        circles_small.clear();
        //circles_big.clear();
        contours.clear();
        hierarchy.clear();
        //cvtColor(image, gray_img, CV_RGB2GRAY);
        //char key_board = ;
        //cout << int(key_board) << endl;
        if (h_flag)
        {
            if(h_flag == 1)
            {
                while(serialGetchar(fd) == 104);
                cout << "received h" << endl;
            }
            h_flag = 2;
            find_flag = 1;
            cvtColor(image, gray_img_h, COLOR_RGB2GRAY);
            goodFeaturesToTrack(gray_img_h, corners, 20, qualityLevel, minDistance, Mat(), blockSize, false, k);
            int r = 4;
            /*for (int i = 0; i < corners.size(); i++)
            {
                circle(image, corners[i], r, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1, 8, 0);
            }*/
            threshold(gray_img_h, threshold_img, 120, 255, THRESH_BINARY_INV);
            //imshow("threshold", threshold_img);
            findContours(threshold_img, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE);
            for (int i = 0; i < contours.size(); i++)
            {
                if (contours[i].size() < 400) continue;
                RotatedRect rect = minAreaRect(contours[i]);
                //if (rect.size.height / rect.size.width < 0.5 || rect.size.height / rect.size.width > 1.5) continue;
                Point2f vertices[4];
                rect.points(vertices);
                int rect_flag = 0;
                int point_flag = 0;
                for (int n = 0; n < corners.size(); n++)
                {
                    for (int m = 0; m < 4; m++)
                    {
                        if (fabs(vertices[m].x - corners[n].x) < 10 && fabs(vertices[m].y - corners[n].y) < 10)
                        {
                            rect_flag++;
                        }
                    }
                    if (pointPolygonTest(contours[i], corners[n], true))
                    {
                        point_flag++;
                    }
                }
                if (rect_flag > 2 && point_flag > 6 && rect.size.height*rect.size.width > 10000)
                {
                    //cout << rect.size.height*rect.size.width << endl;
                    for (int j = 0; j <= 3; j++)
                    {
                        line(image, vertices[j], vertices[(j + 1) % 4], Scalar(0, 0, 255), 1);
                    }
                    center_x = rect.center.x;
                    center_y = rect.center.y;
                    if (center_x < 20 ||  center_x > 780 || center_y < 20 || center_y > 580)
                    {
                        center_x = 0;
                        center_y = 0;
                    }
                }
                memset(send_data, 0, sizeof(send_data));
                *(signed char*)&send_data[0] = 'c';
                *(signed char*)&send_data[1] = 0;
                *(signed char*)&send_data[2] = 0;
                if (center_x != 0 || center_y != 0)
                {
                    target_flag = 1;

                    *(signed char*)&send_data[2] = target_flag;
                }
                cout << "target_flag" << target_flag  << endl;
                if (x_flag == 0)
                {
                    if (center_x > 415)
                    {
                        *(signed char*)&send_data[1] = 6;
                        //*(signed char*) &send_data[2] = 6;
                    }
                    else if (center_x < 385)
                    {
                        *(signed char*)&send_data[1] = 5;
                        //*(signed char*) &send_data[2] = 5;
                    }
                    else
                    {
                        *(signed char*)&send_data[1] = 0;
                        //*(signed char*) &send_data[2] = 0;
                        x_flag = 1;
                    }
                }
                if (x_flag == 1 && y_flag == 0)
                {
                    if (center_y > 315)
                    {
                        *(signed char*)&send_data[1] = 7;
                        //*(signed char*) &send_data[2] = 7;
                    }
                    else if (center_y < 285)
                    {
                        *(signed char*)&send_data[1] = 8;
                        //*(signed char*) &send_data[2] = 8;
                    }
                    else
                    {
                        *(signed char*)&send_data[1] = 0;
                        //*(signed char*) &send_data[2] = 0;
                        y_flag = 1;
                    }
                }
                /*int send_flag = 0;
                if(center_x == 0 || center_y == 0)
                {
                    *(signed char*)&send_data[1] = 5; //前
                    send_flag = 1;
                }
                if(send_flag == 0)
                {
                    if(center_x > x_max && center_y > y_max) *(signed char*)&send_data[1] = 11; //左后
                    else if(center_x < x_min && center_y > y_max) *(signed char*)&send_data[1] = 12; //左前
                    else if(center_x > x_min && center_x < x_max && center_y > y_max) *(signed char*)&send_data[1] = 7; //左
                    else if(center_x > x_max && center_y < y_min) *(signed char*)&send_data[1] = 13; //右后
                    else if(center_x < x_min && center_y < y_min) *(signed char*)&send_data[1] = 14; //右前
                    else if(center_x > x_min && center_x < x_max && center_y < y_min) *(signed char*)&send_data[1] = 8; //右
                    else if(center_x > x_max && center_y < y_max && center_y > y_min) *(signed char*)&send_data[1] = 6; //后
                    else if(center_x < x_min && center_y < y_max && center_y > y_min) *(signed char*)&send_data[1] = 5; //前
                    else if(center_x > x_min && center_x < x_max && center_y < y_max && center_y > y_min)
                    {
                        x_flag = 1;
                        y_flag = 1;
                        *(signed char*)&send_data[1] = 0;
                    }
                }*/
                if(x_flag && y_flag)
                {
                    *(signed char*)&send_data[1] = 'h';
                    cout << "h" << endl;
                }
                cout << "data" << int(send_data[1]) << endl;
                cout << "x = " << center_x << " y= " << center_y << endl;
                write(fd, send_data, 4);
            }
            //imshow("image", image);
            //waitKey(1);
        }
        if (find_flag == 1) continue;
        if (0)//fb_flag == 0
        {
            inRange(image, Scalar(35, 51, 113), Scalar(105, 181, 153), threshold_img);//0 58 0 152 117 36
            //inRange(image, Scalar(63, 183, 81), Scalar(117, 255, 255), threshold_img);
            //inRange(image, Scalar(4, 114, 0), Scalar(255, 201, 102), threshold_img);
            //inRange(image, Scalar(73, 194, 59), Scalar(166, 255, 205), threshold_img);
            //imshow("green_threshold", threshold_img);
            findContours(threshold_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
            for (int i = 0; i < contours.size(); i++)
            {
                if (contours[i].size() < 200) continue;
                RotatedRect rect;
                float w, h;
                rect = minAreaRect(contours[i]);
                if(rect.size.width >= rect.size.height)
                {
                    w = rect.size.width;
                    h = rect.size.height;
                }
                else if(rect.size.width < rect.size.height)
                {
                    h = rect.size.width;
                    w = rect.size.height;
                }
                if(w / h < 0.5 || w / h > 2) continue;
                Point2f center;
                float radius;
                minEnclosingCircle(contours[i], center, radius);
                if (radius < 25) continue;
                //center_x = center.x - 50;
                //center_y = center.y - 10;
                //center_x = center.x - 15; //小
                //center_y = center.y - 20; //小
                center_x = center.x - 8;
                center_y = center.y - 18;  //15偏右 绿色
                circle(image, Point2f(center_x, center_y), 5, Scalar(0, 255, 0), -1, 8);
                find_ac_flag = 1;
                b_flag = 1;
                c_flag = 0;
            }
        }
        if (1)//find_ac_flag == 0
        {
//            inRange(image, Scalar(22, 15, 113), Scalar(222, 102, 223), threshold_img);//57  24  0  151  54 76
//            //inRange(image, Scalar(44, 14, 112), Scalar(138, 87, 252), threshold_img);
//            //imshow("red_threshold", threshold_img);
//            findContours(threshold_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
//            for (int i = 0; i < contours.size(); i++)
//            {
//                if (contours[i].size() < 200) continue;
//                RotatedRect rect;
//                float w, h;
//                rect = minAreaRect(contours[i]);
//                if(rect.size.width >= rect.size.height)
//                {
//                    w = rect.size.width;
//                    h = rect.size.height;
//                }
//                else if(rect.size.width < rect.size.height)
//                {
//                    h = rect.size.width;
//                    w = rect.size.height;
//                }
//                if(w / h < 0.5 || w / h > 2) continue;
//                Point2f center;
//                float radius;
//                minEnclosingCircle(contours[i], center, radius);
//                if (radius < 15) continue;
//                //center_x = center.x - 30;
//                //center_y = center.y - 45;
//                //center_x = center.x - 40; //小
//                //center_y = center.y - 70; //小
//                center_x = center.x - 40;
//                center_y = center.y - 58; //60
//                circle(image, Point2f(center_x, center_y), 5, Scalar(255, 0, 0), -1, 8);
//                find_a_flag = 1;
//                //find_a_flag = 0;
//                c_flag = 1;
//            }
            if(1)/*find_a_flag == 0*/
            {
                cout << frame_num++ << endl;
                GaussianBlur(image, image, Size(9, 9), 2, 2);
                Canny(image, canny_img, 230, 250, 5);
                //imshow("canny", canny_img);
                HoughCircles(canny_img, circles_small, HOUGH_GRADIENT, 1, 5, 45, 100, 0, 150);
                for (size_t i = 0; i < circles_small.size(); i++)
                {
                    Point center1(cvRound(circles_small[i][0]), cvRound(circles_small[i][1]));
                    int radius1 = cvRound(circles_small[i][2]);
                    circle(image, center1, radius1, Scalar(255, 0, 255), 1, 8, 0);
                    center_x_sum = center1.x + center_x_sum;
                    center_y_sum = center1.y + center_y_sum;
                }
                if (circles_small.size() > 5 && fa_flag == 0)
                {
                    if (circles_small.size() > 0)
                    {
                        center_x = center_x_sum / circles_small.size();
                        center_y = center_y_sum / circles_small.size();
                    }
                    //center_x = center_x - 60;
                    //center_y = center_y - 3;
                    //center_x = center_x - 60; //小
                    //center_y = center_y - 25; //小
                    center_x = center_x - 28;  //A点62 30 42
                    center_y = center_y - 25;//21 51
                    center_x_sum = 0;
                    center_y_sum = 0;
                    circle(image, Point2i(center_x, center_y), 5, Scalar(0, 0, 255), -1, 8, 0);
                    a_flag = 1;
                    b_flag = 0;
                    c_flag = 0;
                }
            }
        }
        //cout << "abc_flag = "  << abc_flag << endl;
        //cout << center_x  << "  " << center_y << endl;
        /*if (center_x == 0)
        {
            center_y = 639;
        }
        if (center_y == 0)
        {
            center_y = 479;
        }*/
        circle(image, Point(400, 300), 10, Scalar(255, 0, 0), 3, 8, 0);
        //imshow("image", image);
        //waitKey(1);
        if (a_flag == 1 && b_flag == 0 && c_flag == 0)
        {
            abc_flag = 1;
        }
        else if (a_flag == 1 && b_flag == 1 && c_flag == 0)
        {
            abc_flag = 2;
        }
        else if (a_flag == 1 && b_flag == 1 && c_flag == 1)
        {
            abc_flag = 3;
        }
        //cout << abc_flag << endl;
        memset(send_data, 0, sizeof(send_data));
        *(signed char*)&send_data[0] = 'c';
        *(signed char*)&send_data[1] = 0;
        *(signed char*)&send_data[2] = 0;
        if (center_x < 20 ||  center_x > 780 || center_y < 20 || center_y > 580)
        {
            center_x = 0;
            center_y = 0;
        }
        if (center_x != 0 || center_y != 0)
        {
            target_flag = 1;
            //cout << target_flag  << endl;
            *(signed char*)&send_data[2] = target_flag;
        }
        /*if (x_flag == 0)
        {
            if (center_x > 405)
            {
                *(signed char*)&send_data[1] = 6;
                //*(signed char*) &send_data[2] = 6;
            }
            else if (center_x < 395)
            {
                *(signed char*)&send_data[1] = 5;
                //*(signed char*) &send_data[2] = 5;
            }
            else
            {
                *(signed char*)&send_data[1] = 0;
                //*(signed char*) &send_data[2] = 0;
                x_flag = 1;
            }
        }
        if (x_flag == 1 && y_flag == 0)
        {
            if (center_y > 305)
            {
                *(signed char*)&send_data[1] = 7;
                //*(signed char*) &send_data[2] = 7;
            }
            else if (center_y < 295)
            {
                *(signed char*)&send_data[1] = 8;
                //*(signed char*) &send_data[2] = 8;
            }
            else
            {
                *(signed char*)&send_data[1] = 0;
                //*(signed char*) &send_data[2] = 0;
                y_flag = 1;
                x_flag = 0;
            }
        }*/
        int send_flag = 0;
        if(center_x == 0 || center_y == 0)
        {
            *(signed char*)&send_data[1] = 5; //前
            send_flag = 1;
        }
        if(send_flag == 0)
        {
            if(center_x > x_max && center_y > y_max) *(signed char*)&send_data[1] = 11; //左后
            else if(center_x < x_min && center_y > y_max) *(signed char*)&send_data[1] = 12; //左前
            else if(center_x > x_min && center_x < x_max && center_y > y_max) *(signed char*)&send_data[1] = 7; //左
            else if(center_x > x_max && center_y < y_min) *(signed char*)&send_data[1] = 13; //右后
            else if(center_x < x_min && center_y < y_min) *(signed char*)&send_data[1] = 14; //右前
            else if(center_x > x_min && center_x < x_max && center_y < y_min) *(signed char*)&send_data[1] = 8; //右
            else if(center_x > x_max && center_y < y_max && center_y > y_min) *(signed char*)&send_data[1] = 6; //后
            else if(center_x < x_min && center_y < y_max && center_y > y_min) *(signed char*)&send_data[1] = 5; //前
            else if(center_x > x_min && center_x < x_max && center_y < y_max && center_y > y_min)
            {
                x_flag = 1;
                y_flag = 1;
                *(signed char*)&send_data[1] = 0;
            }
        }
        if (x_flag == 1 && y_flag == 1 && abc_flag == 0)
        {
            *(signed char*)&send_data[1] = 'd';
            //*(signed char*) &send_data[2] = 'd';
            d_flag = 1;
            x_flag = 0;
            y_flag = 0;
            fa_flag = 0;
            fb_flag = 0;
            fc_flag = 1;
        }
        else if (x_flag == 1 && y_flag == 1 && abc_flag == 1)
        {
            *(signed char*)&send_data[1] = 'a';
            //*(signed char*) &send_data[2] = 'a';
            d_flag = 1;
            //h_flag = 1;
            x_flag = 0;
            y_flag = 0;
            cout << "a" << endl;
            fa_flag = 1;
            fb_flag = 0;
            fc_flag = 0;
        }
        else if (x_flag == 1 && y_flag == 1 && abc_flag == 2)
        {
            *(signed char*)&send_data[1] = 'b';
            //*(signed char*) &send_data[2] = 'b';
            d_flag = 1;
            x_flag = 0;
            y_flag = 0;
            cout << "b" << endl;
            fa_flag = 0;
            fb_flag = 1;
            fc_flag = 0;
        }
        else if (x_flag == 1 && y_flag == 1 && abc_flag == 3)
        {
            *(signed char*)&send_data[1] = 'c';
            //*(signed char*) &send_data[2] = 'c';
            //d_flag = 1;
            h_flag = 1;
            x_flag = 0;
            y_flag = 0;
            cout << "c" << endl;
            fa_flag = 0;
            fb_flag = 0;
            fc_flag = 1;
        }
        cout << "data" << int(send_data[1]) << endl;
        cout << "x = " << center_x << " y= " << center_y << endl;
        write(fd, send_data, 4);
        if (d_flag == 1)
        {
            //int key_board = serialGetchar(fd);
            //cout << key_board << endl;
            while (serialGetchar(fd) != 121);
            //if(waitKey(0) == 's') NULL;
            d_flag = 0;
        }
    }
}
