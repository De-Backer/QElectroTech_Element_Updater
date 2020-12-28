#include "loadelement.h"

#include <QUuid>
#include <QtDebug>
#include <catch2/catch.hpp>

TEST_CASE("LoadElement 0.3.0", "0.3.0")
{
	LoadElement mytest(TEST_CATCH_PATH "/testfile_0_3_0.elmt");
	CHECK(10 == mytest.definition("width").toInt());
	CHECK(30 == mytest.definition("height").toInt());
	CHECK(5 == mytest.definition("hotspot_x").toInt());
	CHECK(0 == mytest.definition("hotspot_y").toInt());
	CHECK("element" == mytest.definition("type").toString().toStdString());
	// no link_type
	// Todo wat moet dit zijn def?
	CHECK("" == mytest.definition("link_type").toString().toStdString());
	// no version in definition but in file => version="0.3"
	// Todo wat moet dit zijn?
	REQUIRE_THROWS_WITH(mytest.definition("version"), "unknown value");

	// Todo een beter manier vinden voor random waarden
	REQUIRE_THROWS_WITH(mytest.definition("definition"), "unknown value");
	REQUIRE_THROWS_WITH(mytest.definition("name"), "unknown value");
	REQUIRE_THROWS_WITH(mytest.definition("description"), "unknown value");
	CHECK(
		QUuid("0EE598EC-C72A-43A3-B330-741E2D41940A").toString().toStdString()
		== mytest.uuid().toString().toStdString());
}
