#include "../include/Level.h"
#include "../include/tinyxml2.h"
#include "../include/Ball.h"
#include "../include/Block.h"
#include "../include/BlackHole.h"
#include "../include/PowerUp.h"

using namespace tinyxml2;

std::map<String, Texture> Level::textures = std::map<String, Texture>();

int Level::getID() const {
	return id;
}

void Level::Update() {
	//update all entities in vector
	for(auto itr = m_entities.begin();
		itr != m_entities.end();
		itr++)
	{
		itr->Update();
	}
}

void Level::Draw(RenderWindow &w) {
	//draw all entities in vector
	for(auto itr = m_entities.begin();
		itr != m_entities.end();
		itr++)
	{
		itr->Draw(w);
	}
}

void Level::LoadTexture(String name) {
	if ( textures.find(name) == textures.end() ) {
		//load the texture and add it to the map
		textures[name].loadFromFile("../res/img/" + name);
		}
}


Level Level::LoadFromXML(const char *path) {
	XMLDocument doc;	//empty xml document

	XMLError result = doc.LoadFile(path);	//try to load the xml from file
	if ( result != XML_NO_ERROR )
		throw result;	//throw an error if one occured

	Level tmp_lvl = Level();	//create a temporary level to hold loaded elements

	//query the level id and assign it to the temporary level
	XMLElement* node = doc.FirstChildElement( "LEVEL" )->FirstChildElement( "ID" );
	tmp_lvl.id = atoi(node->GetText());	//atoi converts c string to integer

	//query the gravity force and assign it to the temporary level
	node = doc.FirstChildElement( "LEVEL" )->FirstChildElement( "GRAVITY" );
	Force f = Force( Vector2f(0,0), atof(node->GetText()) );	//atof converts c string to float
	tmp_lvl.m_gravity = Force(f);

	//iterate through all ENTITY elements, creating and adding objects as necessary
	for(XMLElement* node = doc.FirstChildElement( "LEVEL" )->FirstChildElement("ENTITY");
		node != NULL;
		node=node->NextSiblingElement("ENTITY")){

			std::string value = std::string( node->FirstChildElement()->Value() );

			if (value == "BLOCK") {
				//load the block's texture
				String textureName(node->FirstChildElement("TEXTURE")->GetText());
				LoadTexture(textureName);

				//get the position of the block
				XMLElement* positionNode = node->FirstChildElement("POSITION");
				float x = atof(positionNode->FirstChildElement("X")->GetText());
				float y = atof(positionNode->FirstChildElement("Y")->GetText());

				//tmp_lvl.m_entities.push_back( Block() );
			}
			else if (value == std::string("BALL").c_str()) {
				//load the ball's texture
				String textureName( node->FirstChildElement( "TEXTURE" )->Value() );
				LoadTexture( textureName );
				
				//get the position of the ball
				XMLElement* positionNode = node->FirstChildElement( "POSITION" );
				float x = atof( positionNode->FirstChildElement( "X" )->GetText() );
				float y = atof( positionNode->FirstChildElement( "Y" )->GetText() );

				//tmp_lvl.m_entities.push_back( Ball( &textures.find(textureName)->second, Vector2f(x,y) ) );
			}
			else if (value == std::string("BLACKHOLE").c_str()) {
				//get the black hole's texture
				String textureName(node->FirstChildElement("TEXTURE")->Value());
				LoadTexture(textureName);

				//get the position of the black hole
				XMLElement* positionNode = node->FirstChildElement("POSITION");
				float x = atof(positionNode->FirstChildElement("X")->GetText());
				float y = atof(positionNode->FirstChildElement("Y")->GetText());

				//get the angular velocity of the black hole
				float angVel = atof( node->FirstChildElement("ANGULAR_VELOCITY")->GetText() );

				//get the force of the black hole
				Force f = Force(Vector2f(x, y), atof(node->FirstChildElement("POWER")->GetText()));

				//tmp_lvl.m_entities.push_back( BlackHole() );
			}
			else if (value == std::string("POWERUP").c_str()) {
				//get the black hole's texture
				String textureName(node->FirstChildElement("TEXTURE")->GetText());
				LoadTexture(textureName);

				//get the position of the black hole
				XMLElement* positionNode = node->FirstChildElement("POSITION");
				float x = atof(positionNode->FirstChildElement("X")->GetText());
				float y = atof(positionNode->FirstChildElement("Y")->GetText());

				//get the angular velocity of the powerup
				float angVel = atof( node->FirstChildElement("ANGULAR_VELOCITY")->GetText() );

				//tmp_lvl.m_entities.push_back( PowerUp() );
			}
	}//end for loop

	return Level(tmp_lvl);	//return a copy of tmp_lvl (tmp_lvl goes out of scope after this)
}