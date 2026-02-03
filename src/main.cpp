#include <sil/sil.hpp>
void vert(sil::Image&image){
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            image.pixel(x,y).r=0.f;
            image.pixel(x,y).b=0.f;
        }
    }
}

void nb(sil::Image&image){
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            float gray=(image.pixel(x,y).r*0.2126+image.pixel(x,y).g*0.7152+image.pixel(x,y).b*0.0722);
            image.pixel(x,y).r=gray;
            image.pixel(x,y).b=gray;
            image.pixel(x,y).g=gray;
        }
    }
}

void miroir(sil::Image&image){
    sil::Image copy= image; 
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            image.pixel(x,y)=copy.pixel(image.git width()-(x+1),y);
        }
    }
}

int main()
{
    sil::Image image{"images/logo.png"};
    miroir(image);
    image.save("output/logoMiroir.png");

    {sil::Image image{"images/logo.png"};
    nb(image);
    image.save("output/logoNb.png");}

   {sil::Image image{"images/logo.png"};
    vert(image);
    image.save("output/logoVert.png");}
}