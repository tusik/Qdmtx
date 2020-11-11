#include "qdmtx.h"
#include "qdmtxdata.h"
#include <QDir>
Qdmtx::Qdmtx()
{
}

QDmtxData Qdmtx::decodeFromDataMatrix(QImage &pic)
{
    QDmtxData qdd;
    //简化版本
    QTime time;
    QString outstr;

    time.start();//qt开始计时
    qDebug()<<"src.format() "<<pic.format();//注意图片格式要对应 dmtxImageCreate的 不然无法解码

    // 增加超时时间。
    DmtxTime beginTime = dmtxTimeNow();	// 根据系统设置情况，获得当前时间

    DmtxTime stopTime = dmtxTimeAdd(beginTime, maxTimeout);	// 增加xx ms

    //创建dmtxImage，将qt读取到的图片存储到dmtxImage
    qdd.imgdtx = dmtxImageCreate(pic.bits(),pic.width(),pic.height(),DmtxPack32bppXRGB);
    assert(qdd.imgdtx != NULL);
    DmtxDecode *dec = dmtxDecodeCreate(qdd.imgdtx, 1);//解码
    assert(dec != NULL);
    DmtxRegion *reg = nullptr;
    while((reg = dmtxRegionFindNext(dec,&stopTime)) != nullptr){
        //查找下一个，如果超时则认为没有找到

        if(dmtxTimeExceeded(stopTime))
        {
            qDebug()<<"超时";
        }
        else
        {
            if (reg != nullptr)
            {
                qdd.dataMatrixs.push_back(reg);
                auto msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);//获取解码信息
                qdd.messages.push_back(msg);
                if (msg != nullptr)
                {
                    qDebug() << msg->output << endl;//输出解码信息
                    qDebug() << msg->outputIdx << endl;

                    //qt输出解码信息string->QString
                    std::string strout = (char*)msg->output;//解码信息
                    outstr=QString::fromStdString(strout);
                    qDebug()<<"解码信息:"<<outstr;//解码信息
                    qDebug()<<"解码信息xx:"<<msg->output;//解码信息

                    //二维码坐标信息
                    qDebug()<<"reg->leftLine.locPos.X "<<reg->leftLine.locPos.X;
                    qDebug()<<"reg->leftLine.locPos.Y "<<reg->leftLine.locPos.Y;
                    qDebug()<<"reg->leftLine.locNeg.X "<<reg->leftLine.locNeg.X;
                    qDebug()<<"reg->leftLine.locNeg.Y "<<reg->leftLine.locNeg.Y;
                    qDebug()<<"bottomLine.locPos.X "<<reg->bottomLine.locPos.X;
                    qDebug()<<"bottomLine.locPos.Y "<<reg->bottomLine.locPos.Y;
                    qDebug()<<"bottomLine.locNeg.X "<<reg->bottomLine.locNeg.X;
                    qDebug()<<"bottomLine.locNeg.y "<<reg->bottomLine.locNeg.Y;

                }
                else{qDebug()<<"无法检测到2";}
            }
            else{qDebug()<<"无法检测到1";}
        }
        qDebug()<<time.elapsed()/1000.0<<"s";
    }

    return qdd;
}

QDmtxData Qdmtx::decodeFromDataMatrix(QString path)
{
    QDmtxData qdd;
    assert(QFile(path).exists());
    QImage src(path);//路径
    return decodeFromDataMatrix(src);
}

QImage Qdmtx::encodeToDataMatrix(QString &content)
{
//    QTime time;
//    time.start();
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
//    qDebug()<<time.elapsed()/1000.0<<"s";
//    uchar *pxlData = (uchar *)malloc(width*height*bytesPerPixel);
//    memcpy(pxlData,enc->image->pxl,width*height*bytesPerPixel);

//    qDebug()<<time.elapsed()/1000.0<<"s";
    QImage img ;
    img=QImage(enc->image->pxl,width,height,bytesPerLine,QImage::Format_RGB888).copy();
//    qDebug()<<time.elapsed()/1000.0<<"s";
    dmtxEncodeDestroy(&enc);
    return img;
}
