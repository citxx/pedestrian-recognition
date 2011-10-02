#include <QDir>
#include <QStringList>
#include <cstring>

#include "SampleSet.hpp"

SampleSet::SampleSet(const char *directoryName, const char *resultFileName) {
    QDir directory(directoryName);

    if (!directory.exists()) {
        throw "The sample directory does not exist";
    }
    else {
        QStringList samplesInfo = directory.entryList(QStringList("*.png"), QDir::NoFilter, QDir::Name);

        if (strcmp(resultFileName, "") != 0) {
            QFileInfo result(resultFileName);
            if (!result.exists()) {
                throw "The result file does not exist";
            }
            else {
            }
        }
    }
}
