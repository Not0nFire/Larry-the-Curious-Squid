#ifndef _BALL_
#define _BALL_

#include "GameEntity.h"


class Ball : public GameEntity {
private:
	const float coefficentOfRestitution;
	//Vector2f m_gravity;
	float time;
	Vector2i screenBounds;
	float m_radius;
	
public:
	Ball(Vector2i screenBounds, Texture* texture, Vector2f position, Vector2f velocity = Vector2f(0,0), Vector2f scale = Vector2f(1,1), float angularVel = 0, float rotation_degrees = 0, float mass = 1);

	~Ball();
	void Update(const Time &elapsedTime, const Vector2f gravity);
	void Death_Reset();
	float GetRadius();
};
#endif