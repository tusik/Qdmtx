#ifndef QDMTX_H
#define QDMTX_H

#include "Qdmtx_global.h"
#include <QImage>
#include <QTime>
#include <QDebug>
class QdmtxData;
class QDMTX_EXPORT Qdmtx
{
public:
    Qdmtx();
    long maxTimeout = 200;


    [[nodiscard]]QdmtxData decodeFromDataMatrix(QImage& pic);
    [[nodiscard]]QdmtxData decodeFromDataMatrix(QString path);
    QImage encodeToDataMatrix(QString& content);

};

#endif // QDMTX_H
