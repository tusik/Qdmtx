#ifndef QDMTXDATA_H
#define QDMTXDATA_H
#include "Qdmtx_global.h"
#include <assert.h>
#include <QObject>
#include <dmtx.h>
#include <QVector>
class QDMTX_EXPORT QdmtxData : public QObject
{
    Q_OBJECT
public:
    explicit QdmtxData(QObject *parent = nullptr);
    QdmtxData(const QdmtxData& qdd);
    QString message(int i);
    int destory();
    ~QdmtxData();
    QVector<DmtxRegion*> dataMatrixs;
    QVector<DmtxMessage*> messages;
public:
    DmtxImage *imgdtx = nullptr;

signals:

public slots:
};

#endif // QDMTXDATA_H
