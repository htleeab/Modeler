// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();
	//background color
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// draw the floor
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
		glTranslated(-10,0,-10);
		drawBox(20,0.01f,20);
	glPopMatrix();

	// draw the sample model
	setAmbientColor(.1f,.1f,.1f);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
		/*sample
		glPushMatrix();
		glTranslated(-1.5, 0, -2);
		glScaled(3, 1, 4);
		drawBox(1,1,1);
		glPopMatrix();
		// draw cannon
		glPushMatrix();
		glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawCylinder(VAL(HEIGHT), 0.1, 0.1);
		glTranslated(0.0, 0.0, VAL(HEIGHT));
		drawCylinder(1, 1.0, 0.9);

		glTranslated(0.0, 0.0, 0.5);
		glRotated(90, 1.0, 0.0, 0.0);
		drawCylinder(4, 0.1, 0.2);
		glPopMatrix();
		*/


		//upper body
		glPushMatrix();
			glTranslated(0, 10.0, 0.0);
			//head and heck
			glPushMatrix();
				glTranslated(0.0, 5.0, 0.0);
				// draw head
				glPushMatrix();
					setDiffuseColor(1, (float)242 / 255, (float)230 / 255);
					drawSphere(0.9f);//1 unit = 10 cm
				glPopMatrix();
				// draw neck
				glPushMatrix();
					glTranslated(0, -0.7, 0.0);
					glRotated(90, 1.0, 0.0, 0.0);
					setDiffuseColor(1, (float)242 / 255, (float)230 / 255);
					drawCylinder(1.2f, 0.3, 0.5);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				//upper torso
				glTranslated(-1.5, 0, -0.8);
				setDiffuseColor((float)15/255, (float)10 / 255, (float)10 / 255);
				drawBox(3.0f,4.0f,1.7f);
			glPopMatrix();

		glPopMatrix();

		//test triangle (1 face)
		glPushMatrix();
		setDiffuseColor(1, (float)200 / 255, (float)1 / 255);
		glTranslated(0.0, 1.0, 0.0);
		drawTriangle((double)1, (double)1, (double)1, (double)2, (double)1, (double)1, (double)1, (double)2, (double)2);
		glPopMatrix();

	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
    controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
