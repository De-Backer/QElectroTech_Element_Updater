#include "convertelement.h"

ConvertElement::ConvertElement(LoadElement element)
{
	//	element.definition().value("version", "! no version
	// gevonden").toString();
	// verander naar het new element
	new_element.definition(element.definition());
	new_element.description(element.description());
	new_element.elementInformations(element.elementInformations());
	new_element.informations(element.informations());
	new_element.kindInformation(element.kindInformation());
	new_element.name(element.name());
	new_element.uuid(element.uuid());
}

ConvertElement::~ConvertElement() {}

VElement ConvertElement::GetElement() { return new_element; }
