#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat img1 = imread(argv[1], IMREAD_GRAYSCALE); // requestedImage
    Mat img2 = imread(argv[2], IMREAD_GRAYSCALE); // trainImage

    if (argc < 3)
    {
        printf(" Please provide path images as command line arguments! \n");
        return -1;
    }

    /*Mat smooth_img1, smooth_img2;
    GaussianBlur(img1, smooth_img1, Size(3, 3), 0);
    GaussianBlur(img2, smooth_img2, Size(3, 3), 0);

    namedWindow("smooth1", WINDOW_KEEPRATIO);
    imshow("smooth1", smooth_img1);

    namedWindow("smooth2", WINDOW_KEEPRATIO);
    imshow("smooth2", smooth_img2);*/

    // Initiate ORB detector
    //Ptr<ORB> orb = ORB::create();

    // Initiate SIFT detector
    Ptr<xfeatures2d::SURF> surf = xfeatures2d::SURF::create();

    // Find the keypoints and descriptors with ORB
    vector<KeyPoint> kp1, kp2;
    Mat des1, des2;
    surf->detectAndCompute(img1, Mat(), kp1, des1);
    surf->detectAndCompute(img2, Mat(), kp2, des2);

    // create BFMatcher object
    BFMatcher bf(NORM_L1, true);

    // FLANN parameters
    /*Ptr<flann::IndexParams> indexParams = makePtr<flann::KDTreeIndexParams>(5);
    Ptr<flann::SearchParams> searchParams = makePtr<flann::SearchParams>(50);
    FlannBasedMatcher flannMatcher(indexParams, searchParams);*/
    
    /*vector<vector<DMatch>> matches;
    flannMatcher.knnMatch(des1, des2, matches, 2);*/
    
    
    // Match descriptors
    vector<DMatch> matches;
    bf.match(des1, des2, matches);
    
    // Need to draw only good matches, so create a mask
    /*vector<DMatch> goodMatches;
    for (size_t i = 0; i < matches.size(); ++i)
    {
        if (matches[i][0].distance < 0.7 * matches[i][1].distance)
        {
            goodMatches.push_back(matches[i][0]);
        }
    }*/


    // Calculate the average distance of the matches
    /*double avgDistance = 0.0;
    for (DMatch& match : matches)
    {
        avgDistance += match.distance;
    }
    avgDistance /= matches.size();*/
    
    // Set a threshold to determine if the images have the same content
    //double distanceThreshold = 0.6;  // Adjust this value as needed

    /*if(avgDistance < distanceThreshold) print("\nThe two images have the same content");
    else print("\nThe two images don't have the same content");*/

    // Sort them in the order of their distance
    /*sort(matches.begin(), matches.end(), [](const DMatch& a, const DMatch& b) {
        return a.distance < b.distance;
    });*/

    // Draw matches
    Mat img3;
    drawMatches(img1, kp1, img2, kp2, matches, img3, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::DEFAULT);
    
    namedWindow("Matches", WINDOW_KEEPRATIO);
    imshow("Matches", img3);

    

    waitKey(0);

    return 0;
}