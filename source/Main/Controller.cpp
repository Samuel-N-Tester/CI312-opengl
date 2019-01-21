/*
 * Controller.cpp
 *
 *  Created on: 5 Nov 2018
 *      Author: Samuel
 */

#include <source/Main/Controller.h>

Controller::Controller(std::shared_ptr<Model> model_, std::shared_ptr<Viewer>view_) {
	running = true;
	model = model_;
	view = view_;
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

void Controller::run(){
	init();
	Shape* obj2 = new Obj("ball", 0, 0, 2);
	model->addShape(obj2);
	loop();
}

void Controller::init(){
	view->init();
}

void Controller::loop(){
  while(running){
		running = view->render();
	}
}
