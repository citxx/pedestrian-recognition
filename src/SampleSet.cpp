#include <QDir>
#include <QStringList>

#include "SampleSet.hpp"

SampleSet::SampleSet(const char *directoryName, const char *resultFileName) {
    QDir directory(directoryName);

    if (directory.exists()) {
        throw "The sample directory does not exist";
    }
    else {
        QStringList samplesInfo = directory.entryList(QStringList("*.png"), QDir::NoFilter, QDir::Name);

    }
}
