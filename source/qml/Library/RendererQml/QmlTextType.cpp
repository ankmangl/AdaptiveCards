#include "QmlTextType.h"

QmlTextType::QmlTextType(std::string id, std::shared_ptr<QmlTag> textType, std::string text) :
	QmlItemType(id),
	mTextType(textType)
{
	mTextType->Property("text", text);
}

std::shared_ptr<QmlTag> QmlTextType::getQmlString()
{
	 return mTextType;
}

 void QmlTextType::setFont(std::string font)
 {
	 mTextType->Property("font", font);
 }
 void QmlTextType::setHorizontalAlignment(std::string horizontalAlignment)
 {
	 mTextType->Property("horizontalAlignment", horizontalAlignment);
 }
 void QmlTextType::setVerticalAlignment(std::string verticalAlignment)
 {
	 mTextType->Property("verticalAlignment", verticalAlignment);
 }
 void QmlTextType::setLeftPadding(std::string leftPadding)
 {
	 mTextType->Property("leftPadding", leftPadding);
 }
 void QmlTextType::setColor(std::string color)
 {
	 mTextType->Property("color", color);
 }
 void QmlTextType::setWrapMode(std::string wrapMode)
 {
	 mTextType->Property("wrapMode", wrapMode);
 }
 void QmlTextType::setElide(std::string elide)
 {
	 mTextType->Property("elide", elide);
 }

