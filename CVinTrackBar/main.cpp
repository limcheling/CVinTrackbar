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
const char* trackbar_background = "Background: ";
const int max_brightness = 100;
const int max_contrast = 100;
const int max_alphaSlider = 100;
int brightness_value = 50;
int contrast_value = 50;
int alphaSlider = 0; //0: only foreground 1: only background

cv::String windowname;
cv::Mat src, bg, src_dst, bg_dst, dst;

void demo_contrast(int, void*);
void demo_brightness(int, void*);
void demo_backgrond(int, void*);

double alpha = 1, beta = 0;
double dContrast;
int iBrightness;

int main(int argc, const char * argv[]) {
    
    if (argc == 3)
    {
        windowname = argv[1];
    }
    else
    {
        std::cout << "Error: This program expects 2 arguments but only " << argc << " is provided!\n";
        exit(-1);
    }
    
    src = cv::imread(windowname, cv::IMREAD_COLOR);
    bg = cv::imread(argv[2], cv::IMREAD_COLOR); //Read in background picture
    //cv::imshow("src", src);
    //cv::imshow("bg", bg);
    cv::resize(bg, bg, src.size(), 0, 0, cv::INTER_LINEAR);
    
    std::cout << "Src depth: " << src.depth() << " channels: " << src.channels() <<  " type: " << src.type() << " size: "
                << src.size() << " \n";
    std::cout << "Bg depth: " << bg.depth() << " channels: " << bg.channels() <<  " type: " << bg.type() << " size: "
                << bg.size() << "\n";
    if (src.empty())
    {
        std::cout << "Failed to read file!\n";
        exit(-1);
    }
    
    cv::namedWindow(windowname);
    
    cv::createTrackbar(trackbar_brightness, windowname, &brightness_value, max_brightness, demo_brightness);
    //demo(brightness_value, 0);
    cv::createTrackbar(trackbar_contrast, windowname, &contrast_value, max_contrast, demo_contrast);
    //demo(contrast_value, 0);

    cv::createTrackbar(trackbar_background, windowname, &alphaSlider, max_alphaSlider, demo_backgrond);
    
    cv::imshow(windowname, src);
    cv::waitKey();
    
    return 0;
}

void adjustImage(){

    src.convertTo(src_dst, -1, dContrast, iBrightness);
    //cv::imshow("src_dst", src_dst);
    bg.convertTo(bg_dst, -1, dContrast, iBrightness);
    //cv::imshow("bg_dst", bg_dst);
    cv::addWeighted(src_dst, alpha, bg_dst, beta, 0.0, dst);
    cv::imshow(windowname, dst);
}

void demo_brightness(int, void*){
    iBrightness = brightness_value - max_brightness/2 ;
    adjustImage();
}

void demo_contrast(int, void*){
    dContrast = static_cast<double>(contrast_value) * 2 / max_contrast;
    adjustImage();
}

//blend two images
void demo_backgrond(int, void*){
    beta = static_cast<double>(alphaSlider) / max_alphaSlider;
    alpha = 1 - beta;
    adjustImage();
}



