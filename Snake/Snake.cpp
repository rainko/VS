// Snake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int num_horzBox = 30, num_vertBox = 20;
int size = 16;
int w = size * num_horzBox;
int h = size * num_vertBox;

int direction, direction2, snake_length = 4, snake2_length = 4;

struct Snake {
	int x, y;

}s[100];

struct Snake2 {
	int x, y;

}s2[100];

struct Fruit {
	int x, y;
}food;


void Tick() {
	//Move remaining pieces of snake s[1] - s[99]

	for (int i = snake_length; i > 0; --i) {
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	for (int i = snake2_length; i > 0; --i) {
		s2[i].x = s2[i - 1].x;
		s2[i].y = s2[i - 1].y;
	}


	//Head of the snake depends on direction of user s[0]

	//User Up
	if (direction == 3)
		s[0].y -= 1;
	//Down
	if (direction == 0)
		s[0].y += 1;
	//Left
	if (direction == 1)
		s[0].x -= 1;
	//Right
	if (direction == 2)
		s[0].x += 1;


	//User 2
	if (direction2 == 3)
		s2[0].y -= 1;
	//Down
	if (direction2 == 0)
		s2[0].y += 1;
	//Left
	if (direction2 == 1)
		s2[0].x -= 1;
	//Right
	if (direction2 == 2)
		s2[0].x += 1;



	//If Snake eats food it should grow
	if (s[0].x == food.x && s[0].y == food.y) {
		snake_length++;
		

		//Randomly placed food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;

	}

	if (s2[0].x == food.x && s2[0].y == food.y) {
		snake2_length++;


		//Randomly placed food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;

	}


	//Boundary Checking  screen loop back ton other side
	if (s[0].x > num_horzBox)
		s[0].x = 0;

	if (s[0].x < 0)
		s[0].x = num_horzBox;


	//Top and bottom
	if (s[0].y > num_vertBox)
		s[0].y = 0;

	if (s[0].y < 0)
		s[0].y = num_vertBox;

	//Check if go over snake
	for (int i = 1; i < snake_length; i++) {
		//Cut snake i half from place eaten
		if (s[0].x == s[i].x && s[0].y == s[i].y || s[0].x == s2[i].x && s[0].y == s2[i].y){
			snake2_length = i;
		}
	}


	//Boundary Checking  screen loop back ton other side
	if (s2[0].x > num_horzBox)
		s2[0].x = 0;

	if (s2[0].x < 0)
		s2[0].x = num_horzBox;


	//Top and bottom
	if (s2[0].y > num_vertBox)
		s2[0].y = 0;

	if (s2[0].y < 0)
		s2[0].y = num_vertBox;

	for (int i = 1; i < snake2_length; i++) {
		//Cut snake i half from place eaten
		if (s2[0].x == s2[i].x && s2[0].y == s2[i].y || s2[0].x == s[i].x && s2[0].y == s[i].y) {
			snake_length = i;
		}
	}



}

int main() {

	srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake Game!");

	//Textures
	Texture t1, t2, t3, t4;

	t1.loadFromFile("Image/white.png");
	t2.loadFromFile("Image/red.png");
	t3.loadFromFile("Image/fruit.png");
	t4.loadFromFile("Image/green.png");


	//Sprite
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Sprite sprite4(t4);

	food.x = 10;
	food.y = 10;


	Clock clock;
	float timer = 0, delay = 0.1;



	while (window.isOpen()) {

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//increase speed of snake for length > 4
		if(snake_length > 4) {
			delay = 0.1 - ((snake_length / 2) * 0.01);
		}
		else
			delay = 0.1;


		//increase speed of snake for length > 4
		if (snake2_length > 4) {
			delay = 0.1 - ((snake2_length / 2) * 0.01);
		}
		else
			delay = 0.1;



		// Allow us to check when a user does something
		Event e;

		//check when window is closed
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}


		//Controls for snake movement
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			direction = 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			direction = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) { 
			direction = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) { 
			direction = 2;
		}

		//Controls for snake2 movement
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			direction2 = 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			direction2 = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			direction2 = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			direction2 = 2;
		}



		if (timer > delay) {
			timer = 0; //reset timer
			Tick(); //move snake one sprite forward
		}

		//Draw
		window.clear();

		for (int i = 0; i < num_horzBox; i++) {
			for (int j = 0; j < num_vertBox; j++) {
				sprite1.setPosition(i*size, j*size);
				window.draw(sprite1);
			}

			
		}
		//draw snake
		for (int i = 0; i < snake_length; i++) {
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			window.draw(sprite2);
		}

		//draw snake2
		for (int i = 0; i < snake2_length; i++) {
			sprite4.setPosition(s2[i].x*size, s2[i].y*size);
			window.draw(sprite4);
		}

		//Draw fruit
		sprite3.setPosition(food.x*size, food.y*size);
		window.draw(sprite3);

		window.display();
	}
	return 0;
}