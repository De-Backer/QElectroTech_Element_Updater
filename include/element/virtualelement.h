#ifndef VIRTUALELEMENT_H
#define VIRTUALELEMENT_H

#include <QMap>
#include <QString>
#include <QUuid>
#include <QVariant>
#include <QVector>

class VElement
{
  public:
	VElement();
	~VElement();
	QMap<QString, QVariant>			 definition();
	QUuid							 uuid();
	QMap<QString, QString>			 name();
	QMap<QString, QVector<QVariant>> kindInformation();
	QMap<QString, QVector<QVariant>> elementInformations();
	QString							 informations();
	QVector<QMap<QString, QVariant>> description();

  private:
	QMap<QString, QVariant>							Definition;
	QUuid											Uuid;
	QMap<QString, QString>							Name;
	QMap<QString, QVector<QVariant>>				KindInformation;
	QMap<QString, QVector<QVariant>>				ElementInformations;
	QString											Informations;
	QMap<QString, QVector<QMap<QString, QVariant>>> Description;
	// type, list of type{antialias,var}
};

#endif // VIRTUALELEMENT_H
