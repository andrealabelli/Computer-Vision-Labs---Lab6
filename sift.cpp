#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat img1 = imread("C:/Users/andre/OneDrive/Desktop/Computer_Vision/Lab_6/dish1.jpg", IMREAD_GRAYSCALE); // requestedImage
    Mat img2 = imread("C:/Users/andre/OneDrive/Desktop/Computer_Vision/Lab_6/dish3.jpg", IMREAD_GRAYSCALE); // trainImage

    /*if (argc < 3)
    {
        printf(" Please provide path images as command line arguments! \n");
        return -1;
    }*/

    Ptr<SIFT> sift = SIFT::create();
    
            vector<KeyPoint> keypoints1, keypoints2;
            Mat descriptors1, descriptors2;
    
            sift->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
            sift->detectAndCompute(img2, noArray(), keypoints2, descriptors2);

            descriptors1.convertTo(descriptors1, CV_8U);
            descriptors2.convertTo(descriptors2, CV_8U);
    
            BFMatcher matcher(NORM_HAMMING, true);
    
            vector<DMatch> matches;
            matcher.match(descriptors1, descriptors2, matches);

            // Need to draw only good matches, so create a mask
            vector<DMatch> goodMatches;
            for (int i = 0; i < matches.size(); ++i)
            {
                if (matches[i].distance < 2 * matches[i].distance)
                {
                    goodMatches.push_back(matches[i]);
                }
            }

            double avgDistance = goodMatches.size() / (double)matches.size();

            if(avgDistance > 0.7) printf("\nThe images have the same content\n\nScore: %.2f", avgDistance);
            else if (avgDistance < 0.7 && avgDistance > 0.3) printf("\nThe images have similar content processed by some strong transformation\n\nScore: %.2f", avgDistance);
            else printf("\nThe images don't have similar content\n\nScore: %.2f", avgDistance);

            sort(matches.begin(), matches.end(), [](const DMatch& a, const DMatch& b) {
                return a.distance < b.distance;
            });
    
            Mat img4;
            drawMatches(img1, keypoints1, img2, keypoints2, goodMatches, img4, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

            namedWindow("Matches", WINDOW_KEEPRATIO);
    
            imshow("Matches", img4);
            waitKey(0);


    /*Ptr<xfeatures2d::SURF> surf = xfeatures2d::SURF::create();
    
            vector<KeyPoint> keypoints1, keypoints2;
            Mat descriptors1, descriptors2;
    
            surf->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
            surf->detectAndCompute(img2, noArray(), keypoints2, descriptors2);

            descriptors1.convertTo(descriptors1, CV_8U);
            descriptors2.convertTo(descriptors2, CV_8U);
    
            BFMatcher matcher(NORM_HAMMING, true);
    
            vector<DMatch> matches;
            matcher.match(descriptors1, descriptors2, matches);

            // Need to draw only good matches, so create a mask
            /*vector<DMatch> goodMatches;
            for (int i = 0; i < matches.size(); ++i)
            {
                if (matches[i].distance < 2 * matches[i].distance)
                {
                    goodMatches.push_back(matches[i]);
                }
            }

            double avgDistance = goodMatches.size() / (double)matches.size();

            if(avgDistance > 0.7) printf("\nThe images have the same content\n\nScore: %.2f", avgDistance);
            else if (avgDistance < 0.7 && avgDistance > 0.3) printf("\nThe images have similar content processed by some strong transformation\n\nScore: %.2f", avgDistance);
            else printf("\nThe images don't have similar content\n\nScore: %.2f", avgDistance);*/

            /*sort(matches.begin(), matches.end(), [](const DMatch& a, const DMatch& b) {
                return a.distance < b.distance;
            });
    
            Mat img5;
            drawMatches(img1, keypoints1, img2, keypoints2, matches, img5, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::DEFAULT);
    
            imshow("Matches with SURF detector for keypoints", img5);
            waitKey(0);*/

            /*Ptr<ORB> orb = ORB::create();
    
            vector<KeyPoint> keypoints1, keypoints2;
            Mat descriptors1, descriptors2;
    
            orb->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
            orb->detectAndCompute(img2, noArray(), keypoints2, descriptors2);
    
            BFMatcher matcher(NORM_HAMMING, true);
    
            vector<DMatch> matches;
            matcher.match(descriptors1, descriptors2, matches);

            // Need to draw only good matches, so create a mask
           /* vector<DMatch> goodMatches;
            for (int j = 0; j < matches.size(); j++)
            {
                if (matches[j].distance < 2 * matches[j].distance)
                {
                    goodMatches.push_back(matches[j]);
                }
            }   

            double avgDistance = goodMatches.size() / (double)matches.size();

            if(avgDistance > 0.7) printf("\nThe images have the same content\n\nScore: %.2f", avgDistance);
            else if (avgDistance < 0.7 && avgDistance > 0.3) printf("\nThe images have similar content processed by some strong transformation\n\nScore: %.2f", avgDistance);
            else printf("\nThe images don't have similar content\n\nScore: %.2f", avgDistance);*/

            /*sort(matches.begin(), matches.end(), [](const DMatch& a, const DMatch& b) {
                return a.distance < b.distance;
            });
    
            Mat img3;
            drawMatches(img1, keypoints1, img2, keypoints2, matches, img3, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    
            imshow("Matches with ORB detector for keypoints", img3);
            waitKey(0);*/


    
    /*for (int i = 0; i < 3; i++)
    {
        /*if(i==0)
        {
            Ptr<ORB> orb = ORB::create();
    
            vector<KeyPoint> keypoints1, keypoints2;
            Mat descriptors1, descriptors2;
    
            orb->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
            orb->detectAndCompute(img2, noArray(), keypoints2, descriptors2);
    
            BFMatcher matcher(NORM_HAMMING, true);
    
            vector<DMatch> matches;
            matcher.match(descriptors1, descriptors2, matches);

            // Need to draw only good matches, so create a mask
            vector<DMatch> goodMatches;
            for (int j = 0; j < matches.size(); j++)
            {
                if (matches[j].distance < 2 * matches[j].distance)
                {
                    goodMatches.push_back(matches[j]);
                }
            }   

            double avgDistance = goodMatches.size() / (double)matches.size();

            if(avgDistance > 0.7) printf("\nThe images have the same content\n\nScore: %.2f", avgDistance);
            else if (avgDistance < 0.7 && avgDistance > 0.3) printf("\nThe images have similar content processed by some strong transformation\n\nScore: %.2f", avgDistance);
            else printf("\nThe images don't have similar content\n\nScore: %.2f", avgDistance);

            /*sort(matches.begin(), matches.end(), [](const DMatch& a, const DMatch& b) {
                return a.distance < b.distance;
            });
    
            Mat img3;
            drawMatches(img1, keypoints1, img2, keypoints2, matches, img3, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    
            imshow("Matches with ORB detector for keypoints", img3);*/
    
         /*if(i==1){
            
            Ptr<SIFT> sift = SIFT::create();
    
            vector<KeyPoint> keypoints1, keypoints2;
            Mat descriptors1, descriptors2;
    
            sift->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
            sift->detectAndCompute(img2, noArray(), keypoints2, descriptors2);
    
            BFMatcher matcher(NORM_HAMMING, true);
    
            vector<DMatch> matches;
            matcher.match(descriptors1, descriptors2, matches);

            // Need to draw only good matches, so create a mask
            vector<DMatch> goodMatches;
            for (int i = 0; i < matches.size(); ++i)
            {
                if (matches[i].distance < 2 * matches[i].distance)
                {
                    goodMatches.push_back(matches[i]);
                }
            }

            double avgDistance = goodMatches.size() / (double)matches.size();

            if(avgDistance > 0.7) printf("\nThe images have the same content\n\nScore: %.2f", avgDistance);
            else if (avgDistance < 0.7 && avgDistance > 0.3) printf("\nThe images have similar content processed by some strong transformation\n\nScore: %.2f", avgDistance);
            else printf("\nThe images don't have similar content\n\nScore: %.2f", avgDistance);

            /*sort(matches.begin(), matches.end(), [](const DMatch& a, const DMatch& b) {
                return a.distance < b.distance;
            });
    
            Mat img4;
            drawMatches(img1, keypoints1, img2, keypoints2, matches, img4, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    
            imshow("Matches with SIFT detector for keypoints", img4);*/
            
        /*if(i==2){

            Ptr<xfeatures2d::SURF> surf = xfeatures2d::SURF::create();
    
            vector<KeyPoint> keypoints1, keypoints2;
            Mat descriptors1, descriptors2;
    
            surf->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
            surf->detectAndCompute(img2, noArray(), keypoints2, descriptors2);
    
            BFMatcher matcher(NORM_HAMMING, true);
    
            vector<DMatch> matches;
            matcher.match(descriptors1, descriptors2, matches);

            // Need to draw only good matches, so create a mask
            vector<DMatch> goodMatches;
            for (int i = 0; i < matches.size(); ++i)
            {
                if (matches[i].distance < 2 * matches[i].distance)
                {
                    goodMatches.push_back(matches[i]);
                }
            }

            double avgDistance = goodMatches.size() / (double)matches.size();

            if(avgDistance > 0.7) printf("\nThe images have the same content\n\nScore: %.2f", avgDistance);
            else if (avgDistance < 0.7 && avgDistance > 0.3) printf("\nThe images have similar content processed by some strong transformation\n\nScore: %.2f", avgDistance);
            else printf("\nThe images don't have similar content\n\nScore: %.2f", avgDistance);

            /*sort(matches.begin(), matches.end(), [](const DMatch& a, const DMatch& b) {
                return a.distance < b.distance;
            });
    
            Mat img5;
            drawMatches(img1, keypoints1, img2, keypoints2, matches, img5, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    
            imshow("Matches with SURF detector for keypoints", img5);
            waitKey(0);
        }*/

        return 0;
    }
