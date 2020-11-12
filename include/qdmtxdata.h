#ifndef QDMTXDATA_H
#define QDMTXDATA_H
#include "Qdmtx_global.h"
#include <assert.h>
#include <QObject>
#include <QVector>
typedef void QdmtxRegion;
typedef void QdmtxMessage;
typedef void QdmtxImage;
class QDMTX_EXPORT QdmtxData : public QObject
{
    Q_OBJECT
public:
    explicit QdmtxData(QObject *parent = nullptr);
    QdmtxData(const QdmtxData& qdd);
    QString message(int i);
    int destory();
    ~QdmtxData();
    QVector<QdmtxRegion*> dataMatrixs;
    QVector<QdmtxMessage*> messages;
public:
    QdmtxImage *imgdtx = nullptr;

signals:

public slots:
};

#endif // QDMTXDATA_H
