#ifndef __First__FAMaterialComponent__
#define __First__FAMaterialComponent__

#include <string>

class FAMaterialComponent {

private:
	std::string name;


public:
	FAMaterialComponent();
	~FAMaterialComponent();
	void setAttribute(std::string name, float value);
	void render();
	std::string getVertexInput();
	std::string getVertexOutput();
	std::string getVertexMain();
	std::string getFragmentInput();
	std::string getFragmentOutput();
	std::string getFragmentMain();
	std::string getFragmentMainOutput();
	
};

#endif