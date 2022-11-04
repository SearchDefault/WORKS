#ifndef __FILE_MANAGER__
#define __FILE_MANAGER__
// Json Default Lib

#include <../ImGUI/imgui.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

class FileManager
{
    /*
     * Save in File
     * Read is File
    */
    std::fstream file;
    std::string path;
    std::vector<std::string> data;
    
public:
    
    FileManager ( std::string path );
    
    ~FileManager ();
    
    bool Open ( std::string path );
    
    bool SaveInFile ( std::string data );
    
    std::vector<std::string> ReadInFile ();
};

#endif//__FILE_MANAGER__
