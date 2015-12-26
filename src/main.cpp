#include "heightmap.h"
#include "viewer.h"
#include "lodepng.h"
#include "diamond_square_generator.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

/*
void saveToPng(const vector< unsigned char >& img, int w, int h)
{
    unsigned error = lodepng::encode("test.png", img, w, h, LCT_GREY);
    if(error)
        cout << "encoder error " << error << ": " << lodepng_error_text(error) 
                  << endl;
} // saveToPng()
*/

int generate(const vector< string >& args)
{
    auto curArg = args.begin();
    unsigned int sizeArg;
    string targetFileArg;
    if(args.empty()) {
        cout << "Usage: generate [-o target_file] size\n" << endl;
        return 0;
    } 
    if(curArg->size() == 2 && (*curArg)[0] == '-') {
        switch((*curArg)[1]) {
            case('o'): 
                if(curArg + 1 != args.end()) {
                    targetFileArg = *(curArg + 1);
                    curArg += 2;
                } else {
                    cout << "Generate: -o: missing target file name." << endl;
                    return -1;
                }
                break;
            default:
               cout << "Generate: invalid option " << *curArg << endl;
               return -1;
        }
    }
    if(curArg == args.end()) {
        cout << "Generate: no size provided." << endl;
        return -1;
    }
    try {
        sizeArg = stoi(*curArg);
    } catch(...) {
        cout << "Generate: invalid size " << *curArg << endl;
        return -1;
    }
    // Check that size - 1 is a power of 2.
    if(sizeArg == 0 || ((sizeArg - 1) & (sizeArg - 2)) != 0) {
        cout << "Generate: invalid size " << sizeArg 
             << ", must be power of 2 + 1." << endl;
    }
    unsigned int detailLevel = log(sizeArg - 1) / log(2);
    Heightmap heightmap(detailLevel);
    DiamondSquareGenerator generator;
    generator.setCornerSeed(0.0);
    generator.generate(heightmap);
    const vector< unsigned char >& image = heightmap.asImage();
    // Output to STDOUT.
    if(targetFileArg.empty()) {
        vector< unsigned char > out;
        lodepng::encode(out, image, sizeArg, sizeArg, LCT_GREY);
        for(auto it = out.begin(); it != out.end(); it++) {
            cout << *it;
        }
    } else { // Output to file.
        lodepng::encode(targetFileArg.c_str(), image, sizeArg, sizeArg, LCT_GREY);
    }
    return 0;
} // generate()

int view(const vector< string >& args)
{
    auto curArg = args.begin();
    string sourceFileArg;
    if(curArg != args.end() && curArg->size() == 2 && (*curArg)[0] == '-') {
        switch((*curArg)[1]) {
            case('i'): 
                if(curArg + 1 != args.end()) {
                    sourceFileArg = *(curArg + 1);
                    curArg += 2;
                } else {
                    cout << "View: -i: missing source file name." << endl;
                    return -1;
                }
                break;
            default:
               cout << "View: invalid option " << *curArg << endl;
               return -1;
        }
    }
    Viewer viewer;
    // Input from STDIN.
    if(sourceFileArg.empty()) {
        vector< unsigned char > in;
        char byte;
        while(cin.get(byte)) {
            in.push_back(byte);
        }
        vector< unsigned char > out;
        unsigned int w, h;
        lodepng::decode(out, w, h, in, LCT_GREY);
        if(w != h) {
            cout << "View: input image is not square." << endl;
            return -1;
        }
        viewer.setHeightmap(out, w);
    } else { // Input from file.
        vector< unsigned char > out;
        unsigned int w, h;
        lodepng::decode(out, w, h, sourceFileArg, LCT_GREY);
        if(w != h) {
            cout << "View: input image is not square." << endl;
            return -1;
        }
        viewer.setHeightmap(out, w);
    }
    viewer.run();
    return 0;
} // view()

int help(const vector< string >& args)
{
    if(!args.empty()) {
        if(args[0] == "generate") {
            cout << "Usage: generate [-o target_file] size\n\n"
                    "Description:\n"
                    "Generates a heightmap with dimensions size x size."
                    " By default outputs the image to STDOUT. Size should"
                    " be a power of 2 plus 1, e.g. 129, 513, etc.\n\n"
                    "Options:\n"
                    "  -o  Outputs image to target_file instead of STDOUT."
                    " PNG is currently the only supported image format.\n"
                 << endl;
            return 0;
        } else if(args[0] == "view") {
            cout << "Usage: view [-i source_file]\n\n"
                    "Description:\n"
                    "Loads a heightmap image into a 3D viewer. By default,"
                    " uses STDIN as the input.\n\n"
                    "Options:\n"
                    "  -i  Reads the image from source_file instead of "
                    " STDIN."
                    " PNG is currently the only supported image format.\n"
                 << endl;
            return 0;
        }
    }
    cout << "Usage: help command" << endl;
    return 0;
} // help()

int main(int argc, char* argv[])
{
    vector< string > args(argc);
    transform(argv, argv + argc, args.begin(),
        [](char* arg) { return string(arg); });
    if(args.size() > 1) {
        vector< string > cmdArgs(args.begin() + 2, args.end());
        if(args[1] == "generate") {
            return generate(cmdArgs);
        } else if(args[1] == "view") {
            return view(cmdArgs);
        } else if(args[1] == "help") {
            return help(cmdArgs);
        }
    }
    cout << "Usage: heightmap command [options]\n" 
            "Commands:\n"
            "  generate: generates a new heightmap.\n"
            "  view: opens a 3d heightmap viewer.\n" 
            "  help command: shows the usage of a command.\n"
         << endl;
    return 0;
} // main()
