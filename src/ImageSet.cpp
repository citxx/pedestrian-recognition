#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <opencv/highgui.h>

#include "ImageSet.hpp"
#include "debug.hpp"

ImageSet::ImageSet(std::string directoryName):
    directoryName(directoryName) {

    boost::filesystem::path dirPath(directoryName);
    debugInline("Checking sample directory '" + dirPath.string() + "' for existance... ");

    if (!boost::filesystem::exists(dirPath)) {
        throw "Sample directory is not exists";
    }
    if (!boost::filesystem::is_directory(dirPath)) {
        throw "Sample directory is not a directory";
    }

    debug("done.");
}

std::vector <std::string> ImageSet::getNames() const {
    boost::filesystem::path dirPath(directoryName);

    boost::filesystem::path namesPath = dirPath / "files.dir";
    if (boost::filesystem::exists(namesPath)) {
        debugInline("File '" + namesPath.string() + "' is found. Reading names... ");
        boost::filesystem::fstream namesFile(namesPath, std::ios_base::in);
        std::vector <std::string> answer;

        std::string name;
        while (namesFile >> name) {
            answer.push_back(name);
        }
        debug("done.");

        return answer;
    }
    else {
        std::cerr << "File 'files.dir' is not found. Trying to get file list by myself =( ... ";

        std::vector <std::string> answer;

        boost::filesystem::directory_iterator file(dirPath), end;
        while (file != end) {
            if (boost::filesystem::is_regular_file(*file) && file->path().extension() == ".png") {
                std::string name = file->path().filename().string();
                answer.push_back(name.substr(0, name.length() - 4));
            }

            ++file;
        }

        std::cerr << "done." << std::endl;

        return answer;
    }
}

cv::Mat ImageSet::getImage(std::string name) const {
    boost::filesystem::path filePath = boost::filesystem::path(this->directoryName) / (name + ".png");

    if (!boost::filesystem::exists(filePath)) {
        std::cerr << "File '" << filePath.string() << "' is not exists" << std::endl;
        throw "Image does not exist";
    }

    return cv::imread(filePath.string().c_str());
}
