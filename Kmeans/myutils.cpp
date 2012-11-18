/**
 * @file myutils.cpp
 * @brief utility functions for OpenCV
 *
 * @author Tatsuya Harada
 * @date Nov. 5, 2011
 */
#include "myutils.h"

/**
 * @brief load the float (double) matrix from file
 * 
 * @param fname pointer of file name
 * @return loaded matrix
 */
Mat LoadMat (char *fname){
  FILE *fp;
  char buf[1024];
  int nd; //< the number of data
  int ndim; //< the number of dimensions
  char *token = (char *)" ";
  char *seek;
  double *heap;
  int count;
  int i,j;

  if((fp=fopen(fname,"r"))==NULL){
    printf("file open error.\n");
    exit(EXIT_FAILURE);
  }
  
  nd=0;
  count=0;
  heap = (double *)malloc(sizeof(double));

  while(fgets(buf,sizeof(buf),fp)!=NULL){
    if ( (seek = strtok(buf,token)) != NULL ){
      ndim=0;
      do {
	heap = (double *)realloc(heap,sizeof(double)*(count+1));
	*(heap+count) = atof(seek);
	ndim++;
	count++;
      } while ( (seek = strtok(NULL,token)) != NULL );
    }
    nd++;
  }

  fclose(fp);

  Mat mat=Mat::zeros(nd,ndim,CV_32FC1);

  count=0;
  for(i=0;i<nd;i++){
    for(j=0;j<ndim;j++){
      mat.at<float>(i,j)=*(heap+count);
      count++;
    }
  }

  free(heap);
  
  return mat;
}

/**
 * @brief load the integer matrix from file
 * 
 * @param fname pointer of file name
 * @return loaded matrix
 */
Mat LoadMat_i (char *fname){
  FILE *fp;
  char buf[1024];
  int nd; //< the number of data
  int ndim; //< the number of dimensions
  char *token = (char *)" ";
  char *seek;
  int *heap;
  int count;
  int i,j;

  if((fp=fopen(fname,"r"))==NULL){
    printf("file open error.\n");
    exit(EXIT_FAILURE);
  }
  
  nd=0;
  count=0;
  heap = (int *)malloc(sizeof(int));

  while(fgets(buf,sizeof(buf),fp)!=NULL){
    if ( (seek = strtok(buf,token)) != NULL ){
      ndim=0;
      do {
	heap = (int *)realloc(heap,sizeof(int)*(count+1));
	*(heap+count) = atoi(seek);
	ndim++;
	count++;
      } while ( (seek = strtok(NULL,token)) != NULL );
    }
    nd++;
  }

  fclose(fp);

  Mat mat=Mat::zeros(nd,ndim,CV_32SC1);

  count=0;
  for(i=0;i<nd;i++){
    for(j=0;j<ndim;j++){
      mat.at<int>(i,j)=*(heap+count);
      count++;
    }
  }

  free(heap);
  
  return mat;
}


/**
 * @brief plot 2D data with gnuplot
 * 
 * @param mat cv::Mat pointer of 2D data
 * @param idxmat index of mat
 * @param nc the number of categories
 */
void plotclusters2D(Mat& mat, Mat& idxmat, int nc)
{
  // plot data with gnuplot
  Mat maxmat=Mat::zeros(1,2,CV_32FC1);
  Mat minmat=Mat::zeros(1,2,CV_32FC1);

  cv::reduce(mat,maxmat,0,CV_REDUCE_MAX);
  cv::reduce(mat,minmat,0,CV_REDUCE_MIN);

  FILE *gp;
  gp = popen("gnuplot -persist","w");
  fprintf(gp, "set multiplot\n"); // multiplot mode on
  fprintf(gp, "set xrange [%lf : %lf]\n",minmat.at<float>(0,0),maxmat.at<float>(0,0));
  fprintf(gp, "set yrange [%lf : %lf]\n",minmat.at<float>(0,1),maxmat.at<float>(0,1));

  // plot all data
  int c,i;
  for(c=0;c<nc;c++){
    fprintf(gp, "plot '-' linetype %d pointtype %d\n",c+1 ,c+1);
    for(i=0; i<mat.rows; i++){
      if(idxmat.at<int>(0,i)==c){
	fprintf(gp,"%lf\t%lf\n", mat.at<float>(i,0), mat.at<float>(i,1));
      }
    }
    fprintf(gp,"e\n");
  }
  
  fprintf(gp, "set nomultiplot\n"); // multiplot mode off
  pclose(gp);
}


