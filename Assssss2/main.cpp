
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <sys/time.h>
#elif defined(WIN32)
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <sys/time.h>
#endif


#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"


#include "Shape.hpp"
#include "Vehicle.hpp"
#include "RecPrism.h"
#include "TrapPrism.h"
#include "TriPrism.h"
#include "cylinder.h"
#include "MyVehicle.h"
//#include "Wheel.h"

void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
//   can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;

// default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

//int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	//   with the name of the class you want to show as the current 
	//   custom vehicle.
	// -------------------------------------------------------------------------
	// calling MyVehicle function to print the car at 0,0,0
	vehicle = new MyVehicle(0,0,0);


	// add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10, 10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10, -10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10, 10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10, -10, 1));

	// add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);


	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

//drawing reference points within the virtual world
void drawGoals()
{
	for (int i = 0; i < goals.size(); ++i) {
		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		// white
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}

void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();

	// draw other vehicles
	for (std::map<int, Vehicle *>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter)
		iter->second->draw();

	// draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();

	}

	// draw obstacles
	ObstacleManager::get()->drawAll();

	// draw goals
	drawGoals();

	// draw HUD
	HUD::Draw();

	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;
}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if (QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {

	if (KeyManager::get()->isAsciiKeyPressed('a')) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c')) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d')) {
		Camera::get()->strafeRight();
	}

	if (KeyManager::get()->isAsciiKeyPressed('s')) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w')) {
		Camera::get()->moveForward();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ')) {
		Camera::get()->strafeUp();
	}

	speed = 0;
	steering = 0;

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}

	// attempt to do data communications every 4 frames if we've created a local vehicle
	if (frameCounter % 4 == 0 && vehicle != NULL) {

		// if not connected, attempt to connect every 2 seconds
		if (!RemoteDataManager::IsConnected()) {
			if (frameCounter % 120 == 0) {

				// erase other vehicles
				for (std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au","18081");
				//www.robotics.unsw.edu.au
				//192.168.1.1

				// on connect, let's tell the server what we look like
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					vm.remoteID = 0;

					std::vector<Shape*>ListShape = dynamic_cast<MyVehicle*>(vehicle)->getShapes();
					//iterate through vector ListShape created in constructor
					for (int i = 0; i < ListShape.size(); i++) {
					//ShapeInit is a struct with shape parameters and info
					ShapeInit vehicle;

					vehicle.xyz[0] = ListShape[i]->getX();
					vehicle.xyz[1] = ListShape[i]->getY();
					vehicle.xyz[2] = ListShape[i]->getZ();
					vehicle.rotation = ListShape[i]->getRotation();
					vehicle.rgb[0] = ListShape[i]->getRed();
					vehicle.rgb[1] = ListShape[i]->getGreen();
					vehicle.rgb[2] = ListShape[i]->getBlue();


					RecPrism *p1 = dynamic_cast
					if (dynamic_cast <RecPrism *> (ListShape[i]) != nullptr){
						vehicle.type = RECTANGULAR_PRISM;
						vehicle.params.rect.xlen = (float)dynamic_cast<RecPrism*>(ListShape[i])->GetX();
						vehicle.params.rect.ylen = (float)dynamic_cast<RecPrism*>ListShape[i]->GetY();
						vehicle.params.rect.zlen = (float)dynamic_cast<RecPrism*>ListShape[i]->GetZ();
					}
					else if (dynamic_cast <TriPrism *> (ListShape[i]) != nullptr) {
						vehicle.type = TRIANGULAR_PRISM;
						vehicle.params.tri.alen = (float)dynamic_cast<TriPrism*>ListShape[i]->GetX();
						vehicle.params.tri.blen = (float)dynamic_cast<TriPrism*>ListShape[i]->GetY();
						vehicle.params.tri.depth = (float)dynamic_cast<TriPrism*>ListShape[i]->GetZ();
						vehicle.params.tri.angle = (float)dynamic_cast<TriPrism*>ListShape[i]->GetAngle();
					}
					else if (dynamic_cast <TrapPrism *> (ListShape[i]) != nullptr) {
						vehicle.type = TRAPEZOIDAL_PRISM;
						vehicle.params.trap.alen = (float)dynamic_cast<TrapPrism*>ListShape[i]->GetA();
						vehicle.params.trap.blen = (float)dynamic_cast<TrapPrism*>ListShape[i]->GetB();
						vehicle.params.trap.depth = (float)dynamic_cast<TrapPrism*>ListShape[i]->GetDepth();
						vehicle.params.trap.height = (float)dynamic_cast<TrapPrism*>ListShape[i]->GetHeight();
						vehicle.params.trap.aoff = (float)dynamic_cast<TrapPrism*>ListShape[i]->GetOffset();
					}
					else(dynamic_cast <Cylinder *> (ListShape[i]) != nullptr) {
						vehicle.type = CYLINDER;
						vehicle.params.cyl.radius = (float)dynamic_cast<Cylinder*>ListShape[i]->GetR();
						vehicle.params.cyl.depth = (float)dynamic_cast<Cylinder*>ListShape[i]->GetL();
						vehicle.params.cyl.isRolling = (float)dynamic_cast<Cylinder*>ListShape[i]->GetisRolling();
						vehicle.params.cyl.isSteering = (float)dynamic_cast<Cylinder*>ListShape[i]->GetisSteering();
					}
					vm.shapes.push_back(vehicle);
					}
					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// if we're connected, send our vehicle state to the server
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			vs.rotation = vehicle->getRotation();
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// if we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for (unsigned int i = 0; i < msgs.size(); i++) {

				RemoteMessage msg = msgs[i];
				//cout << msg.payload << endl;

				switch (msg.type) {
					// new models
				case 'M':
				{
					std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
					for (unsigned int j = 0; j < models.size(); j++) {
						VehicleModel vm = models[j];

						// uncomment the line below to create remote vehicles
						otherVehicles[vm.remoteID] = new MyVehicle();
						//std::vector<ShapeInit>::iterator it;
						ShapeInit it;
						
						//
						// more student code goes here
						//
						
						int i;
						
						Shape * sh = NULL;
						const double time = 0.042;
						//sh = new Wheel (length, radius, isRolling, isSteering);
						vm.shapes.push_back(it);
						int k = 0;
						for (k = 0; k < models.size(); k++) {
							for (i = 0; i < vm.shapes.size(); i++) {

								if (vm.shapes[i].type == CYLINDER) {
									sh = new Cylinder(
										vm.shapes[i].params.cyl.radius,
										vm.shapes[i].params.cyl.depth,

										vm.shapes[i].params.cyl.isRolling,
										vm.shapes[i].params.cyl.isSteering
									);
									sh->setPosition(
										vm.shapes[i].xyz[0],
										vm.shapes[i].xyz[1],
										vm.shapes[i].xyz[2]
									);
									sh->setColor(
										vm.shapes[i].rgb[0],
										vm.shapes[i].rgb[1],
										vm.shapes[i].rgb[2]
									);
									sh->setRotation(vm.shapes[i].rotation);
									otherVehicles[vm.remoteID]->addShape(sh);
								}

								if (vm.shapes[i].type == RECTANGULAR_PRISM) {
									sh = new RecPrism(
										vm.shapes[i].params.rect.xlen,
										vm.shapes[i].params.rect.ylen,
										vm.shapes[i].params.rect.zlen
									);
									sh->setPosition(
										vm.shapes[i].xyz[0],
										vm.shapes[i].xyz[1],
										vm.shapes[i].xyz[2]
									);
									sh->setColor(
										vm.shapes[i].rgb[0],
										vm.shapes[i].rgb[1],
										vm.shapes[i].rgb[2]
									);
									sh->setRotation(vm.shapes[i].rotation);
									otherVehicles[vm.remoteID]->addShape(sh);
								}
								if (vm.shapes[i].type == TRIANGULAR_PRISM) {
									sh = new TriPrism(
										vm.shapes[i].params.tri.alen,
										vm.shapes[i].params.tri.blen,
										vm.shapes[i].params.tri.depth,
										vm.shapes[i].params.tri.angle
									);
									sh->setPosition(
										vm.shapes[i].xyz[0],
										vm.shapes[i].xyz[1],
										vm.shapes[i].xyz[2]
									);
									sh->setColor(
										vm.shapes[i].rgb[0],
										vm.shapes[i].rgb[1],
										vm.shapes[i].rgb[2]
									);
									sh->setRotation(vm.shapes[i].rotation);
									otherVehicles[vm.remoteID]->addShape(sh);
								}
								if (vm.shapes[i].type == TRAPEZOIDAL_PRISM) {
									sh = new TrapPrism(
										vm.shapes[i].params.trap.alen,
										vm.shapes[i].params.trap.blen,
										vm.shapes[i].params.trap.depth,
										vm.shapes[i].params.trap.height,
										vm.shapes[i].params.trap.aoff
									);
									sh->setPosition(
										vm.shapes[i].xyz[0],
										vm.shapes[i].xyz[1],
										vm.shapes[i].xyz[2]
									);
									sh->setColor(
										vm.shapes[i].rgb[0],
										vm.shapes[i].rgb[1],
										vm.shapes[i].rgb[2]
									);
									sh->setRotation(vm.shapes[i].rotation);
									otherVehicles[vm.remoteID]->addShape(sh);
								}

							}
						}
						
						/*for (std::vector<ShapeInit>::iterator it = vm.shapes.begin(); it != vm.shapes.end(); it++) {
							//for (int i = 0; i < vm.shapes.size(); i++)
							// vm.shapes[i].type

							//if (vm.shapes[1].type == 1) 
							//vm.shapes[i].params.rect.xlen;
							//vm.shapes[i].rotationvm.shapes[i].xyz[0-2]

							//vm shapes = obtain vector shape in it

							if (it->type == RECTANGULAR_PRISM) {
							RecPrism* r = new RecPrism(it->params.rect.xlen, it->params.rect.ylen, it->params.rect.zlen);
							r->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
							r->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
							otherVehicles[vm.remoteID]->addShape(r);

							}
							else if (it->type == TRIANGULAR_PRISM) {
							TriPrism* t = new TriPrism(it->params.tri.alen, it->params.tri.blen, it->params.tri.angle, it->params.tri.depth);
							t->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
							t->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
							otherVehicles[vm.remoteID]->addShape(t);

							}
							else if (it->type == TRAPEZOIDAL_PRISM) {
							TrapPrism* trap = new TrapPrism(it->params.trap.alen, it->params.trap.blen, it->params.trap.height, it->params.trap.aoff, it->params.trap.depth);
							trap->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
							trap->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
							otherVehicles[vm.remoteID]->addShape(trap);

							}else if(it->type == CYLINDER){
							Cylinder* c = new Cylinder(it->params.cyl.radius, it->params.cyl.depth, it->params.cyl.isRolling, it->params.cyl.isSteering);
							c->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
							c->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
							otherVehicles[vm.remoteID]->addShape(c);

							}

							

						}*/
					}


					break;
				}

				// vehicle states
				case 'S':
				{
					std::vector<VehicleState> states = GetVehicleStates(msg.payload);
					for (unsigned int i = 0; i < states.size(); i++) {
						VehicleState vs = states[i];

						std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
						if (iter != otherVehicles.end()) {
							Vehicle * veh = iter->second;
							remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
						}
					}
					break;
				}

				// goal state
				case 'G':
				{
					goals = GetGoals(msg.payload);
					break;
				}

				// obstacle state
				case 'O':
				{
					std::vector<ObstacleState> obs = GetObstacles(msg.payload);
					for (unsigned int i = 0; i < obs.size(); i++) {
						Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
						ObstacleManager::get()->addObstacle(o);
					}
					break;
				}

				// disconnect list
				case 'D':
				{
					std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
					for (unsigned int i = 0; i < disconnectedIDs.size(); i++) {
						int id = disconnectedIDs[i];
						std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
						if (iter != otherVehicles.end()) {
							delete iter->second;
							otherVehicles.erase(iter);
						}
					}
					break;
				}

				// error message
				case 'E':
				{
					cerr << "Server error: " << msg.payload << endl;
					break;
				}

				}
			}
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// do a simulation step
	if (vehicle != NULL) {
		vehicle->update(speed, steering, elapsedTime);
	}
	for (std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// keys that will be held down for extended periods of time will be handled
	//   in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// keys that react ocne when pressed rather than need to be held down
	//   can be handles normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;
	}

};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {
	KeyManager::get()->specialKeyReleased(keycode);
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};


