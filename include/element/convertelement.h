#ifndef CONVERTELEMENT_H
#define CONVERTELEMENT_H

#include "loadelement.h"
#include "virtualelement.h"

/**
 * @brief The ConvertElement class
 *
 */
class ConvertElement
{
  public:
	ConvertElement(LoadElement element);
	~ConvertElement();
	VElement GetElement();

  private:
	VElement new_element;
};

#endif // CONVERTELEMENT_H
