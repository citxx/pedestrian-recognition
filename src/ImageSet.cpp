#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <opencv/highgui.h>

#include "ImageSet.hpp"

ImageSet::ImageSet(std::string directoryName):
    directoryName(directoryName) {

    boost::filesystem::path dirPath(directoryName);
    if (!boost::filesystem::exists(dirPath)) {
        std::cerr << "The directory '" << directoryName << "' is not exists" << std::endl;
        throw "Sample directory is not exists";
    }
    if (!boost::filesystem::is_directory(dirPath)) {
        std::cerr << "'" << directoryName << "' is not a directory" << std::endl;
        throw "Sample directory is not a directory";
    }
}

std::vector <std::string> ImageSet::getNames() const {
    boost::filesystem::path dirPath(directoryName);

    boost::filesystem::path namesPath = dirPath / "files.dir";
    if (boost::filesystem::exists(namesPath)) {
        boost::filesystem::fstream namesFile(namesPath, std::ios_base::in);
        std::vector <std::string> answer;

        std::string name;
        while (namesFile >> name) {
            answer.push_back(name);
        }

        return answer;
    }
    else {
        std::cerr << "File 'files.dir' is not found. Trying to get file list by myself =(.";

        std::vector <std::string> answer;

        for (boost::filesystem::path::iterator file = dirPath.begin(); file != dirPath.end(); ++file) {
            boost::filesystem::path filePath = dirPath / (*file);
            if (filePath.extension() == ".png") {
                answer.push_back(filePath.filename());
            }
        }

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
