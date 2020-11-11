#ifndef QDMTXDATA_H
#define QDMTXDATA_H
#include "Qdmtx_global.h"
#include <assert.h>
#include <QObject>
#include <dmtx.h>
#include <QVector>
class QDMTX_EXPORT QDmtxData : public QObject
{
    Q_OBJECT
public:
    explicit QDmtxData(QObject *parent = nullptr);
    QDmtxData(const QDmtxData& qdd);
    QString message(int i);
    int destory();
    ~QDmtxData();
    QVector<DmtxRegion*> dataMatrixs;
    QVector<DmtxMessage*> messages;
public:
    DmtxImage *imgdtx = nullptr;

signals:

public slots:
};

#endif // QDMTXDATA_H
