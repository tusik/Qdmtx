#include "qdmtxdata.h"

QdmtxData::QdmtxData(QObject *parent) : QObject(parent)
{

}

QdmtxData::QdmtxData(const QdmtxData &qdd)
{
    this->messages      =   qdd.messages;
    this->dataMatrixs   =   qdd.dataMatrixs;
    this->imgdtx        =   qdd.imgdtx;

}

QString QdmtxData::message(int i)
{
    assert(i < messages.size());
    if(i < messages.size())
        return "";

    std::string _msg(reinterpret_cast<char*>(messages.at(i)->output));

    return QString::fromStdString(_msg);
}

int QdmtxData::destory()
{
    while(!messages.empty()){

        auto msg = messages.front();
        messages.pop_front();
        dmtxMessageDestroy(&msg);

        auto reg = dataMatrixs.front();
        dataMatrixs.pop_front();
        dmtxRegionDestroy(&reg);

    }
    dmtxImageDestroy(&imgdtx);
    return 0;
}

QdmtxData::~QdmtxData()
{
//    dmtxMessageDestroy(&msg);

//    dmtxRegionDestroy(&reg);

//    dmtxImageDestroy(&imgdtx);
}
