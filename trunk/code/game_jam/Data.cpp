#include "Data.h"


Data::Data()
{
}


Data::~Data()
{
}
Data* Data::GetInstance()
{
	static Data data;
	return &data;
}
