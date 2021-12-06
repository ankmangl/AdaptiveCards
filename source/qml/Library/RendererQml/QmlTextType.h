#pragma once
#include "QmlBaseType.h"
#include "QmlItemtype.h"

class QmlTextType :
    public QmlItemType
{
    std::shared_ptr<QmlTag> mTextType;

public:
    QmlTextType(std::string id, std::shared_ptr<QmlTag> textType, std::string text);
    std::shared_ptr<QmlTag> getQmlString();
    void setFont(std::string font);
    void setHorizontalAlignment(std::string horizontalAlignment);
    void setVerticalAlignment(std::string verticalAlignment);
    void setLeftPadding(std::string leftPadding);
    void setColor(std::string color);
    void setWrapMode(std::string wrapMode);
    void setElide(std::string elide);
};

