//#include "StarFallEngine.h"
//
//using namespace STR_FALL;
//
//int main()
//{
//    std::cout << "Directory Operations:\n";
//    std::cout << "Working directory: " << GetWorkingDirectory() << "\n";
//
//    std::cout << "Setting directory to 'Assets'...\n";
//    SetWorkingDirectory("Assets");
//    std::cout << "New directory: " << GetWorkingDirectory() << "\n\n";
//
//    std::cout << "Files in Directory:\n";
//    auto filenames = GetFilesInDirectory(GetWorkingDirectory());
//    for (const auto& filename : filenames)
//    {
//        std::cout << filename << "\n";
//    }
//    std::cout << "\n";
//
//    if (!filenames.empty())
//    {
//        std::string str = GetFilename(filenames[0]);
//        std::cout << "Filename: " << str << "\n";
//
//        str = GetFileExtension(filenames[0]);
//        std::cout << "Extension: " << str << "\n";
//
//        str = GetFilenameNoExtension(filenames[0]);
//        std::cout << "Filename No Extension: " << str << "\n\n";
//    }
//
//    std::cout << "Text File Reading:\n";
//    std::string str;
//    if (ReadTextFile("test.txt", str))
//    {
//        std::cout << str << "\n";
//    }
//
//    std::cout << "Text File Writing:\n";
//    WriteTextFile("test.txt", "Hello, World!", true);
//    if (ReadTextFile("test.txt", str))
//    {
//        std::cout << str << "\n";
//    }
//}