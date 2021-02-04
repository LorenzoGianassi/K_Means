
#ifndef MIDTERM_PC_CLUSTER_H
#define MIDTERM_PC_CLUSTER_H

#include "Point.h"
#include <queue>

class Cluster{
private:
    double coord_x;
    double coord_y;
    int N_points; // number of points in the cluster
    double tot_coord_x;
    double tot_coord_y;
public:

    Cluster(double coord_x,double coord_y){
        N_points = 0;
        this->coord_x = coord_x;
        this->coord_y = coord_y;
        tot_coord_x = 0;
        tot_coord_y = 0;
    }

    Cluster(){
        N_points = 0;
        this->coord_x = 0;
        this->coord_y = 0;
        tot_coord_x = 0;
        tot_coord_y = 0;
    }
    double get_x(){
        return this->coord_x;
    }

    double get_y(){
        return this->coord_y;
    }
    void add_point(Point pt){
        N_points++; // increase the number of points of the cluster
        tot_coord_x += pt.get_x(); //update the value of total coordinate x
        tot_coord_x += pt.get_y(); //update the value of total coordinate y
    }
    void delete_values(){
        this->N_points = 0;
        this->tot_coord_x = 0;
        this->tot_coord_y = 0;
    }

    bool update_values(){
        if(this->coord_x == tot_coord_x/this->N_points && this->coord_y == tot_coord_y/this->N_points){
            return false;
        }
        else{
            this->coord_x = tot_coord_x/this->N_points;
            this->coord_y = tot_coord_x/this->N_points;
            return true;
        }

    }

};

#endif //MIDTERM_PC_CLUSTER_H
