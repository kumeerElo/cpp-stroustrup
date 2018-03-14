#include "std_lib_facilities.h"
#include "Simple_window.h"
//#include "Graph.h"
#include <iostream>

class Binary_tree : public Shape {
public:
    enum Arrow 
		{Up = 123, Down = 456
		};
private:
    // Unfortunately, because we can't have virtual class functions,
    // the structure is horrible, but I can't see a simpler solution
    class Subnode {
    public:
        Point c;
        int n, s, l, r;
        string a;
        Subnode (Vector_ref<Subnode> & subnodes,
                Point c0, int n0, int s0) : c(c0), n(n0), s(s0), a("") {
            if (n0 <= 0) return;
            int t = 2*s0;
            subnodes.push_back(
                new Subnode(subnodes,Point(c0.x-t,c0.y+t),n0-1,s0/2));
            l = int(subnodes.size()-1);
            subnodes.push_back(
                new Subnode(subnodes,Point(c0.x+t,c0.y+t),n0-1,s0/2));
            r = int(subnodes.size()-1);
        }
    };
    Arrow mode;
    int levels;
    // Note that the last element will be the root
    Vector_ref<Subnode> subnodes;
public:
    Binary_tree (Point c, int n, int s, Arrow d) : levels(n), mode(d) {
        if (n < 0 || n > 5) error("Bad number of levels");
        if (s < (1<<n)) error("Bad size for tree");
        if (n <= 0) return;
        subnodes.push_back(new Subnode(subnodes,c,n-1,s/2));
    }
    virtual void drawl (Point c, int s) const {
        fl_arc(c.x-s,c.y-s,2*s,2*s,0,360);
    }
    void draw_lines () const {
        if (color().visibility()) {
            fl_color(color().as_int());
            for (int i = 0; i < int(subnodes.size()); ++i) {
                Point c = subnodes[i].c;
                int s = subnodes[i].s;
                drawl(c,s);
                fl_draw(subnodes[i].a.c_str(),c.x,c.y);
                if (subnodes[i].n > 0) {
                    int u = int(s/sqrt(2.0)),
                        v = 2*s-int(s/(2.0*sqrt(2.0)));
                    fl_line(c.x-u,c.y+u,c.x-v,c.y+v);
                    fl_line(c.x+u,c.y+u,c.x+v,c.y+v);
                    int p = (u+v)/2, q = (v-u+1)/2;
                    if (mode == Up) {
                        fl_line(c.x-p,c.y+p,c.x-p-q,c.y+p);
                        fl_line(c.x-p,c.y+p,c.x-p,c.y+p+q);
                        fl_line(c.x+p,c.y+p,c.x+p+q,c.y+p);
                        fl_line(c.x+p,c.y+p,c.x+p,c.y+p+q);
                    } else if (mode == Down) {
                        fl_line(c.x-p,c.y+p,c.x-p+q,c.y+p);
                        fl_line(c.x-p,c.y+p,c.x-p,c.y+p-q);
                        fl_line(c.x+p,c.y+p,c.x+p-q,c.y+p);
                        fl_line(c.x+p,c.y+p,c.x+p,c.y+p-q);
                    }
                }
            }
        }
    }
    void move (int x, int y) {
        for (int i = 0; i < int(subnodes.size()); ++i)
            subnodes[i].c = Point(subnodes[i].c.x+x,subnodes[i].c.y+y);
    }
    void annotate (int n, int w, const string arg) {
        if (n < 0 || n > levels) error("Bad level");
        if (w < 0 || w >= (1<<n)) error("Bad node in level");
        int k = int(subnodes.size()-1), m = (1<<n), x = w;
        for (int i = 0; i < n; ++i) {
            x <<= 1;
            if (x&m)
                k = subnodes[k].r;
            else
                k = subnodes[k].l;
        }
        subnodes[k].a = arg;
    }
};

class Square_tree : public Binary_tree {
    void drawl (Point c, int s) const {
        double t = s/sqrt(2.0);
        fl_line(c.x-t,c.y-t,c.x-t,c.y+t);
        fl_line(c.x-t,c.y+t,c.x+t,c.y+t);
        fl_line(c.x+t,c.y+t,c.x+t,c.y-t);
        fl_line(c.x+t,c.y-t,c.x-t,c.y-t);
    }
public:
    Square_tree (Point c, int n, int s, Arrow d) : Binary_tree (c,n,s,d) {}
};

int main () {
    Point top_left(200,100);
    Simple_window win(top_left,800,800,"Astrology");
    Binary_tree t(Point(400,300),5,200,Binary_tree::Up);
    t.set_color(Color::green);
    win.attach(t);      
    win.wait_for_button();
    //t.annotate(0,0,"Kilroy was here");
    t.annotate(2,3,"Hello, sailor!");
    t.annotate(3,2,"I yam what I yam");
    Square_tree v(Point(150,150),3,50,Binary_tree::Down);
    v.set_color(Color::red);
    win.attach(v);      
    win.wait_for_button();
    v.move(500,100);
    win.wait_for_button();
}
