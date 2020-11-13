#ifndef QDMTXDATA_H
#define QDMTXDATA_H
#include "Qdmtx_global.h"
#include <assert.h>
#include <QObject>
#include <QVector>
#include <QList>
typedef void QdmtxRegion;
typedef void QdmtxMessage;
typedef void QdmtxImage;
class QDMTX_EXPORT QdmtxDataStruct{
public:
    QdmtxRegion*    reg         = nullptr   ;
    QdmtxMessage*   message     = nullptr   ;
};
class QDMTX_EXPORT QdmtxData : public QObject
{
    Q_OBJECT
public:
    explicit QdmtxData(QObject *parent = nullptr);
    QdmtxData(const QdmtxData& qdd);
    QString message(int i);
    int destory();
    ~QdmtxData();
    QList<QdmtxDataStruct> dataMatrixs;
public:
    QdmtxImage *imgdtx = nullptr;

signals:

public slots:
};

#endif // QDMTXDATA_H
