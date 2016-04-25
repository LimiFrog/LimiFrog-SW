package com.example.limifrog_v2;


import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

/**
 * A view container where OpenGL ES graphics can be drawn on screen. This view
 * can also be used to capture touch events, such as a user interacting with
 * drawn objects.
 */
public class CubeSurfaceView extends GLSurfaceView
{

	float touchedX = 0;
	float touchedY = 0;
	CubeRenderer renderer;

	public CubeSurfaceView(Context context)
	{
		super(context);
		
		// Create an OpenGL ES 2.0 context.
		setEGLContextClientVersion(2);
		
		// Set the Renderer for drawing on the CubeSurfaceView
		setRenderer(renderer = new CubeRenderer(this));
	}

	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
//		if (event.getAction() == MotionEvent.ACTION_DOWN)
//		{
//			touchedX = event.getX();
//			touchedY = event.getY();
//		}
//		else if (event.getAction() == MotionEvent.ACTION_MOVE)
//		{
//			renderer.xAngle += (touchedX - event.getX()) / 2f;
//			renderer.yAngle += (touchedY - event.getY()) / 2f;
//
//			touchedX = event.getX();
//			touchedY = event.getY();
//		}
		return true;
	}
	
	public void setAngle(float xAngle, float yAngle, float zAngle)
	{
		renderer.xAngle = xAngle;
		renderer.yAngle = yAngle;
		renderer.zAngle = zAngle;
	}
	
}