//Usage:
//Hold down the number keys , 1-7, to select one or multiple circles.
//While circle(s) are selected, use the left mouse button to translate and use the right mouse button to rotate.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <vector>

#include "object.h"
using namespace std;

#define MAX_NUM_CIRCLE 7
#define CIRCLE_RADIUM 2.0f

int win_width = 600, win_height = 600;
float canvas_width = 20.0f;
float canvas_height = 20.0f;

constexpr float lb_w = 3.5f, lb_h = 2.0f, ub_w = 4.5f, ub_h = 2.0f, arm_w = 1.5f, arm_h = 1.0f, leg_w = 1.0f, leg_h = 2.0f, neck_w = 0.75f, neck_h = 1.0f, head_s = 2.0f, h_s = 1.5f
                ,
                f_w = 4.0f, f_h = 1.0f;

object* selected_object;


vector<object*> objects;

float curMouse[2];
float preMouse[2];

void set_selected_object(object* new_object)
{
	if (selected_object)
		selected_object->geometry_data->color[0] = 0.0f;
	new_object->geometry_data->color[0] = 1.0f;
	selected_object = new_object;
}

void create_human()
{
	// Root / Lower Body
	auto lower_body = new object("Lower_Body");
	lower_body->geometry_data->vertices =
	{
		{-lb_w / 2.0f, 0.0f},
		{lb_w / 2.0f, 0.0f},
		{lb_w / 2.0f, lb_h},
		{-lb_w / 2.0f, lb_h}
	};

	// Root / Lower Body / Upper Body
	auto upper_body = new object("Upper_Body");
	upper_body->geometry_data->vertices =
	{
		{-ub_w / 2.0f, 0.0f},
		{ub_w / 2.0f, 0.0f},
		{ub_w / 2.0f, ub_h},
		{-ub_w / 2.0f, ub_h}
	};
	upper_body->transform->set_parent(lower_body);
	upper_body->transform->position = {0.0f, lb_h};

	// Root / Lower Body / Upper Body / Neck
	auto neck = new object("Neck");
	neck->geometry_data->vertices =
	{
		{-neck_w / 2.0f, 0.0f},
		{neck_w / 2.0f, 0.0f},
		{neck_w / 2.0f, neck_h},
		{-neck_w / 2.0f, neck_h}
	};
	neck->transform->set_parent(upper_body);
	neck->transform->position = {0.0f, ub_h};

	// Root / Lower Body / Upper Body / Neck / Head
	auto head = new object("Head");
	head->geometry_data->vertices =
	{
		{-head_s / 2.0f, 0.0f},
		{head_s / 2.0f, 0.0f},
		{head_s / 2.0f, head_s},
		{-head_s / 2.0f, head_s}
	};
	head->transform->set_parent(neck);
	head->transform->position = {0.0f, neck_h};

	// Root / Lower Body / Upper Body / Right Arm
	auto r_arm = new object("R Arm");
	r_arm->geometry_data->vertices =
	{
		{-arm_w, -arm_h / 2.0f},
		{0.0f, -arm_h / 2.0f},
		{0.0f, arm_h / 2.0f},
		{-arm_w, arm_h / 2.0f}
	};
	r_arm->transform->set_parent(upper_body);
	r_arm->transform->position = {-ub_w / 2.0f, ub_h - arm_h / 2.0f};

	// Root / Lower Body / Upper Body / Right Arm / Right Fore Arm 
	auto r_f_arm = new object("R Fore Arm");
	r_f_arm->geometry_data->vertices =
	{
		{-arm_w, -arm_h / 2.0f},
		{0.0f, -arm_h / 2.0f},
		{0.0f, arm_h / 2.0f},
		{-arm_w, arm_h / 2.0f}
	};
	r_f_arm->transform->set_parent(r_arm);
	r_f_arm->transform->position = {-arm_w, 0.0f};

	// Root / Lower Body / Upper Body / Right Arm / Right Fore Arm / Right Hand 
	auto r_hand = new object("R Hand");
	r_hand->geometry_data->vertices =
	{
		{-h_s, -h_s / 2.0f},
		{0.0f, -h_s / 2.0f},
		{0.0f, h_s / 2.0f},
		{-h_s, h_s / 2.0f}
	};
	r_hand->transform->set_parent(r_f_arm);
	r_hand->transform->position = {-arm_w, 0.0f};

	// Root / Lower Body / Upper Body / Left Arm
	auto l_arm = new object("L Arm");
	l_arm->geometry_data->vertices =
	{
		{arm_w, -arm_h / 2.0f},
		{0.0f, -arm_h / 2.0f},
		{0.0f, arm_h / 2.0f},
		{arm_w, arm_h / 2.0f}
	};
	l_arm->transform->set_parent(upper_body);
	l_arm->transform->position = {ub_w / 2.0f, ub_h - arm_h / 2.0f};

	// Root / Lower Body / Upper Body / Left Arm / Left Fore Arm 
	auto l_f_arm = new object("L Fore Arm");
	l_f_arm->geometry_data->vertices =
	{
		{arm_w, -arm_h / 2.0f},
		{0.0f, -arm_h / 2.0f},
		{0.0f, arm_h / 2.0f},
		{arm_w, arm_h / 2.0f}
	};
	l_f_arm->transform->set_parent(l_arm);
	l_f_arm->transform->position = {arm_w, 0.0f};

	// Root / Lower Body / Upper Body / Left Arm / Left Fore Arm / Left Hand 
	auto l_hand = new object("L Hand");
	l_hand->geometry_data->vertices =
	{
		{h_s, -h_s / 2.0f},
		{0.0f, -h_s / 2.0f},
		{0.0f, h_s / 2.0f},
		{h_s, h_s / 2.0f}
	};
	l_hand->transform->set_parent(l_f_arm);
	l_hand->transform->position = {arm_w, 0.0f};

	// Root / Lower Body / Right Thigh
	auto r_thigh = new object("R Thigh");
	r_thigh->geometry_data->vertices =
	{
		{-leg_w / 2.0f, 0.0f},
		{leg_w / 2.0f, 0.0f},
		{leg_w / 2.0f, -leg_h},
		{-leg_w / 2.0f, -leg_h}
	};
	r_thigh->transform->set_parent(lower_body);
	r_thigh->transform->position = {-(lb_w - leg_w) / 2.0f, 0.0f};

	// Root / Lower Body / Right Thigh / Right Leg
	auto r_leg = new object("R Leg");
	r_leg->geometry_data->vertices =
	{
		{-leg_w / 2.0f, 0.0f},
		{leg_w / 2.0f, 0.0f},
		{leg_w / 2.0f, -leg_h},
		{-leg_w / 2.0f, -leg_h}
	};
	r_leg->transform->set_parent(r_thigh);
	r_leg->transform->position = {0.0f, -leg_h};

	// Root / Lower Body / Right Thigh / Right Leg / Right Foot
	auto r_foot = new object("R Foot");
	r_foot->geometry_data->vertices =
	{
		{-(f_w - leg_w) / 2.0f, 0.0f},
		{leg_w / 2.0f, 0.0f},
		{leg_w / 2.0f, -f_h},
		{-(f_w - leg_w) / 2.0f, -f_h}
	};
	r_foot->transform->set_parent(r_leg);
	r_foot->transform->position = {0.0f, -leg_h};

	// Root/ Lower Body/ Left Thigh
	auto l_thigh = new object("L Thigh");
	l_thigh->geometry_data->vertices =
	{
		{-leg_w / 2.0f, 0.0f},
		{leg_w / 2.0f, 0.0f},
		{leg_w / 2.0f, -leg_h},
		{-leg_w / 2.0f, -leg_h}
	};
	l_thigh->transform->set_parent(lower_body);
	l_thigh->transform->position = {(lb_w - leg_w) / 2.0f, 0.0f};

	// Root / Lower Body / Left Thigh / Left Leg
	auto l_leg = new object("L Leg");
	l_leg->geometry_data->vertices =
	{
		{-leg_w / 2.0f, 0.0f},
		{leg_w / 2.0f, 0.0f},
		{leg_w / 2.0f, -leg_h},
		{-leg_w / 2.0f, -leg_h}
	};
	l_leg->transform->set_parent(l_thigh);
	l_leg->transform->position = {0.0f, -leg_h};

	// Root / Lower Body / Left Thigh / Left Leg / Left Foot
	auto l_foot = new object("L Foot");
	l_foot->geometry_data->vertices =
	{
		{(f_w - leg_w) / 2.0f, 0.0f},
		{-leg_w / 2.0f, 0.0f},
		{-leg_w / 2.0f, -f_h},
		{(f_w - leg_w) / 2.0f, -f_h}
	};
	l_foot->transform->set_parent(l_leg);
	l_foot->transform->position = {0.0f, -leg_h};

	objects.push_back(lower_body);
}

void init(void)
{
	create_human();

	set_selected_object(objects[0]);
}

void draw_geometry(const object* geometry)
{
	const auto geometry_data = geometry->geometry_data;
	const auto transform = geometry->transform;

	glPushMatrix();

	glTranslatef(transform->position.x, transform->position.y, transform->position.z);
	glRotatef(transform->rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(transform->rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(transform->rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(transform->scale.x, transform->scale.y, transform->scale.z);

	glColor4fv(geometry_data->color);
	glLineWidth(geometry_data->point_size);

	glBegin(geometry_data->draw_type);

	for (const auto vertex : geometry_data->vertices)
		glVertex3f(vertex.x, vertex.y, vertex.z);

	glEnd();

	if (transform->get_child_count() > 0)
	{
		for (const auto child : transform->children)
			draw_geometry(child);
	}

	glPopMatrix();
}

void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// the following codes could be written in a for loop.
	// Here I expand them so that you can better trace the changes of cirlce's coordinate system.

	for (const object* circle : objects)
		draw_geometry(circle);

	glutSwapBuffers();
}


void reshape(int w, int h)
{
	win_width = w;
	win_height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-canvas_width / 2.0f, canvas_width / 2.0f, -canvas_height / 2.0f, canvas_height / 2.0f);
	glViewport(0, 0, (GLsizei)win_width, (GLsizei)win_height);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) // 'esc' key
		exit(0);

	switch (key)
	{
	case 97:
		selected_object->transform->rotation.z += 10.0f;
		break;
	case 100:
		selected_object->transform->rotation.z += -10.0f;
		break;
	}

	glutPostRedisplay();
}

void special_keyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		{
			object* parent = selected_object->transform->parent;
			if (parent)
				set_selected_object(parent);
		}
		break;
	case GLUT_KEY_DOWN:
		{
			object* first_child = selected_object->transform->get_child(0);
			if (first_child)
				set_selected_object(first_child);
		}
		break;
	case GLUT_KEY_LEFT:
		{
			transform* parent_transform = selected_object->transform->parent->transform;
			if (parent_transform)
			{
				if (parent_transform->get_child_count() > 1)
				{
					object* new_object = parent_transform->get_prev_child(selected_object);
					set_selected_object(new_object);
				}
			}
		}
		break;
	case GLUT_KEY_RIGHT:
		{
			transform* parent_transform = selected_object->transform->parent->transform;
			if (parent_transform)
			{
				if (parent_transform->get_child_count() > 1)
				{
					object* new_object = parent_transform->get_next_child(selected_object);
					set_selected_object(new_object);
				}
			}
		}
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(win_width, win_height);
	glutCreateWindow("Transform with Robot");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);
	// glutKeyboardUpFunc(keyboardUp);
	// glutMouseFunc(mouse);
	// glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}
