#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include "../GL/glew.h"
#include <list>

class Technique
{
public:
	Technique();
	~Technique();
	virtual bool Init();
	void Enable();

protected:
	bool AddShader(GLenum ShaderType, const char* pShaderText);
	bool Linking();
	GLint GetUniformLocation(const char* pUniformName);

private:
	GLuint m_shaderProg;
	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList m_shaderObjList;
};

#endif /* SHADERMANAGER_H */