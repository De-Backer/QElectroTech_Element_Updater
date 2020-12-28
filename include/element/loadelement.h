#ifndef LOADELEMENT_H
#define LOADELEMENT_H

#include <QFile>
#include <QString>
#include <QUuid>
#include <QVariant>
#include <QXmlStreamReader>

class LoadElement
{
  public:
	LoadElement(QString file);
	QVariant definition(QString value);
	QUuid	 uuid();
	QString	 name(QString value);
	QVariant kindInformation(QString value);
	QString	 informations();

  private:
	int				  width		   = 0;
	int				  height	   = 0;
	int				  hotspot_x	   = 0;
	int				  hotspot_y	   = 0;
	QString			  type		   = "todo"; // wat is de def?
	QString			  link_type	   = "todo"; // wat is de def?
	QUuid			  uuid_element = QUuid::createUuid();
	QFile*			  element;
	QXmlStreamReader* Reader;
	void			  LoadElement0_3_0(QXmlStreamReader* reader);
	void			  LoadElement0_7_0(QXmlStreamReader* reader);
};

#endif // LOADELEMENT_H
