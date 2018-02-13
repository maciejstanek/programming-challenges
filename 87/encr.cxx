#include <stdio.h>
#include <iostream>
#include <Magick++.h>

using namespace std;
using namespace Magick;

int main(int argc, char **argv) {
  InitializeMagick(*argv);

  Image image;
  try {
    image.read("duck.jpg");
    image.crop(Geometry(100, 100, 100, 100));
    image.write("THE_DUCK.png");
  }
  catch(Exception &error_) {
    cout << "Caught exception: " << error_.what() << endl;
    return 1;
  }
  return 0;
}
