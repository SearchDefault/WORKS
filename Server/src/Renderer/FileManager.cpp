#include "FileManager.hpp"

FileManager::FileManager ( std::string path )
{
    Open ( path );
}

FileManager::~FileManager ()
{
    if ( file.is_open () )
        file.close ();
}

bool FileManager::Open ( std::string path )
{
    if ( file.is_open () )
        file.close ();
    
    this -> path = path;
    file.open ( path, std::fstream::in | std::fstream::out | std::fstream::app );
    
    if ( !file.is_open () )
        return false;
    
    return true;
}

bool FileManager::SaveInFile ( std::string data )
{
    if ( file.is_open () )
    {
        file << data << std::endl;
        
        return true;
    }
    
    return false;
}

std::vector<std::string> FileManager::ReadInFile ()
{
    std::vector<std::string> data;
    std::string str;
    
    if ( file.is_open () )
    {
        while ( !file.eof () )
        {
            file >> str;
            data.push_back ( str );
        }
        return data;
    }
    return data;
}
