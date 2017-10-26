///This class was made my Callum Flannagan

#include "primitiveType.h"


const std::string ASSET_PATH = "../assets/";
const std::string SHADER_PATH = "shaders/";
const std::string TEXTURE_PATH = "textures/";
const std::string FONT_PATH = "fonts/";
const std::string MODEL_PATH = "models/";

Vertex triangleData[] =
{
	{ vec3(-0.5f, 0.5f, 0.5f), vec3(0.25f, 0.25f, 0.5f), vec2(0.0f, 0.0f) },// Top Left
	{ vec3(-0.5f, -0.5f, 0.5f), vec3(0.25f, 0.25f, 0.5f), vec2(0.0f, 1.0f) },// Bottom Left
	{ vec3(0.5f, -0.5f, 0.5f), vec3(0.25f, -0.25f, 0.5f), vec2(1.0f, 1.0f) }, //Bottom Right
	{ vec3(0.5f, 0.5f, 0.5f), vec3(0.25f, -0.25f, 0.5f), vec2(1.0f, 0.0f) },// Top Right


	//back
	{ vec3(-0.5f, 0.5f, -0.5f), vec3(0.25f, 0.25f, -0.5f), vec2(0.0f, 0.0f) },// Top Left
	{ vec3(-0.5f, -0.5f, -0.5f), vec3(0.25f, 0.25f, -0.5f), vec2(0.0f, 1.0f) },// Bottom Left
	{ vec3(0.5f, -0.5f, -0.5f), vec3(0.25f, -0.25f, -0.5f), vec2(1.0f, 1.0f) }, //Bottom Right
	{ vec3(0.5f, 0.5f, -0.5f), vec3(0.25f, -0.25f, -0.5f), vec2(1.0f, 0.0f), }// Top Right
};

Vertex triangleData2[] =
{
	{ vec3(0.5f, 0.5f, 0.5f), vec3(0.25f, -0.25f, 0.5f), vec2(1.0f, 0.0f) },// Top Right
	{ vec3(-0.5f, 0.5f, 0.5f), vec3(0.25f, 0.25f, 0.5f), vec2(0.0f, 0.0f) },// Top Left
	{ vec3(-0.5f, 0.5f, -0.5f), vec3(0.25f, 0.25f, -0.5f), vec2(0.0f, 0.0f) },// Top Left
	{ vec3(0.5f, 0.5f, -0.5f), vec3(0.25f, -0.25f, -0.5f), vec2(1.0f, 0.0f), }// Top Right
};

//GLuint planeindices[] = {
//		//front
//		0, 1, 2,
//		0, 3, 2
//	};

GLuint planeindices[] = {
	//front
	3, 0, 4,
	3, 8, 4
};

//GLuint triangleIndices[];

//GLuint m_indices[];

GLuint cubeIndices[] = {
	//front
	0, 1, 2,
	0, 3, 2,

	//left
	4, 5, 1,
	4, 1, 0,

	//right
	3, 7, 2,
	7, 6, 2,

	//bottom
	1, 5, 2,
	6, 2, 1,

	//top
	5, 0, 7,
	5, 7, 3,

	//back
	4, 5, 6,
	4, 7, 6
};

primitiveType::primitiveType()
{

}

primitiveType::~primitiveType(){

}



//Allow's you to create a shape at a given position
void primitiveType::createPrimitive(shaderType type, vec3 position, vec3 rotation, vec3 scaling)
{
	GameObject* objectShape = new GameObject();
	Transform* transform = new Transform();
	Mesh *mesh = new Mesh();

	determineShader(type);
	
	std::string vsPath = ASSET_PATH + SHADER_PATH + shaderFilenameVS;
	std::string fsPath = ASSET_PATH + SHADER_PATH + shaderFilenameFS;
	materialPrimitive->loadShader(vsPath, fsPath);

	objectShape->setMaterial(materialPrimitive);
	objectShape->setMesh(mesh);

	transform->setPosition(position.x, position.y, position.z);
	transform->setRotation(rotation.x, rotation.y, rotation.z);
	transform->setScale(scaling.x, scaling.y, scaling.z);
	objectShape->setTransform(transform);
	displayList.push_back(objectShape);

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->init();
		(*iter)->getMesh()->copyVertexData(8, sizeof(Vertex), (void**)triangleData);
		(*iter)->getMesh()->copyIndexData(36, sizeof(int), (void**)planeindices);
	}
}

void primitiveType::setPrimitiveTexture(std::string diffTexturePath, std::string specTexturePath, std::string bumpTexturePath){

	diffuseArray.push_back(diffTexturePath);
	specularArray.push_back(specTexturePath);
	bumpArray.push_back(bumpTexturePath);

	for (int i = 0; i < diffuseArray.size(); i++) {

		materialPrimitive = new Material();

		std::string diffTexturePath = ASSET_PATH + TEXTURE_PATH + diffuseArray[i];
		std::string specTexturePath = ASSET_PATH + TEXTURE_PATH + specularArray[i];
		std::string bumpTexturePath = ASSET_PATH + TEXTURE_PATH + bumpArray[i];

		materialPrimitive->loadDiffuseMap(diffTexturePath);
		materialPrimitive->loadSpecularMap(specTexturePath);
		materialPrimitive->loadBumpMap(bumpTexturePath);
	}
}

//Sets the directories for bump mapping
void primitiveType::setModelsBump(std::string modelFilename, std::string diffTexturePath,
	std::string specTexturePath, std::string bumpTexturePath){

	fileArray.push_back(modelFilename);
	diffuseArray.push_back(diffTexturePath);
	specularArray.push_back(specTexturePath);
	bumpArray.push_back(bumpTexturePath);
}

//Sets the directories for parrallax mapping
void primitiveType::setModelsParrallax(std::string modelFilename, std::string diffTexturePath,
	std::string specTexturePath, std::string bumpTexturePath, std::string heightMapPath){

	fileArray.push_back(modelFilename);
	diffuseArray.push_back(diffTexturePath);
	specularArray.push_back(specTexturePath);
	bumpArray.push_back(bumpTexturePath);
	heightArray.push_back(heightMapPath);
}

//Sets the transformations for models
void primitiveType::setTransformation(vec3 position, vec3 rotation, vec3 scaling){

	m_position.push_back(position);
	m_rotation.push_back(rotation);
	m_scaling.push_back(scaling);
}

//loads the models
void primitiveType::loadModels(shaderType type){

	for (int i = 0; i < fileArray.size(); i++) {

		std::string modelPath = ASSET_PATH + MODEL_PATH + fileArray[i];
		std::string diffTexturePath = ASSET_PATH + TEXTURE_PATH + diffuseArray[i];
		std::string specTexturePath = ASSET_PATH + TEXTURE_PATH + specularArray[i];
		std::string bumpTexturePath = ASSET_PATH + TEXTURE_PATH + bumpArray[i];

		determineShader(type);

		if (type == parralax)
			heightTexturePath = ASSET_PATH + TEXTURE_PATH + heightArray[i];

		GameObject * go = loadFBXFromFile(modelPath);

		for (int b = 0; b < go->getChildCount(); b++)
		{
			go->setName("a");
			Material * material = new Material();
			material->init();

			std::string vsPath = ASSET_PATH + SHADER_PATH + shaderFilenameVS;
			std::string fsPath = ASSET_PATH + SHADER_PATH + shaderFilenameFS;
			material->loadShader(vsPath, fsPath);

			material->loadDiffuseMap(diffTexturePath);
			material->loadSpecularMap(specTexturePath);
			material->loadBumpMap(bumpTexturePath);

			if (type == parralax)
				material->loadHeightMap(heightTexturePath);

			go->getChild(b)->setMaterial(material);
		}

		go->getTransform()->setRotation(m_rotation[i].x, m_rotation[i].y, m_rotation[i].z);
		go->getTransform()->setScale(m_scaling[i].x, m_scaling[i].y, m_scaling[i].z);
		go->getTransform()->setPosition(m_position[i].x, m_position[i].y, m_position[i].z);
		displayList.push_back(go);
	}
}

//Determines which shader to use (assigns shader filepath)
void primitiveType::determineShader(shaderType type){

	switch (type){

	case parralax:
		shaderFilenameVS = "/ParallaxMappingVS.glsl";
		shaderFilenameFS = "/ParallaxMappingFS.glsl";
		break;
	case bump:
		shaderFilenameVS = "/BumpmappingVS.glsl";
		shaderFilenameFS = "/BumpmappingFS.glsl";
		break;
	case directionalLight:
		shaderFilenameVS = "/DirectionalLightTextureVS.glsl";
		shaderFilenameFS = "/DirectionalLightTextureFS.glsl";
		break;
	case texturing:
		shaderFilenameVS = "/textureVS.glsl";
		shaderFilenameFS = "/textureFS.glsl";
		break;
	case point:
		shaderFilenameVS = "/pointLightVS.glsl";
		shaderFilenameFS = "/pointLightFS.glsl";
		break;
	default:
		break;
	}
}


std::vector<GameObject*> primitiveType::getDisplayList(){
	return displayList;
}

void primitiveType::setDisplaylist(std::vector<GameObject*> List){
	for (int i = 0; i < List.size(); i++){
		displayList.push_back(List[i]);
	}
}
///This class was made my Callum Flannagan
