#pragma once
#include "QmlTextType.h"
#include "AdaptiveCardQmlRenderer.h"
#include "TextBlock.h"

class TextBlockAdaptiveCard
{
	std::shared_ptr<QmlTag> mTextBlock;
public :
	TextBlockAdaptiveCard(std::shared_ptr<AdaptiveCards::TextBlock> textBlock, std::shared_ptr<AdaptiveRenderContext> context);
	static std::shared_ptr<QmlTag> GetTextBlockMouseArea();
	void AddAccessibilityToTextBlock(RendererQml::CardConfig cardConfig);
	std::shared_ptr<QmlTag> getQmlString();
};

