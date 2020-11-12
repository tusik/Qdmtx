﻿#include "qdmtx.h"
#include "qdmtxdata.h"
#include <QDir>
Qdmtx::Qdmtx()
{
}

QdmtxData Qdmtx::decodeFromDataMatrix(QImage &pic)
{
    QdmtxData qdd;

    QTime time;
    QString outstr;

    time.start();
    qDebug()<<"src.format() "<<pic.format();


    DmtxTime beginTime = dmtxTimeNow();

    DmtxTime stopTime = dmtxTimeAdd(beginTime, maxTimeout);

    qdd.imgdtx = dmtxImageCreate(pic.bits(),pic.width(),pic.height(),DmtxPack32bppXRGB);
    assert(qdd.imgdtx != NULL);
    DmtxDecode *dec = dmtxDecodeCreate(qdd.imgdtx, 1);
    assert(dec != NULL);
    DmtxRegion *reg = nullptr;
    while((reg = dmtxRegionFindNext(dec,&stopTime)) != nullptr){

        if(dmtxTimeExceeded(stopTime))
        {
            qDebug()<<"datamatrix decode timeout.";
        }
        else
        {
            if (reg != nullptr)
            {
                qdd.dataMatrixs.push_back(reg);
                auto msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);
                qdd.messages.push_back(msg);
                if (msg != nullptr)
                {


                }
                else
                {
                    qDebug()<<"Null messages.";
                }
            }
            else
            {
                qDebug()<<"Null region found.";
            }
        }
        qDebug()<<time.elapsed()/1000.0<<"s";
    }
    dmtxDecodeDestroy(&dec);
    return qdd;
}

QdmtxData Qdmtx::decodeFromDataMatrix(QString path)
{
    QdmtxData qdd;
    assert(QFile(path).exists());
    QImage src(path);
    return decodeFromDataMatrix(src);
}

QImage Qdmtx::encodeToDataMatrix(QString &content)
{
    assert(content.size()<=256);
    DmtxEncode     *enc;
    enc = dmtxEncodeCreate();

    enc->sizeIdxRequest=DmtxSymbolSquareAuto;
    assert(enc != NULL);
    auto str = content.toStdString();
    char *tempChar = const_cast<char*>(str.c_str());
    unsigned char *tempChar1 = reinterpret_cast<unsigned char*>(tempChar);
    dmtxEncodeDataMatrix(enc, static_cast<int>(str.size()), tempChar1);
    int width = dmtxImageGetProp(enc->image, DmtxPropWidth);
    int height = dmtxImageGetProp(enc->image, DmtxPropHeight);
    int bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);
    int bytesPerLine = dmtxImageGetProp(enc->image, DmtxPropRowSizeBytes);

    QImage img ;
    img=QImage(enc->image->pxl,width,height,bytesPerLine,QImage::Format_RGB888).copy();

    dmtxEncodeDestroy(&enc);
    return img;
}
