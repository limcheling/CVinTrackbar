//
//  main.cpp
//  CVinTrackBar
//
//  Created by Cheling Lim on 12/2/18.
//  Copyright © 2018 Cheling Lim. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


const char* trackbar_brightness = "Brightness: ";
const char* trackbar_contrast = "Contrast: ";
const int max_brightness = 100;
const int max_contrast = 100;
int brightness_value = 50;
int contrast_value = 50;
cv::String windowname;
cv::Mat src, dst;

void demo_contrast(int, void*);
void demo_brightness(int, void*);

int main(int argc, const char * argv[]) {
    
    if (argc > 1)
    {
        windowname = argv[1];
    }
    
    src = cv::imread(windowname, cv::IMREAD_COLOR);
    
    std::cout << "depth: " << src.depth() << " channels: " << src.channels() <<  " type: " << src.type() << "\n";
    if (src.empty())
    {
        std::cout << "Failed to read file!\n";
        exit(-1);
    }
    
    cv::namedWindow(windowname);
    
    cv::createTrackbar(trackbar_brightness, windowname, &brightness_value, max_brightness, demo_brightness, &contrast_value);
    //demo(brightness_value, 0);
    cv::createTrackbar(trackbar_contrast, windowname, &contrast_value, max_contrast, demo_contrast, &brightness_value);
    //demo(contrast_value, 0);

    
    cv::imshow(windowname, src);
    cv::waitKey();
    
    return 0;
}

void demo_brightness(int iValueBrightness, void* userData){
    int iBrightness = iValueBrightness - max_brightness/2 ;
    //double contrast = static_cast<double>((*static_cast<int*>(userData))) * 2 / max_contrast;
    double contrast = static_cast<double>(contrast_value) * 2 / max_contrast;
    
    src.convertTo(dst, -1, contrast, iBrightness);
    cv::imshow(windowname, dst);
}

void demo_contrast(int iValueContrast, void* userData){
    double contrast = static_cast<double>(iValueContrast) * 2 / max_contrast;
    //int iBrightness = (*static_cast<int*>(userData)) - max_brightness/2 ;
    int iBrightness = brightness_value - max_brightness/2 ;
    
    src.convertTo(dst, -1, contrast, iBrightness);
    cv::imshow(windowname, dst);
    
}


