#include "QmlItemType.h"


QmlItemType::QmlItemType(std::string id) :
	QmlBaseType(id)
{
	
}

std::shared_ptr<QmlTag> QmlItemType::getQmlString()
{
	return mItemType;
}
