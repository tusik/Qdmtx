#include "qdmtxdata.h"
#include <dmtx.h>
#include <QDebug>
QdmtxData::QdmtxData(QObject *parent) : QObject(parent)
{

}

QdmtxData::QdmtxData(const QdmtxData &qdd)
{
    this->dataMatrixs   =   qdd.dataMatrixs;
    this->imgdtx        =   qdd.imgdtx;

}

QString QdmtxData::message(int i)
{
    assert(i < dataMatrixs.size());
    if(i >= dataMatrixs.size())
        return "";
    auto msg = static_cast<DmtxMessage*>(dataMatrixs.at(i).message);
    if(msg!=nullptr){
        return QString::fromStdString((char*)(msg->output));
    }
    return "";
}

int QdmtxData::destory()
{
    while(!dataMatrixs.empty()){

        auto dm = dataMatrixs.front();
        dataMatrixs.pop_front();
        DmtxMessage* m_ptr = static_cast<DmtxMessage*>(dm.message);
        dmtxMessageDestroy(&m_ptr);

        dataMatrixs.pop_front();
        DmtxRegion* r_ptr = static_cast<DmtxRegion*>(dm.reg);
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
