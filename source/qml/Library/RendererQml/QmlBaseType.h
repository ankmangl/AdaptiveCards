#pragma once
#include <memory>
#include "QmlTag.h"

using namespace RendererQml;
class QmlBaseType
{
	const std::string mId;
public :
	QmlBaseType(std::string id);
	virtual  std::shared_ptr<QmlTag> getQmlString() = 0;
    virtual void setFont(std::string font) = 0;
    virtual void setHorizontalAlignment(std::string horizontalAlignment) = 0;
    virtual void setVerticalAlignment(std::string verticalAlignment) = 0;
    virtual void setLeftPadding(std::string leftPadding) = 0;
    virtual void setColor(std::string color) = 0;
    virtual void setWrapMode(std::string wrapMode) = 0;
    virtual void setElide(std::string elide) = 0;
};

