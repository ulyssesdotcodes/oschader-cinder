#include "ConnectionProgram.h"

void ConnectionProgram::setConnection(std::string c)
{
	mConnection = c;
}

ConnectionProgram::ConnectionProgram(ProgramStateRef state, ci::gl::BatchRef b) : Program(b, state)
{
}

ProgramRef ConnectionProgram::getConnection()
{
	return getProgram(mConnection);
}
