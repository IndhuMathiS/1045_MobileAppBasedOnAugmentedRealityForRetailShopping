#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>
using namespace cv;
using namespace std;

CvFont font; 
CvSeq* face;
IplImage* hsv;
Point2f p[4],q[4];
IplImage* img=NULL;
int found, scale = 1;
cv::Point2f v[4],b[4];
unsigned int j=0, i=0;
int line_type = CV_AA; // change it to 8 to see non-antialiased graphics 
static CvMemStorage* storage = 0;
CvPoint pt1, pt2,pt3,pt4,pt5,pt6,pt7;
const int boardWidth=5, boardHeight=4;
Mat overlay, perspMat, pic,frame, templ;
static CvHaarClassifierCascade* cascade = 0;
const Size boardSize = Size(boardWidth,boardHeight);
const char *cascade_name="haarcascade_frontalface_alt.xml"; //semi-plam
 CvSize size;
/************************************************************************************/
void merge(cv::Mat &in1, cv::Mat &in2,cv::Mat &out)
{
    int nLines = in1.rows;
    int nc = in1.cols * in1.channels();
    if(in1.isContinuous())
    {
        nc = nc*nLines;
        nLines = 1;
    }
    for(int j=0;j<nLines;j++)
    {
        uchar* dataIN1 = in1.ptr<uchar>(j); //fajne :)
        uchar* dataIN2 = in2.ptr<uchar>(j);
        uchar* dataOUT = out.ptr<uchar>(j);
        for(int i=0;i<nc; i++)
        {
            if(dataIN2[i] == 0)
            {
                dataOUT[i] = dataIN1[i];
            }
            else
            {
                dataOUT[i] = dataIN2[i];
            }

        }
    }
}

/************************************************************************************/
int main()
{

    int b=1,x=0,y=0,c=0,c1=0,a=0,w=0,N=0,L=0;
//  CvCapture* capture = cvCaptureFromCAM( 0 );
      
     CvCapture* capture = cvCreateFileCapture("rtsp://10.0.0.90:8086");
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
   cvSetCaptureProperty(capture, CV_CAP_PROP_FPS, 10);
 CvSize size = cvSize(
                     (int)cvGetCaptureProperty( capture,
                                               CV_CAP_PROP_FRAME_WIDTH),
                     (int)cvGetCaptureProperty( capture,
                                               CV_CAP_PROP_FRAME_HEIGHT)
                     );
 CvVideoWriter *writer = cvCreateVideoWriter("out.mjpg",CV_FOURCC('M','J','P','G'),10,size);
    vector<Point> corners;
    Point2f p[4],q[4];
    overlay = Mat::zeros(319,239,CV_8UC3);
    storage = cvCreateMemStorage(0);
    cvClearMemStorage( storage );
    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    pic = cv::imread("N1.png");
          //  flip(pic,pic,0);
          //  flip(pic,pic,1);
    while(1)
    {
	c=c1=0;
        img = cvQueryFrame( capture );
	if ( !img )
	  {
	    printf("Connect Camera.....\n");
	    break;
	  }
        if ( L == 3 )
        { 
          for( y=0; y<10; y++ )
           {
	     L=0;
             img = cvQueryFrame( capture );
      	    // cvShowImage( "Frame", img );
             cvWaitKey(33); 
	   }
	}
	Mat src(img);
        if(!img)break;
        face = cvHaarDetectObjects( img, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40));

           for( i = 0; i < (face ? face->total : 0); i++ )
              {
               CvRect* r = (CvRect*)cvGetSeqElem( face, i );
               found =10;
               pt1.x = r->x*scale+50 ;
               pt2.x = (r->x+r->width)*scale+50;
               pt1.y = r->y*scale ;
               pt2.y = (r->y+r->height)*scale  ;
               //cvRectangle( img, pt1, pt2, CV_RGB(0,0,0), 3, 8, 0 );
             }

/************************************Next************************************/
	pt7.x=20;pt7.y=10;
	cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 0.3,0.3 );  
	cvPutText( img, "Next", pt7, &font, CV_RGB(255,255,0)); 
        cvRectangle( img, cvPoint(0,0),cvPoint(65,20), CV_RGB(0,255,0), 2, 8, 0 );
/************************************prev************************************/
	pt7.x=280;pt7.y=14;
        cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 0.4,0.4 );  
        cvPutText( img, "Prev", pt7, &font, CV_RGB(255,255,0));
        cvRectangle( img, cvPoint(270,0),cvPoint(320,20), CV_RGB(0,255,0), 2, 8, 0 );
	pt7.x=96;pt7.y=14;
        cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 0.4,0.4 );  
        cvPutText( img, "Augment Reality", pt7, &font, CV_RGB(255,255,0));
	pt3.x=65;pt3.y=20;pt4.x=270;pt4.y=20;//hori
	cvLine( img, pt3, pt4, CV_RGB(0,255,255), 2, 8, 0 );//bottom-hor

        Mat hsv;
        cvtColor(src, hsv, CV_BGR2HSV);
        Mat bw;
        inRange(hsv, Scalar(0, 50, 170, 0), Scalar(10, 180, 256, 0), bw);//red
        vector<vector<Point> > contours;
        findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        Mat dst = Mat::zeros(src.size(), src.type());
	Mat dst1 = Mat::zeros(src.size(), src.type());
        drawContours(dst, contours, -1, Scalar::all(255), CV_FILLED);
unsigned int v1=0,v2=0,v3=0,v4=0,v5=0,v6=0,v7=0,v8=0;	
        if ( found > 5 )
        { 
         for(  y = 8; y < 13; y++ )
           {
            for(  x = 8; x < 55; x++ )
              {
                a=saturate_cast<uchar>(( dst.at<Vec3b>(y,x)[0] ));
   	        if ( (a > 230 ) )
		  {
                    c =c+1;
	            c1 =0;
                  }
	       }
	    }

        for(  y = 8; y < 13; y++ )
          {
           for(  x = 275; x < 317; x++ )
             {
               w=saturate_cast<uchar>(( dst.at<Vec3b>(y,x)[0] ));
   	       if ( (w > 230 ) )
		{
                  c1 = c1 + 1;
		  c = 0;	  
                }
	     }
	  }
prev:
        if( ( c > 7 ) && ( b == 0 ) )
          {
            pic = cv::imread("N2.png");
   flip(pic,pic,0);
          flip(pic,pic,1);
            b=b+1;c=0;L=3;
	    goto Next;
          }
        if( ( c > 7 ) && ( b == 1 ) )
          {
            pic = cv::imread("N3.png");
            flip(pic,pic,0);
            flip(pic,pic,1);
	    if (N==9){N=0;L=3;c=0;goto Next;}
            b=b+1;c=0;L=3;
	    goto Next;
          }

        if( ( c > 7 ) && ( b == 2 ) )
          {
            pic = cv::imread("N4.png");
            flip(pic,pic,0);
            flip(pic,pic,1);
	    if (N==9){N=0;L=3;b=b-1;goto Next;}
            c=0;L=3;
	    goto Next;
          }
           
        if( ( c1 > 7 ) )
          {
            b=b-1;
	    c1=0;
            //printf("Prev.............\n");
	    c=10;
	    N=9;
	    goto prev;
          }
Next:
            found=0;
            frame=img;
            ///printf("argument...........\n");
            q[0].x= 0;
            q[0].y= 0;
            q[1].x= 150;
            q[1].y= 0;
            q[2].x= 150;
            q[2].y= 180;
            q[3].x= 0;     //center
            q[3].y= 180;
	v1=pt1.y,v2=pt1.x,v3=pt2.y,v4=pt1.x,v5=pt2.y,v6=pt2.x,v7=pt1.y,v8=pt2.x;
            for(i=0;i<corners.size();i++)//find the size of contour
   	       {
   	 	 cout << "# of corners points: " << corners.size() << endl ;
	       }

            p[0].x= v1;// pt1.x;
            p[0].y= v2;//pt1.y;
            p[1].x= v3;//pt2.x;
            p[1].y= v4;//pt1.y;

            p[2].x= v5;//pt2.x;
            p[2].y= v6;//pt2.y;
            p[3].x= v7;//pt1.x;
            p[3].y= v8;//pt2.y;

            perspMat = getPerspectiveTransform(q,p);
            warpPerspective(pic,overlay,perspMat,Size(frame.cols,frame.rows));
            merge(frame,overlay,frame);
        imshow("Frame",frame);
            
        }
//for ( j=0; j<=100;j++)
//{

 //cvWriteFrame(writer,img);


//}

        //     cvWriteFrame(writer,img); //change 14-11-2014
 // cvSaveImage("out.jpg", img);       
cvWriteFrame(writer, img);
 
      cvWaitKey( 33); 
    }


cvReleaseCapture( &capture );
//cvReleaseVideoWriter( &writer );
//cvReleaseVideoWriter( &writer );
    return 0;
}
