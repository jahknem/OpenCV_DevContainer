#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;

/**
 * Ad-hoc implementation to load OBJ files. Probably only works for bunny.obj
 * @param path path to a .obj file
 * @param vtx Nx(x,y,z) array of positions
 * @param idx Mx(i0, i1, i2) array of triangle faces
 */
static void load_obj(const char* path, Mat_<Vec3f>& vtx, Mat_<Vec3i>& idx)
{    
    std::ifstream f(path);
    
    char c;
    Vec3f av;
    Vec3i af;
    
    while(f.good())
    {
        f >> c;
        switch(c)
        {
            case 'v':
                f >> av.val[0] >> av.val[1] >> av.val[2];
                vtx.push_back(av);
                break;
            case 'f':
                f >> af.val[0] >> af.val[1] >> af.val[2];
                idx.push_back(af - Vec3i::all(1));
                break;
            default:
                f.ignore(1024, '\n');
        }
    }
}


int main(int argc, char** argv)
{
    // YOUR CODE BEGINS HERE
    CV_Assert(false && "Rename this to: firstname_lastname.cpp");
    return 0;
}
