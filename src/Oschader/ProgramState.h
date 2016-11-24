#pragma once

#include "InputResolver.h"

class ProgramFactory;
class Program;

class ProgramState;
typedef std::shared_ptr<ProgramState> ProgramStateRef;

class ProgramState {
public:
	void update(std::function<void(std::shared_ptr<Program>)> updateFn);
	void setProgram(std::string id, std::string name, std::function<std::shared_ptr<Program>()>);
	void clearProgram(std::string id);
	std::shared_ptr<Program> getProgram(std::string id);
	
private:
	std::map<std::string, std::pair<std::string, std::shared_ptr<Program>>> mState;
};