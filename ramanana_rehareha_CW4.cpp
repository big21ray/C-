


#include <iostream>




#define _USE_MATH_DEFINES
#include <cmath>


using namespace std;





class point{

    public:
        double x,y;

        point() {x = y = 0.0;}
        point(int a, int b);
        point(double a, double b);
        point(double a, int b);
        point(int a, double b);

};

point::point(int a,int b){
    x = (double) a;
    y = (double) b;
}

point::point(double a, double b){
    x = a;
    y = b;
}

point::point(int a, double b){
    x = double(a);
    y = b;
}
point::point(double a, int b){
    x = a;
    y = (double) b;
}

double dista(point p1, point p2);

class shape {
    protected:
        point centre;
    public:
        shape() { centre.x = centre.y = 0.0; }
        shape(const point &p) : centre(p) {}
        double dist(const shape &s);
        virtual point center() const {return centre;} ;
        virtual double area() const = 0;
        virtual double circ() const = 0;
        virtual ~shape() {}
};


double shape::dist(const shape &s){
    point a = this->center();
    point b = s.center();
    return(dista(a,b));
}

double sratio(const shape &s);


class circle : public shape {
    double radius;
public:
    circle(const point &p, double r) : shape(p) {
        if(r <0){
            radius = 0.0;
        }
        else{
            radius = r;
        }
    }
    double area() const;
    double circ() const; // both may use constant M_PI from <cmath>
    point center() const;
};

double circle::area() const{

   double p;
   p = M_PI*radius*radius;
   return p;
}

double circle::circ() const{

   double p;
   p = 2*M_PI*radius;
   return p;
}

point circle::center() const{
    return centre;
}






class triangle : public shape {
    point a,b,c;
public:
    triangle(const point &p1, const point &p2,const point &p3) : shape(p1) {
        a = p1;
        b = p2;
        c = p3;
        centre = this->center();
    }
    point center() const;
    double area() const;
    double circ() const;
};

double triangle::area() const{

   double s,p,e,r,t;
   e = dista(a,b);
   r = dista(a,c);
   t = dista(b,c);
   s = (e+r+t)/2;

   p = s*(s-e)*(s-r)*(s-t);
   return(sqrt(p));

}

double triangle::circ() const{

    double s,e,r,t;
    e = dista(a,b);
    r = dista(a,c);
    t = dista(b,c);
    s = (e+r+t)/2;

    return(2*s);

}

point triangle::center() const{

    return(point((a.x+b.x+c.x)/3,(a.y+b.y+c.y)/3));
}


class rectangle : public shape {
    point a,b,c,d;
public:
    rectangle(const point &p1, const point &p2) : shape(p1) {
        a = p1;
        c = p2;
        d = point(p1.x,p2.y);
        b = point(p2.x,p1.y);
        centre = this->center();


    }
    point center() const;
    double area() const;
    double circ() const; // both may use constant M_PI from <cmath>
};

double rectangle::area() const{

   double e,r;
   e = dista(a,b);
   r = dista(a,d);
   return(e*r);
}

double rectangle::circ() const{

    double e,r;
    e = dista(a,b);
    r = dista(a,d);
    return(2*(e+r));
}

point rectangle::center() const{
    return(point((a.x+c.x)/2,(a.y+c.y)/2));

}


int main() {

    point p(-15,20), p1(0,0), p2(3,0), p3(1.5,3), p4(0,1), p5(3,2);
    circle c(p,5.0);
    triangle t(p1,p2,p3);
    rectangle r(p4,p5);
    cout << sratio(r) << endl;

    cout << "The distance between triangle and circle is " << t.dist(c) << endl;
    return 0;

}

double dista(point p1, point p2){
    double d ;

    d = (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    return(sqrt(d));
}


double sratio(const shape &s){

    double a;
    double c;
    a = s.area();
    c = s.circ();
    if(c==0.0){
        return 1.0;
    }
    else{
        return(a/c);
    }



}


