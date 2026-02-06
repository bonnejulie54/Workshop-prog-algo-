#include <sil/sil.hpp>
#include <random.hpp>
#include <cmath>

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
            image.pixel(x,y)=copy.pixel(image.width()-(x+1),y);
        }
    }
}

void echange_canaux(sil::Image&image){
    sil::Image copy= image; 
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            image.pixel(x,y).r=copy.pixel(x,y).g;
            image.pixel(x,y).g=copy.pixel(x,y).r;
        }
    }
}

void degrade(sil::Image&image){
    sil::Image copy= image; 
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            float t = static_cast<float>(x)/(image.width()-1);
            image.pixel(x,y)={t,t,t};    
             }
    }
}
 
void negatif(sil::Image&image){
    sil::Image copy= image; 
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
           image.pixel(x,y)=1.0f-copy.pixel(x,y);
        }
    }
}

void bruit(sil::Image&image){
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<100;++x){
           float pix=random_int(0.f,image.width()-1 );
           float r= random_float(0.f, 1.f);
           float g= random_float(0.f, 1.f);
           float b= random_float(0.f, 1.f);
           image.pixel(pix,y)= {r,g,b};
        }
    }
}

void rotation(sil::Image&image){
    sil::Image copy= image; 
    sil::Image new_image{image.height(), image.width()};
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
           int new_x = copy.height() - 1 - y;
            int new_y = x;

            new_image.pixel(new_x, new_y) = copy.pixel(x, y);
        }
    }
    image = new_image;
}

void rgb_split(sil::Image&image){
    sil::Image copy= image; 
    int d=30;
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            int xr = x - d; 
            int xb = x + d; 
            if(xr < 0) xr = 0;
            if(xb >= image.width()) xb = image.width() - 1;
            image.pixel(x,y).r=copy.pixel(xr,y).r;
            image.pixel(x,y).g=copy.pixel(x,y).g;
            image.pixel(x,y).b=copy.pixel(xb,y).b;
        }
    }
}

void eclaircir(sil::Image&image){
    sil::Image copy= image; 
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            image.pixel(x,y).r = sqrt(copy.pixel(x,y).r);
            image.pixel(x,y).g = sqrt(copy.pixel(x,y).g);
            image.pixel(x,y).b = sqrt(copy.pixel(x,y).b);
        }
    }
}

void assombrir(sil::Image&image){
    sil::Image copy= image; 
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            image.pixel(x,y).r = copy.pixel(x,y).r*copy.pixel(x,y).r;
            image.pixel(x,y).g = copy.pixel(x,y).g*copy.pixel(x,y).g;
            image.pixel(x,y).b = copy.pixel(x,y).b*copy.pixel(x,y).b;
        }
    }
}

void disque_blanc( sil::Image&image){
    
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            if ( (x-image.width()/2)*(x-image.width()/2)+(y-image.height()/2)*(y-image.height()/2)<=50*50){
                image.pixel(x,y)={1.0f,1.0f,1.0f};
            }
        }
    }
}

void cercle_blanc( sil::Image&image){
    int thickess=5;
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            if ( (x-image.width()/2)*(x-image.width()/2)+(y-image.height()/2)*(y-image.height()/2)<=50*50 and (x-image.width()/2)*(x-image.width()/2)+(y-image.height()/2)*(y-image.height()/2)>=(50-thickess)*(50-thickess)) {
                image.pixel(x,y)={1.0f,1.0f,1.0f};
            }
        }
    }
}

void rosace( sil::Image&image){
    int thickess=5;
    for(int y=0; y<image.height();++y){
        for ( int x=0;x<image.width();++x){
            if ( (x-image.width()/2)*(x-image.width()/2)+(y-image.height()/2)*(y-image.height()/2)<=50*50 and (x-image.width()/2)*(x-image.width()/2)+(y-image.height()/2)*(y-image.height()/2)>=(50-thickess)*(50-thickess)) {
                image.pixel(x,y)={1.0f,1.0f,1.0f};
            }
            for ( int i=0;i<6;++i){
                float angle=i*M_PI/3;

                float centre_x= 50*cos(angle)+image.width()/2;
                float centre_y=50*sin(angle)+image.height()/2;

                if ( (x-centre_x)*(x-centre_x)+(y-centre_y)*(y-centre_y)<=50*50 and (x-centre_x)*(x-centre_x)+(y-centre_y)*(y-centre_y)>=(50-thickess)*(50-thickess)) {
                image.pixel(x,y)={1.0f,1.0f,1.0f};
                }
                
                
            }
        }
    }
}

void glitch(sil::Image& image) {
    int width = image.width();
    int height = image.height();

    int iterations = 100; 

    for (int i = 0; i < iterations; i++) {

        int w = random_int(2, 30);
        int h = random_int(2, 10);

        int x1 = random_int(0, width - w - 1);
        int y1 = random_int(0, height - h - 1);
        int x2 = random_int(0, width - w - 1);
        int y2 = random_int(0, height - h - 1);

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {

                auto temp = image.pixel(x1 + x, y1 + y);
                image.pixel(x1 + x, y1 + y) = image.pixel(x2 + x, y2 + y);
                image.pixel(x2 + x, y2 + y) = temp;
            }
        }
    }
}

void mosaic(sil::Image& image, sil::Image& result){ 

    for (int y = 0; y < result.height(); ++y)
    {
        for (int x = 0; x < result.width(); ++x)
        {
            int rx = x % image.width();
            int ry = y % image.height();

            result.pixel(x, y) = image.pixel(rx, ry);
        }
    }
}

void mosaic_miroir(sil::Image& image, sil::Image& result)
{
    for (int y = 0; y < result.height(); ++y)
    {
        for (int x = 0; x < result.width(); ++x)
        {
            int rx = x % image.width();
            int ry = y % image.height();

            if ((x / image.width()) % 2 == 1)
                rx = image.width() - 1 - rx;

            if ((y / image.height()) % 2 == 1)
                ry = image.height() - 1 - ry;

            result.pixel(x, y) = image.pixel(rx, ry);
        }
    }
}


int main()
{
    sil::Image image{"images/logo.png"};
    sil::Image result{image.width()*5, image.height()*5};
    mosaic_miroir(image, result);
    result.save("output/mosaic_mirror.png");
   
   { sil::Image image{"images/logo.png"};
    sil::Image result{image.width()*10, image.height()*10};
    mosaic(image, result);
    result.save("output/mosaic.png");}

    
    {sil::Image image{300/*width*/, 200/*height*/};
    degrade(image);
    image.save("output/degrade.png");}
    
    {sil::Image image{"images/logo.png"};
    glitch(image);
    image.save("output/logoGlitch.png");}
    
    {sil::Image image{500/*width*/, 500/*height*/};
    rosace(image);
    image.save("output/rosace.jpg");}
    
    {sil::Image image{500/*width*/, 500/*height*/};
    cercle_blanc(image);
    image.save("output/cercleBlanc.jpg");}
    
    {sil::Image image{500/*width*/, 500/*height*/};
    disque_blanc(image);
    image.save("output/disqueBlanc.jpg");}

    {sil::Image image{"images/photo.jpg"};
    assombrir(image);
    image.save("output/photoAssombrit.jpg");}
    
    {sil::Image image{"images/photo.jpg"};
    eclaircir(image);
    image.save("output/photoEclaircit.jpg");}

    {sil::Image image{"images/logo.png"};
    rgb_split(image);
    image.save("output/logoRgbSplit.png");}

    {sil::Image image{"images/logo.png"};
    rotation(image);
    image.save("output/logoRotation.png");}

    {sil::Image image{"images/logo.png"};
    bruit(image);
    image.save("output/logoBruit.png");}

    {sil::Image image{"images/logo.png"};
    negatif(image);
    image.save("output/logoNegatif.png");}

    {sil::Image image{"images/logo.png"};
    echange_canaux(image);
    image.save("output/logoEchange.png");}

    {sil::Image image{"images/logo.png"};
    miroir(image);
    image.save("output/logoMiroir.png");}

    {sil::Image image{"images/logo.png"};
    nb(image);
    image.save("output/logoNb.png");}

   {sil::Image image{"images/logo.png"};
    vert(image);
    image.save("output/logoVert.png");}
}