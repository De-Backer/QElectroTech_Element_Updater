#ifndef LOADELEMENT_H
#define LOADELEMENT_H

#include <QFile>
#include <QMap>
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
	QString	 name(QString language);
	QVariant kindInformation(QString value);
	QString	 informations();

  private:
	int					   width		= 0;
	int					   height		= 0;
	int					   hotspot_x	= 0;
	int					   hotspot_y	= 0;
	QString				   type			= "todo"; // wat is de def?
	QString				   link_type	= "todo"; // wat is de def?
	QUuid				   uuid_element = QUuid::createUuid();
	QMap<QString, QString> name_element;
	QString				   informations_element;
	QFile*				   element;
	void				   LoadElement0_22(QXmlStreamReader* reader);
	void				   LoadElement0_3(QXmlStreamReader* reader);
	void				   LoadElement0_4(QXmlStreamReader* reader);
	void				   LoadElement0_5(QXmlStreamReader* reader);
	void				   LoadElement0_60(QXmlStreamReader* reader);
	void				   LoadElement0_70(QXmlStreamReader* reader);
	void				   LoadElement0_80(QXmlStreamReader* reader);
};

#endif // LOADELEMENT_H
