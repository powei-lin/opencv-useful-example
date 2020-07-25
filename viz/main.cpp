#include <opencv2/viz.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    viz::Viz3d myWindow("Coordinate Frame");
    Mat rvec = (Mat_<float>(3,1) << -(float)CV_PI/6, 0, 0);
    Mat rmat;
    Rodrigues(rvec, rmat);
    Affine3f posess(rmat, Vec3f(0, -3, -5)), posess2(Vec3f(0,0,0), Vec3f(0, -1, -3));
    // cout << myWindow.getViewerPose().rvec() << endl;
    myWindow.setViewerPose(posess);
    myWindow.showWidget("Coordinate Widget", viz::WCoordinateSystem());
    // viz::WLine axis(Point3f(-1.0f,-1.0f,-1.0f), Point3f(1.0f,1.0f,1.0f));
    viz::WCameraPosition wcam(Vec2d(1,1), 1.0, viz::Color::green());
    // axis.setRenderingProperty(viz::LINE_WIDTH, 4.0);
    
    myWindow.showWidget("cam", wcam);
    myWindow.setWidgetPose("cam", posess2);


    viz::WCube cube_widget(Point3f(0.5,0.5,0.0), Point3f(0.0,0.0,-0.5), true, viz::Color::blue());
    cube_widget.setRenderingProperty(viz::LINE_WIDTH, 4.0);
    myWindow.showWidget("Cube Widget", cube_widget);
    Mat rot_vec = Mat::zeros(1,3,CV_32F);
    float translation_phase = 0.0, translation = 0.0;
    while(!myWindow.wasStopped())
    {
        /* Rotation using rodrigues */
        rot_vec.at<float>(0,0) += (float)CV_PI * 0.01f;
        rot_vec.at<float>(0,1) += (float)CV_PI * 0.01f;
        rot_vec.at<float>(0,2) += (float)CV_PI * 0.01f;
        translation_phase += (float)CV_PI * 0.01f;
        translation = sin(translation_phase);
        Mat rot_mat;
        Rodrigues(rot_vec, rot_mat);
        Affine3f pose(rot_mat, Vec3f(translation, translation, translation));
        myWindow.setWidgetPose("Cube Widget", pose);
        myWindow.spinOnce(1, false);
        
        // cout << myWindow.getViewerPose().rvec() << endl;
        cout << myWindow.getViewerPose().translation() << endl;
    }
    return 0;
}