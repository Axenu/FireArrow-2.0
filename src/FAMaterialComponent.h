#ifndef __First__FAMaterialComponent__
#define __First__FAMaterialComponent__

#include <string>
#include <map>

class FAMaterialComponent {

private:
	std::map<std::string, FAMaterialComponent *> requirements;

public:
	FAMaterialComponent();
	~FAMaterialComponent();
	std::string getVertexIO();
	std::string getVertexMain();
	std::string getFragmentIO();
	std::string getFragmentMain();
	std::string getFragmentMainOutput();


protected:

	std::string name;
	std::string vertexIO;
	std::string vertexMain;
	std::string fragmentIO;
	std::string fragmentMain;
	std::string fragmentOutput;

	virtual void setAttribute(std::string name, float value) = 0;
	virtual void bind() = 0;
	
};

class FAVertexColorComponent : public FAMaterialComponent {
public:
	FAVertexColorComponent();
	void setAttribute(std::string name, float value);
	void bind();
};

class FAVertexNormalComponent : public FAMaterialComponent {
public:
	FAVertexNormalComponent();
	void setAttribute(std::string name, float value);
	void bind();
};

#endif