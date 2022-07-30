
#ifndef MIDTERM_PC_POINT_H
#define MIDTERM_PC_POINT_H

class Point{

private:
    double coord_x; // identifies the x coordinate of the point
    double coord_y; // identifies the y coordinate of the point
    int id_cluster; // identifies the id of the cluster of the point

public:

    Point(double coord_x, double coord_y){
        this->coord_x = coord_x;
        this->coord_y = coord_y;
        id_cluster = 0;
    }

    Point (){
        coord_x = 0;
        coord_y = 0;
        id_cluster = 0;
    }

    // getter and setter methods of the class point
    double get_x(){
        return this->coord_x;
    }

    double get_y(){
        return this->coord_y;
    }

    void set_id(int id){
        this->id_cluster = id;
    }

    int get_cluster_id(){
        return id_cluster;
    }
};

#endif //MIDTERM_PC_POINT_H
