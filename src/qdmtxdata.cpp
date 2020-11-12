#include "qdmtxdata.h"
#include <dmtx.h>
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

    std::string _msg(reinterpret_cast<char*>(static_cast<DmtxMessage*>(messages.at(i))->output));

    return QString::fromStdString(_msg);
}

int QdmtxData::destory()
{
    while(!messages.empty()){

        auto msg = messages.front();
        messages.pop_front();
        DmtxMessage* m_ptr = static_cast<DmtxMessage*>(msg);
        dmtxMessageDestroy(&m_ptr);

        auto reg = dataMatrixs.front();
        dataMatrixs.pop_front();
        DmtxRegion* r_ptr = static_cast<DmtxRegion*>(reg);
        dmtxRegionDestroy(&r_ptr);

    }
    DmtxImage* i_ptr = static_cast<DmtxImage*>(imgdtx);
    dmtxImageDestroy(&i_ptr);
    return 0;
}

QdmtxData::~QdmtxData()
{
//    dmtxMessageDestroy(&msg);

//    dmtxRegionDestroy(&reg);

//    dmtxImageDestroy(&imgdtx);
}
