#include <iostream>
#include <fstream>

using namespace std;

class KImage{
  
private:
    unsigned char header[54];
    unsigned char* pixelData;

    int width;
    int height;
    short bpp;
    int pixelBytes;
    int rowSize;
    int dataSize;

    int read_int(unsigned char* bytes) {
        return (int)(bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24));
    }

    short read_short(unsigned char* bytes) {
        return (short)(bytes[0] | (bytes[1] << 8));
    }

public:
    KImage() : pixelData(nullptr) {}

    bool load(const char* filename) {
        ifstream in(filename, ios::binary);
        if (!in) {
            cout << "BMP dosyasi acilamadi!" << endl;
            return false;
        }

        in.read((char*)header, 54);

        if (header[0] != 'B' || header[1] != 'M') {
            cout << "Gecerli bir BMP degil!" << endl;
            return false;
        }

        width  = read_int(&header[18]);
        height = read_int(&header[22]);
        bpp    = read_short(&header[28]);

        if (bpp != 24 && bpp != 32) {
            cout << "Sadece 24-bit ve 32-bit BMP destekleniyor!" << endl;
            return false;
        }

        pixelBytes = bpp / 8;
        rowSize = (width * pixelBytes + 3) & (~3);
        dataSize = rowSize * height;

        pixelData = new unsigned char[dataSize];
        in.read((char*)pixelData, dataSize);
        in.close();

        return true;
    }

    void printInfo() const {
        cout << "BMP Bilgileri:" << endl;
        cout << "Width  : " << width << endl;
        cout << "Height : " << height << endl;
        cout << "BPP    : " << bpp << endl;
    }

    void eraseCenterSquare(int eraseSize) {
        int half = eraseSize / 2;
        int centerX = width / 2;
        int centerY = height / 2;

        for (int y = centerY - half; y < centerY + half; y++) {
            if (y < 0 || y >= height) continue;

            for (int x = centerX - half; x < centerX + half; x++) {
                if (x < 0 || x >= width) continue;

                int index = y * rowSize + x * pixelBytes;

                pixelData[index + 0] = 0; // B
                pixelData[index + 1] = 0; // G
                pixelData[index + 2] = 0; // R

                if (pixelBytes == 4)
                    pixelData[index + 3] = 255;
            }
        }
    }

    bool save(const char* filename) {
        ofstream out(filename, ios::binary);
        if (!out) {
            cout << "Cikis dosyasi olusturulamadi!" << endl;
            return false;
        }

        out.write((char*)header, 54);
        out.write((char*)pixelData, dataSize);
        out.close();

        return true;
    }

    ~KImage() {
        delete[] pixelData;
    }
};

int main() {

    KImage k;

    if (!k.load("odev12.bmp"))
        return 1;

    k.printInfo();

    k.eraseCenterSquare(500);

    if (!k.save("output.bmp"))
        return 1;

    cout << "output.bmp basariyla olusturuldu!" << endl;
    return 0;
}
