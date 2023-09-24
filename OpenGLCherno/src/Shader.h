#pragma once

#include <string>

class Shader
{
public:
	Shader();
	virtual ~Shader();
	
	bool loadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void unload();

	inline unsigned int getID() const { return m_ID; }

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	
private:
	unsigned int m_ID = 0;
};