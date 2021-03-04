#include <iostream>
#include <iomanip>
#include <fstream>
#include <ios>
#include <list>
#include <vector>
#include <chrono>
#include <iterator>
#include <stdlib.h>
#include <ctime>
#include <math.h>

class RGB {
public:
    int Red;
    int Blue;
    int Green;
    double grayScale;
    RGB()
    {

    }
    RGB(int red, int green, int blue)
    {
        Red = red;
        Green = green;
        Blue = blue;
        grayScale = (red + blue + green)/3;
    }
    double getGrayScale()
    {
        return grayScale;
    }

private:




};

using namespace std;

void readImage();

int	GX[3][3];
int	GY[3][3];
void output();
void part1();
vector<RGB> magicNumbers;
std::vector<int> XSide;
std::vector<int> YSide;
int pixel;
string pix;


int main() {
    cout << "Size B4: " << magicNumbers.size() << endl;
    readImage();
    cout << "Size After: " << magicNumbers.size() << endl;


    //part1();

    //output();

    return 0;
}

void part1() {



//
//    for (int y = 0; y < height; y++) {
//        for (int x = 0; x < width; x++) {
//
//            test<< matrix[y][x] << " "<< matrix[y][x] << " " << matrix[y][x] << "     ";
//            cout << matrix[y][x]  << endl;
//        }
//        test << endl;
//    }

    //test.close();

}



void readImage() {
    int width = 1280;
    int height = 853;
    string magic;
    std::ifstream test;
    int red;
    int blue;
    int green;
    test.open ("elephant.ppm");
    int i = 0;
    while (test >> magic)
    {
        if(i>3) {
            if(i%3 == 1)
            {
                red = stoi(magic);
            }
            if(i%3 == 2)
            {
                blue = stoi(magic);
            }
            if(i%3 == 0)
            {
                green = stoi(magic);
                RGB gen(red, green, blue);
                magicNumbers.push_back(gen);
            }
        }
        else if( i ==0)
        {
            pix = magic;
            cout << "Pix: " <<pix << endl;
        }
        else if( i ==1)
        {
            width = stoi(magic);
            cout << "Width: " <<width << endl;
        }
        else if( i ==2)
        {
            height = stoi(magic);
            cout << "Hei: " <<height << endl;
        }

        else if(i ==3)
        {
            pixel = stoi(magic);
            cout << "Pixel: " <<pixel << endl;
        }

        i++;
    }
    test.close();
    cout << "before" << endl;

    int matrix[height][width];


    cout << "after" << endl;
    int iii = 0;
    std::ofstream output;
    output.open("elephant .ppm");
    output << pix << endl << width << ' ' << height << endl << pixel << endl;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            matrix[y][x] = int(magicNumbers[iii].grayScale);
            //cout << matrix[y][x] << "  " << magicNumbers[iii].getGrayScale() << endl;
            output<< matrix[y][x] << " "<< matrix[y][x] << " " << matrix[y][x] << "     ";
            iii++;
        }
        output << endl;
    }

    GX[0][0] = -1; GX[0][1] = 0; GX[0][2] = 1;
    GX[1][0] = -2; GX[1][1] = 0; GX[1][2] = 2;
    GX[2][0] = -1; GX[2][1] = 0; GX[2][2] = 1;

    GY[0][0] =  1; GY[0][1] =  2; GY[0][2] =  1;
    GY[1][0] =  0; GY[1][1] =  0; GY[1][2] =  0;
    GY[2][0] = -1; GY[2][1] = -2; GY[2][2] = -1;
    int tracker = 0;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            int xval;
            int yval;
            if(h == 0 || w== 0 || h == height-1 || w == width-1)
            {
                XSide.push_back(0);
                YSide.push_back(0);


            }
            else
            {

                xval = abs((matrix[h-1][w-1] * GX[0][0])+ (matrix[h-1][w] * GX[0][1])+
                       (matrix[h-1][w+1] * GX[0][2]) + (matrix[h][w-1] * GX[1][0]) + (matrix[h][w] * GX[1][1]) +
                       (matrix[h][w+1] * GX[1][2]) + (matrix[h+1][w-1] * GX[2][0]) + (matrix[h+1][w] * GX[2][1]) +
                       (matrix[h+1][w+1] * GX[2][2]));
                XSide.push_back(xval);
                cout << "xval: " << xval;

                yval = abs((matrix[h-1][w-1] * GY[0][0])+ (matrix[h-1][w] * GY[0][1])+
                       (matrix[h-1][w+1] * GY[0][2]) + (matrix[h][w-1] * GY[1][0]) + (matrix[h][w] * GY[1][1]) +
                       (matrix[h][w+1] * GY[1][2]) + (matrix[h+1][w-1] * GY[2][0]) + (matrix[h+1][w] * GY[2][1]) +
                       (matrix[h+1][w+1] * GY[2][2]));
                YSide.push_back(yval);
                cout << "Yval: " << yval;
            }


            matrix[h][w]  = sqrt((xval*xval) + (yval * yval));

            if(matrix[h][w] > 200)
            {
                matrix[h][w] = 0;
            }
            else
            {
                matrix[h][w] = 255;
            }

        tracker++;

        }

    }
    cout << "X After: " << XSide.size() << endl;
    cout << "Y After: " << YSide.size() << endl;
    std::ofstream out;
    out.open("output2.ppm");
    out << pix << endl << width << ' ' << height << endl << pixel << endl;
        for (int yy = 0; yy < height; yy++) {
        for (int xx = 0; xx < width; xx++) {

            out<< matrix[yy][xx] << " "<< matrix[yy][xx] << " " << matrix[yy][xx] << "     ";
            //cout << matrix[yy][xx]  << endl;
        }
        out << endl;
    }

    out.close();
}