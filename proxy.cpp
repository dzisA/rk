#include <iostream>


class Image {
public:
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual void display() = 0;
    virtual ~Image() = default;
};

class RealImage : public Image {
    int w, h;
public:
    RealImage(int w_, int h_) : w(w_), h(h_) {}
    int getWidth() override  { return w; }
    int getHeight() override { return h; }
    void display() override   { std::cout << "Image with size " << w << "x" << h << " was displayed" << "\n" ; }
};

class Downloader {
public:
    RealImage* getImage(const std::string& path) {
        return new RealImage(1920, 1080);
    }
};

class ImageProxy : public Image {
    RealImage* real = nullptr;
    std::string filename;
    Downloader* downloader;
public:
    ImageProxy(const std::string& f, Downloader* d)
        : filename(f), downloader(d) {}

    void load() {
        if (!real)
            real = downloader->getImage(filename);
    }

    int getWidth() override  { load(); return real->getWidth(); }
    int getHeight() override { load(); return real->getHeight(); }
    void display() override  { load(); real->display(); }
    ~ImageProxy() { delete real; }
};

int main()
{
    Downloader dwn;
    ImageProxy proxy("pic.png", &dwn);
    proxy.display();
    return 0;
}
