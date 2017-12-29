/*---------------------------------------------------------------------+\
|
|	main.cpp  --  application framework for running Gadget package
|                 with OpenGL as the graphics library
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include <gtk/gtk.h>

#include <stdio.h>
#include <unistd.h>

#include "UKeys.h"
#include "GaugeViewGTK.h"
#include "GaugeApp.h"
#include "CServiceManager.h"
#include "CKeyNames.h"


/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
#define YMAX	700
#define XMAX	(YMAX*3/2)

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
static GaugeViewGTK* GaugeView;
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
bool	g_bCalculateNeeded;		// extern
NAMESPACE_GADGET_END

int g_appStart;


bool	g_bStandardCalc = false;

/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * display - glut display callback function

\+---------------------------------------------------------------------*/
void	display
		(
		void
		)
{
//		printf("glut display callback function \n");
	if ( GaugeView )
		GaugeView->Render();
}

/*---------------------------------------------------------------------+\

 * keyboard - glut keyboard callback function

\+---------------------------------------------------------------------*/
void	keyboard
		(
		unsigned char key,
		int x,
		int y
		)
{
	long	mMods = 0;

	if ( isalpha(key) )
	{
		if ( isupper(key) )
		{
			mMods |= MODKEY_M_SHIFT;
		}
		else
		{
			key = toupper(key);
		}
	}
	//printf("keyboard-Down: %d\n", (int) key);
	if ( GaugeView )
	{
		GaugeView->OnKeyDown(key, 1, mMods);
		g_bStandardCalc = true;
	}
}

/*---------------------------------------------------------------------+\

 * keyboardUp - glut keyboard callback function

\+---------------------------------------------------------------------*/
void 	keyboardUp
		(
		unsigned char key,
		int x,
		int y
		)
{
	long	mMods = 0;

	if ( isalpha(key) )
	{
		if ( isupper(key) )
		{
			mMods |= MODKEY_M_SHIFT;
		}
		else
		{
			key = toupper(key);
		}
	}
	//printf("keyboard-Up: %d\n", (int) key);
	if ( GaugeView )
	{
		GaugeView->OnKeyUp(key, 1, mMods);
		g_bStandardCalc = true;
	}
}


/*---------------------------------------------------------------------+\

 * mouseButton - glut mouseButton callback function

\+---------------------------------------------------------------------*/
void	mouseButton
		(
		int	nButtonCode,
		int mModifiers,
		int x,
		int y
		)
{
#if 0
	switch (nButtonCode)
	{
	case GLUT_LEFT_BUTTON:
		if(mModifiers == GLUT_DOWN)
		{
			GaugeView->OnLButtonDown(mModifiers, x, y);
			//printf("mouseButton Down = %d, x=%d, y=%d\n", nButtonCode, x, y);
		}
		else if (mModifiers == GLUT_UP)
		{
			GaugeView->OnLButtonUp(mModifiers, x, y);
			//printf("mouseButton Up = %d, x=%d, y=%d\n", nButtonCode, x, y);
		}
		g_bStandardCalc = true;
		break;
	default:
		break;
	}
#endif

}

/*---------------------------------------------------------------------+\

 * mouseMove -

\+---------------------------------------------------------------------*/
void	mouseMove
		(
		int	x,
		int	y
		)
{
	GaugeView->OnMouseMove( 0, x, y );
	g_bStandardCalc = true;
	//if ( GaugeView->Calculate())
	//	glutPostRedisplay();
}


/*---------------------------------------------------------------------+\

 * windowResize -

\+---------------------------------------------------------------------*/
void	windowResize
		(
		int	x,
		int	y
		)
{

	if ( GaugeView )
	{
		GaugeView->Size( x, y );
		//glutPostRedisplay();
	}
}


/*---------------------------------------------------------------------+\

 * initSpecialKeys -

\+---------------------------------------------------------------------*/
static unsigned char	m_aSpecial[128] = {0};

void	initSpecialKeys
		(
		void
		)
{
#if 0
	::memset( m_aSpecial, 0, sizeof(m_aSpecial) );

	CKeyNames	k;

	m_aSpecial[GLUT_KEY_F1] = k.GetKey( "F1" );
	m_aSpecial[GLUT_KEY_F2] = k.GetKey( "F2" );
	m_aSpecial[GLUT_KEY_F3] = k.GetKey( "F3" );
	m_aSpecial[GLUT_KEY_F4] = k.GetKey( "F4" );
	m_aSpecial[GLUT_KEY_F5] = k.GetKey( "F5" );
	m_aSpecial[GLUT_KEY_F6] = k.GetKey( "F6" );
	m_aSpecial[GLUT_KEY_F7] = k.GetKey( "F7" );
	m_aSpecial[GLUT_KEY_F8] = k.GetKey( "F8" );
	m_aSpecial[GLUT_KEY_F9] = k.GetKey( "F9" );
	m_aSpecial[GLUT_KEY_F10] = k.GetKey( "F10" );
	m_aSpecial[GLUT_KEY_F11] = k.GetKey( "F11" );
	m_aSpecial[GLUT_KEY_F12] = k.GetKey( "F12" );

	m_aSpecial[GLUT_KEY_LEFT] = k.GetKey( "LEFT" );
	m_aSpecial[GLUT_KEY_UP] = k.GetKey( "UP" );
	m_aSpecial[GLUT_KEY_RIGHT] = k.GetKey( "RIGHT" );
	m_aSpecial[GLUT_KEY_DOWN] = k.GetKey( "DOWN" );

	m_aSpecial[GLUT_KEY_PAGE_UP] = k.GetKey( "PRIOR" );
	m_aSpecial[GLUT_KEY_PAGE_DOWN] = k.GetKey( "NEXT" );
	m_aSpecial[GLUT_KEY_HOME] = k.GetKey( "HOME" );
	m_aSpecial[GLUT_KEY_END] = k.GetKey( "END" );
	m_aSpecial[GLUT_KEY_INSERT] = k.GetKey( "INSERT" );
#endif
}

/*---------------------------------------------------------------------+\

 * specialKey - glut specialKey callback function

\+---------------------------------------------------------------------*/
void	specialKey
		(
		int key,
		int x,
		int y
		)
{
	//printf("specialKey-Down = %d\n", key);
	if (GaugeView)
	{
		if ( 0 <= (unsigned)key  &&  (unsigned)key < sizeof(m_aSpecial) )
			key = m_aSpecial[key];
		GaugeView->OnKeyDown(key, 1, 0);
		g_bStandardCalc = true;
	}
}

/*---------------------------------------------------------------------+\

 * specialKeyUp - glut specialKey callback function

\+---------------------------------------------------------------------*/
void	specialKeyUp
		(
		int key,
		int x,
		int y
		)
{
	//printf("specialKey-Up = %d\n", key);
	if (GaugeView)
	{
		if ( 0 <= (unsigned)key  &&  (unsigned)key < sizeof(m_aSpecial) )
			key = m_aSpecial[key];
		GaugeView->OnKeyUp(key, 1, 0);
		g_bStandardCalc = true;
	}
}

/*---------------------------------------------------------------------+\

 * timer_func - glut timer callback function

\+---------------------------------------------------------------------*/
void	timer_func
		(
		int msec_delay
		)
{
#if 0
	if ( GaugeView->CalculateNow())
		glutPostRedisplay();
	else
		GaugeView->StaleData();
	glutTimerFunc(msec_delay, timer_func, msec_delay); // recursively call timer_func
#endif
}

/*---------------------------------------------------------------------+\

 * idle_func - glut idle callback function

\+---------------------------------------------------------------------*/
void	idle_func
		(
		void
		)
{
#if 0
	if ( g_bStandardCalc )
	{
		if ( GaugeView->Calculate() )
			glutPostRedisplay();
	}
	else if ( g_bCalculateNeeded )
	{
		if ( GaugeView->CalculateNow() )
			glutPostRedisplay();
	}
	g_bStandardCalc = false;
	g_bCalculateNeeded = false;
#endif
}


/*---------------------------------------------------------------------+\

 * gl_Reshape -

\+---------------------------------------------------------------------*/
void	gl_Reshape
		(
		int width,
		int height
		)
{
	if ( GaugeView )
	{
		GaugeView->Size( width, height );
		//glutPostRedisplay();
	}

}

/*---------------------------------------------------------------------+\

 * gl_Init -

\+---------------------------------------------------------------------*/
void	gl_Init
		(
		void
		)
{
#if 0
	//glEnable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );


	/* set up standard orthogonal view with clipping */
	/* box as cube of side 2 centered at origin */
	/* This is default view and these statement could be removed */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

//	glIndex(0, DEFAULT_ALPHA_VALUE);
	gl_Reshape(XMAX, YMAX);
	glLineWidth(1.0); /* set line width */

	//setup_colors();
#endif

}

/*---------------------------------------------------------------------+\

 * main -

\+---------------------------------------------------------------------*/
int		main
		(
		int		argc,
		char**	argv
		)
{
	g_appStart = false;
	g_bCalculateNeeded = false;

	initSpecialKeys();

	GtkWidget*	pWindow;
	GtkWidget*	pDrawArea;

	gtk_init( &argc, &argv );

	pWindow = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	pDrawArea = gtk_drawing_area_new();
	gtk_container_add( GTK_CONTAINER(pWindow), pDrawArea );

	gtk_window_set_title( GTK_WINDOW(pWindow), "GaugeApp Workbench" );
	gtk_window_set_default_size( GTK_WINDOW(pWindow), XMAX, YMAX );
	gtk_widget_show( pWindow );

	g_signal_connect_swapped(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);


	gtk_main();	// while (1) ...

//	dlopen(NULL, RTLD_NOW|RTLD_GLOBAL);


	/* You must call glutInit before any other OpenGL/GLUT calls */
//	glutInit(&argc,argv);
//
//	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
//
//
//	glutInitWindowSize(XMAX,YMAX);
//	glutInitWindowPosition(0,0);
//	glutCreateWindow("GaugeApp Workbench");
//	glutReshapeFunc(windowResize);
//	glutDisplayFunc(display);
//	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
//	glutIgnoreKeyRepeat(true);
//	glutKeyboardFunc(keyboard);
//	glutKeyboardUpFunc(keyboardUp);
//	glutSpecialFunc(specialKey);
//	glutSpecialUpFunc(specialKeyUp);
//	glutMouseFunc(mouseButton);
//	glutMotionFunc(mouseMove);
//	glutIdleFunc(idle_func);
//
//
//	gl_Init();
//
//	printf("Processing Gauge XML...\n");
//	GaugeView = new GaugeViewOpenGL(XMAX, YMAX);//usleep(1000000);
//
//	timer_func(int(0.5*1000));
//	//timer_func(1000);	// redisplay every 1 second
//
//	glutSwapBuffers();
//
//	g_appStart = true;
//
//	//printf("Starting glutMainLoop()...version 1.0.0 - dated 7/17/2010e\n");
//
//	glutMainLoop(); //while(1)...

	return 0;
}



