#include <QStringList>
#include <QFileInfo>
#include <QFileInfoList>

#include "SampleSet.hpp"

SampleSet::SampleSet(const QDir &directory) {
    if (!directory.exists()) {
        throw "The sample directory does not exist";
    }
    else {
        QFileInfoList samplesInfo = directory.entryInfoList(QStringList("*.png"));
        QFileInfoList answersInfo = directory.entryInfoList(QStringList("*.idl"));

        if (samplesInfo.count() + answersInfo.count() != directory.entryList(QDir::NoDotAndDotDot).count()) {
            throw "Wrong format of sample directory";
        }
        else {

        }
    }
}
