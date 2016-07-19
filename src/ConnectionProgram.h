#pragma once

#include "Program.h"

class ConnectionProgram : public virtual Program {
public:
	virtual void setConnection(std::string) override;

protected:
	ConnectionProgram(ProgramStateRef, ci::gl::BatchRef);
	ProgramRef getConnection();

private:
	std::string mConnection;
};