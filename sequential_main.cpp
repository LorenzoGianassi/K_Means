#include <iostream>
#include <chrono>
#include <cmath>
#include <omp.h>
#include "Point.h"
#include "Cluster.h"
#include "fstream"
using namespace std;

int num_pt = 500000;
int  num_cl = 20;
int iterations = 20;
double max_value = 100000;

vector<Point> create_point(int num_pt);
vector<Cluster> create_cluster(int num_cl);
void find_distance(vector<Point> &pts, vector<Cluster> &cls);
double euclidean_dist(Point pt, Cluster cl);
bool update_clusters(vector<Cluster> &cls);
void plot(vector<Point> &points);


int main() {

    srand(time(NULL));
    printf("Number of Points %d\n",num_pt);
    printf("Number of Clusters %d\n",num_cl);

    double start_time = omp_get_wtime();
    printf("Initialization \n");

    printf("Creation of the Points \n");
    vector<Point> pts = create_point(num_pt);
    printf("Points Created \n");

    printf("Creations of the Clusters \n");
    vector<Cluster> cls = create_cluster(num_cl);
    printf("Clusters Created \n");

    double end_time1 = omp_get_wtime();

    auto duration = end_time1 - start_time;
    printf("Initialization made in: %f seconds\n",duration);

    int iteration_num=0;
    bool iterate = true;
    printf("-STARTING ITERATE-\n");

    while(iteration_num < iterations && iterate){

        iteration_num ++;
        find_distance(pts,cls);
        iterate = update_clusters(cls);
        printf("Iterarion %d \n",iteration_num);

    }
    double end_time2 = omp_get_wtime();
    duration = end_time2 - end_time1;
    printf("Number of iterarions %d, total time %f seconds, iteration time avg %f seconds \n",
           iteration_num,duration, duration/iteration_num);

    printf("Storing the points coordinates and cluster-id...\n");
    plot(pts);


    return 0;
}





// create number of points equal to num_py
vector<Point> create_point(int num_pt){
    vector<Point>pts(num_pt);
    Point *ptr = &pts[0];
    for (int i = 0; i <num_pt; i++) {
        Point* point = new  Point(rand() % (int) max_value, rand() % (int) max_value);
        // assign the value of *point to ptr[i] that points to &pts
        ptr[i]= *point;
    }
    return pts;
}

// create number of clusters equal to num_cl
vector<Cluster> create_cluster(int num_cl){
    vector<Cluster>cls(num_cl);
     Cluster* ptr = &cls[0];
    for (int i = 0; i <num_cl; i++) {
        Cluster* cluster = new  Cluster(rand() % (int) max_value, rand() % (int) max_value);
        ptr[i] = *cluster;
    }
    return cls;
}

//calculate the euclidean distance between the point and the cluster
double euclidean_dist(Point pt, Cluster cl){
    //sqrt((point.x^2-cluster.x^2)+(point.y^2-cluster.y^2))
    double dist =sqrt(pow(pt.get_x() - cl.get_x(),2) +
                      pow(pt.get_y() - cl.get_y(), 2));
    return dist;
}

// update the values of the clusters
bool update_clusters(vector<Cluster>&cls) {
    bool  iterate = false;
    for (int i = 0; i < cls.size(); i++) {
        iterate = cls[i].update_values();
        cls[i].delete_values();
    }
    return iterate;
}
void find_distance(vector<Point>&pts,vector<Cluster>&cls){
        unsigned long pts_size = pts.size();
        unsigned long cls_size = cls.size();

        double min_dist;
        int min_index;

    for (int i = 0; i <pts_size ; i++) {
        Point &point = pts[i];
        min_dist = euclidean_dist(point,cls[0]);
        min_index = 0;
        for (int j = 0; j < cls_size; j++) {
            Cluster &cluster = cls[j];
            double dist = euclidean_dist(point, cluster);
            // check the value of the distance if is inferior, update
            if (dist<min_dist){
                min_dist = dist;
                min_index = j;
            }
        }
        // set the cluster_id oof the point with minor distance
        //printf(" il min index: %d\n",min_index);
        pts[i].set_id(min_index);
        // add the point to the found cluster
        cls[min_index].add_point(pts[i]);
    }

 }



//Draw point plot with gnuplot
void plot(vector<Point> &points){


    ofstream Myfile("data.txt");
    Myfile << "x,y,cluster_id"<< endl ;

    for(int i = 0; i < points.size(); i++){

        Point point = points[i];
        Myfile << point.get_x() << "," << point.get_y() << "," << point.get_cluster_id() << endl;

    }
    Myfile.close();
}


