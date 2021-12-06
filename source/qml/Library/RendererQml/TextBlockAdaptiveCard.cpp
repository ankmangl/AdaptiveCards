#include "TextBlockAdaptiveCard.h"
#include "MarkDownParser.h"

TextBlockAdaptiveCard::TextBlockAdaptiveCard(std::shared_ptr<AdaptiveCards::TextBlock> textBlock, std::shared_ptr<AdaptiveRenderContext> context)
	:mTextBlock(std::make_shared<QmlTag>("TextEdit"))
{

	mTextBlock->Property("width", "parent.width");
	mTextBlock->Property("clip", "true");
	mTextBlock->Property("textFormat", "Text.RichText");


	std::string horizontalAlignment = AdaptiveCards::EnumHelpers::getHorizontalAlignmentEnum().toString(textBlock->GetHorizontalAlignment());
	mTextBlock->Property("horizontalAlignment", Utils::GetHorizontalAlignment(horizontalAlignment));

	std::string color = context->GetColor(textBlock->GetTextColor(), textBlock->GetIsSubtle(), false);
	mTextBlock->Property("color", color);

	int fontSize = context->GetConfig()->GetFontSize(textBlock->GetFontType(), textBlock->GetTextSize());
	mTextBlock->Property("font.pixelSize", std::to_string(fontSize));
	mTextBlock->Property("font.weight", Utils::GetWeight(textBlock->GetTextWeight()));

	if (!textBlock->GetId().empty())
	{
		textBlock->SetId(context->ConvertToValidId(textBlock->GetId()));
		mTextBlock->Property("id", textBlock->GetId());
	}
	if (!textBlock->GetIsVisible())
	{
		mTextBlock->Property("visible", "false");
	}

	if (textBlock->GetWrap())
	{
		mTextBlock->Property("wrapMode", "Text.Wrap");
	}

	std::string fontFamily = context->GetConfig()->GetFontFamily(textBlock->GetFontType());
	if (!fontFamily.empty())
	{
		mTextBlock->Property("font.family", fontFamily, true);
	}


	std::string text = TextUtils::ApplyTextFunctions(textBlock->GetText(), context->GetLang());
	auto markdownParser = std::make_shared<AdaptiveSharedNamespace::MarkDownParser>(text);
	text = markdownParser->TransformToHtml();
	text = Utils::HandleEscapeSequences(text);
	const std::string linkColor = context->GetColor(AdaptiveCards::ForegroundColor::Accent, false, false);
	//CSS Property for underline, striketrhough,etc
	const std::string textDecoration = "none";
	text = Utils::FormatHtmlUrl(text, linkColor, textDecoration);
	mTextBlock->Property("text", text, true);


	std::string onLinkActivatedFunction = Formatter() << "{"
		<< "adaptiveCard.buttonClicked(\"\", \"Action.OpenUrl\", link);"
		<< "console.log(link);"
		<< "}";
	mTextBlock->Property("onLinkActivated", onLinkActivatedFunction);

	std::string textType = textBlock->GetElementTypeString();
	//ElideRight and MaxLine Count not supported
	//MouseArea to Change Cursor on Hovering Links
	mTextBlock->AddChild(this->GetTextBlockMouseArea());
	AddAccessibilityToTextBlock(context->GetRenderConfig()->getCardConfig());
}


std::shared_ptr<QmlTag> TextBlockAdaptiveCard::GetTextBlockMouseArea()
{
	auto MouseAreaTag = std::make_shared<QmlTag>("MouseArea");
	MouseAreaTag->Property("anchors.fill", "parent");
	MouseAreaTag->Property("cursorShape", "parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor");
	MouseAreaTag->Property("acceptedButtons", "Qt.NoButton");
	return MouseAreaTag;
}

void TextBlockAdaptiveCard::AddAccessibilityToTextBlock(RendererQml::CardConfig cardConfig)
{
	mTextBlock->Property("property string accessibleText", "getText(0, length)");
	mTextBlock->Property("property string link", "", true);
	mTextBlock->Property("activeFocusOnTab", "true");
	mTextBlock->Property("Accessible.name", "accessibleText");
	mTextBlock->Property("readOnly", "true");
	mTextBlock->Property("selectByMouse", "false");
	mTextBlock->Property("selectByKeyboard", "false");
	mTextBlock->Property("Keys.onPressed", Formatter() << "{"
		<< "if (event.key === Qt.Key_Tab) {event.accepted = selectLink(this, true);}"
		<< "else if (event.key === Qt.Key_Backtab) {event.accepted = selectLink(this, false);}"
		<< " else if (event.key == Qt.Key_Return || event.key == Qt.Key_Enter || event.key == Qt.Key_Space) { if (link) {linkActivated(link);} event.accepted = true;}}");

	mTextBlock->Property("onSelectedTextChanged", Formatter() << "{"
		<< "if (link) { accessibleText = selectedText + ' has link,' + link + '. To activate press space bar.';}"
		<< "else {accessibleText = ''}}");

	mTextBlock->Property("onActiveFocusChanged", Formatter() << "{"
		<< "if (activeFocus) { accessibleText = getText(0,length);}}");

	auto uiFocusRectangle = std::make_shared<QmlTag>("Rectangle");
	uiFocusRectangle->Property("anchors.fill", "parent");
	uiFocusRectangle->Property("color", "transparent", true);
	uiFocusRectangle->Property("border.width", "parent.activeFocus ? 1 : 0");
	uiFocusRectangle->Property("border.color", Formatter() << "parent.activeFocus ? '" << cardConfig.focusRectangleColor << "' : 'transparent'");
	mTextBlock->AddChild(uiFocusRectangle);
}


std::shared_ptr<QmlTag> TextBlockAdaptiveCard::getQmlString() {
	return mTextBlock;
}
