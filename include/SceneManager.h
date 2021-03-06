#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include <unordered_map>
#include "Scene.h"
#include "Level.h"

using namespace std;

//singleton class to handle scenes and the navigation between them
class SceneManager {
private:
	unordered_map<string, I_Scene*> m_scenes;

	string currentScene;

	static SceneManager *m_instance;

	SceneManager() {}

public:
	~SceneManager() {}

	static SceneManager* instance();

	// Gets the name of the current scene.
	const string getCurrentScene() const;

	//get a pointer the the current scene (which allows it to be edited)
	I_Scene * getEditableScene() const;

	// Template function must be defined here or we'll get linker errors.
	// (template function not instantiated until used)
	template<typename T>
	void createScene( string const &name, T* derivedSceneObject ) {
	/*if ( typeid T* != typeid I_Scene* )
		return false;*/

	m_scenes[name] = derivedSceneObject;
	currentScene = name;
	//m_scenes[name]->name = name;
	//m_scenes[name]->dispose = &SceneManager::deleteScene;

	//return true;
	}

	// Calls the current scene's update method
	void updateCurrentScene( sf::Time const &elapsedTime);

	// Calls the current scene's draw method
	void drawCurrentScene( sf::RenderWindow &w );

	// Returns true if no further processing should be done for the event (i.e. the event has been used up )
	bool passEventToCurrentScene( sf::Event &theEvent );

	void navigateToScene( string const &path );
};
#endif