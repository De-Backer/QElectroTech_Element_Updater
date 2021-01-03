#include "convertelement.h"

ConvertElement::ConvertElement(LoadElement element)
{
	element.definition().value("version", "! no version gevonden").toString();
	// verander naar het new element
}

ConvertElement::~ConvertElement() {}

VElement ConvertElement::GetElement() { return new_element; }
