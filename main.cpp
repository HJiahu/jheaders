#include<iostream>
#include"format.h"
#include"ezlog.h"
#include"filesystem.h"
#include"json.h"
#include"3rdparty/CImg.h"
using namespace std;
namespace jh = jheaders;

#ifndef _MSC_VER
    #define INIT_EZLOG
#endif // !_MSC_VER

using namespace cimg_library;


int main()
{
    std::string img_path ("./lena.bmp");
    EZAssert (jh::exists (img_path));
    CImg<unsigned char> image (img_path.c_str()), visu (500, 400, 1, 3, 0);
    const unsigned char red[] = { 255, 0, 0 }, green[] = { 0, 255, 0 }, blue[] = { 0, 0, 255 };
    image.blur (2.5);
    CImgDisplay main_disp (image, "Click a point"), draw_disp (visu, "Intensity profile");
    
    while (!main_disp.is_closed() && !draw_disp.is_closed())
    {
        main_disp.wait();
        
        if (main_disp.button() && main_disp.mouse_y() >= 0)
        {
            const int y = main_disp.mouse_y();
            visu.fill (0).draw_graph (image.get_crop (0, y, 0, 0, image.width() - 1, y, 0, 0), red, 1, 1, 0, 255, 0);
            visu.draw_graph (image.get_crop (0, y, 0, 1, image.width() - 1, y, 0, 1), green, 1, 1, 0, 255, 0);
            visu.draw_graph (image.get_crop (0, y, 0, 2, image.width() - 1, y, 0, 2), blue, 1, 1, 0, 255, 0).display (draw_disp);
        }
    }
    
#ifdef _MSC_VER
    system ("pause");
#endif
}
