#include "CombinatorProgram.h"
#include "ConnectionProgram.h"

void ConnectionProgram::setConnection(std::string)
{
}

ConnectionProgram::ConnectionProgram(ProgramStateRef)
{
}

ProgramRef ConnectionProgram::getConnection()
{
	return ProgramRef();
}
