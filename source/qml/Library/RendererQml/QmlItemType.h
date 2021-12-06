#pragma once
#include "QmlBaseType.h"

class QmlItemType :
    public QmlBaseType
{
    std::shared_ptr<QmlTag> mItemType;

public:
    QmlItemType(std::string id);
    std::shared_ptr<QmlTag> getQmlString();

};

