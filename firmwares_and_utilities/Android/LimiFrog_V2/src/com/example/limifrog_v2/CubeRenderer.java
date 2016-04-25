package com.example.limifrog_v2;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.example.limifrog_v2.R;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.GLUtils;
import android.opengl.Matrix;
import android.os.SystemClock;


public class CubeRenderer implements GLSurfaceView.Renderer 
{
	/**
	 * Store the model matrix. This matrix is used to move models from object space (where each model can be thought
	 * of being located at the center of the universe) to world space.
	 */
	public float xAngle = 0;
	public float yAngle = 0;
	public float zAngle = 0;
	private float[] mModelMatrix = new float[16];

	short[] indeces = 
		{
			0, 1, 2, 2, 3, 0,
            4, 5, 7, 5, 6, 7,
            8, 9, 11, 9, 10, 11,
            12, 13, 15, 13, 14, 15,
            16, 17, 19, 17, 18, 19,
            20, 21, 23, 21, 22, 23,		
		};
	
	/**
	 * Store the view matrix. This can be thought of as our camera. This matrix transforms world space to eye space;
	 * it positions things relative to our eye.
	 */
	private float[] mViewMatrix = new float[16];


	/** Store the projection matrix. This is used to project the scene onto a 2D viewport. */
	private float[] mProjectionMatrix = new float[16];

	
	
	/** Allocate storage for the final combined matrix. This will be passed into the shader program. */
	private float[] mMVPMatrix = new float[16];
	private final FloatBuffer mCubeColors;
	/** Store our model data in a float buffer. */
	private final FloatBuffer mcubeVertices;

	ShortBuffer indexBuffer = null;
	/** Store our model data in a float buffer. */
	private final FloatBuffer mCubeTextureCoordinates;
	 
	/** This will be used to pass in the texture. */
	private int mTextureUniformHandle;
	 
	/** This will be used to pass in model texture coordinate information. */
	private int mTextureCoordinateHandle;
	 
	/** Size of the texture coordinate data in elements. */
	private final int mTextureCoordinateDataSize = 2;
	 
	/** This is a handle to our texture data. */
	private int mTextureDataHandle0;
	private int mTextureDataHandle1;
	private int mTextureDataHandle2;
	private int mTextureDataHandle3;
	private int mTextureDataHandle4;
	private int mTextureDataHandle5;

	/** This will be used to pass in the transformation matrix. */
	private int mMVPMatrixHandle;
	
	/** This will be used to pass in model position information. */
	private int mPositionHandle;
	/** This is a handle to our cube shading program. */
	private int mProgramHandle;
	/** This will be used to pass in model color information. */
	private int mColorHandle;

	/** How many bytes per float. */
	private final int mBytesPerFloat = 4;
	
	
	 GLSurfaceView mActivityContext;		
	/**
	 * Initialize the model data.
	 */
	public CubeRenderer(CubeSurfaceView cubesurfaceview)
	{	
		mActivityContext = cubesurfaceview;
		// Define points for equilateral triangles.
				
		// This triangle is red, green, and blue.
		final float[] triangle1VerticesData = 
			{
				// X, Y, Z, 
			
				-0.4f, -0.4f,  0.1f,	// left-bottom-front			
	            0.4f, -0.4f,  0.1f, 	// right-bottom-front          
	            0.4f,  0.4f,  0.1f, 	// right-top-front   
	           -0.4f,  0.4f,  0.1f, 	// left-top-front
	         	         
	            0.4f, -0.4f,  0.1f,     // right-bottom-front      
	            0.4f, -0.4f, -0.1f,     // right-bottom-back      
	            0.4f,  0.4f, -0.1f,     // right-top-back         
	            0.4f,  0.4f,  0.1f, 	// right-top-front
	         	          
	            0.4f, -0.4f, -0.1f, 	// right-bottom-back           
	           -0.4f, -0.4f, -0.1f, 	// left-bottom-back         
	           -0.4f,  0.4f, -0.1f, 	// left-top-back          
	            0.4f,  0.4f, -0.1f, 	// right-top-back
	           	          
	           -0.4f, -0.4f, -0.1f,  	// left-bottom-back        
	           -0.4f, -0.4f,  0.1f, 	// left-bottom-front	          
	           -0.4f,  0.4f,  0.1f, 	// left-top-front         
	           -0.4f,  0.4f, -0.1f, 	// left-top-back
	         	         
	           -0.4f,  0.4f,  0.1f, 	// left-top-front         
	            0.4f,  0.4f,  0.1f, 	// right-top-front          
	            0.4f,  0.4f, -0.1f, 	// right-top-back       
	           -0.4f,  0.4f, -0.1f, 	// left-top-back
	         	         
	           -0.4f, -0.4f,  0.1f, 	// left-bottom-front         
	            0.4f, -0.4f,  0.1f, 	// right-bottom-front           
	            0.4f, -0.4f, -0.1f, 	// right-bottom-back           
	           -0.4f, -0.4f, -0.1f,		// left-bottom-back	
		    };
		
		// R, G, B, A
		final float[] cubeColorData =
		{				
				// Front face (white)
				1.0f, 1.0f, 1.0f, 1.0f,				
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,				
				
				// Right face (white)
				1.0f, 1.0f, 1.0f, 1.0f,				
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,				
				
				// Back face (white)
				1.0f, 1.0f, 1.0f, 1.0f,				
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,				
				
				// Left face (white)
				1.0f, 1.0f, 1.0f, 1.0f,				
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,				
				
				// Top face (white)
				1.0f, 1.0f, 1.0f, 1.0f,				
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,				
				
				// Bottom face (white)
				1.0f, 1.0f, 1.0f, 1.0f,				
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,				

		};
		
		// S, T (or X, Y)
		// Texture coordinate data.
		// Because images have a Y axis pointing downward (values increase as you move down the image) while
		// OpenGL has a Y axis pointing upward, we adjust for that here by flipping the Y axis.
		// What's more is that the texture coordinates are the same for every face.
		
		// See: http://www.jayway.com/2010/12/30/opengl-es-tutorial-for-android-part-vi-textures/
		
		//NB:
		// Android uses the top-left corner as being 0,0 of the coordinate system, 
		// OpenGL uses the bottom-left corner being 0,0 
		final float[] cubeTextureCoordinateData =
		{		
				//front face
				0.0f, 1.0f, 									
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
		
				
				// Right face 
				0.0f, 1.0f, 									
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
				
				// Back face 
				0.0f, 1.0f, 									
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,	
				
				// Left face 
				0.0f, 1.0f, 									
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
				
				// Top face 
				0.0f, 1.0f, 									
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
				
				// Bottom face 
				0.0f, 1.0f, 									
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,	
		};
				
		// Initialize the buffers.
		mcubeVertices = ByteBuffer.allocateDirect(triangle1VerticesData.length * mBytesPerFloat).order(ByteOrder.nativeOrder()).asFloatBuffer();						
		mcubeVertices.put(triangle1VerticesData).position(0);
		
		mCubeTextureCoordinates = ByteBuffer.allocateDirect(cubeTextureCoordinateData.length * mBytesPerFloat).order(ByteOrder.nativeOrder()).asFloatBuffer();
		mCubeTextureCoordinates.put(cubeTextureCoordinateData).position(0);
		
		mCubeColors = ByteBuffer.allocateDirect(cubeColorData.length * mBytesPerFloat).order(ByteOrder.nativeOrder()).asFloatBuffer();							
		mCubeColors.put(cubeColorData).position(0);
		
		indexBuffer = ByteBuffer.allocateDirect(indeces.length * 2).order(ByteOrder.nativeOrder()).asShortBuffer();
		indexBuffer.put(indeces).position(0);		
	}
	

	
	public static int loadTexture(GLSurfaceView mActivityContext2, final int resourceId)
	{
	    final int[] textureHandle = new int[1];
	 
	    GLES20.glGenTextures(1, textureHandle, 0);
	 
	    if (textureHandle[0] != 0)
	    {
	        final BitmapFactory.Options options = new BitmapFactory.Options();
	        options.inScaled = false;   // No pre-scaling
	 
	        // Read in the resource
	        final Bitmap bitmap = BitmapFactory.decodeResource(mActivityContext2.getResources(), resourceId, options);
	 
	        // Bind to the texture in OpenGL
	        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureHandle[0]);
	 
	        // Set filtering
	        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
	        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST);
	 
	        // Load the bitmap into the bound texture.
	        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
	 
	        // Recycle the bitmap, since its data has been loaded into OpenGL.
	        bitmap.recycle();
	    }
	 
	    if (textureHandle[0] == 0)
	    {
	        throw new RuntimeException("Error loading texture.");
	    }
	 
	    return textureHandle[0];
	}
	
	@Override
	public void onSurfaceCreated(GL10 glUnused, EGLConfig config) 
	{
	
		GLES20.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// Use culling to remove back faces.
//		GLES20.glEnable(GLES20.GL_CULL_FACE);
		GLES20.glEnable(GLES20.GL_DEPTH_TEST);

//		// Position the eye behind the origin.
		// Position the eye behind the origin.
		final float eyeX = 0.0f;
		final float eyeY = 0.0f;
		final float eyeZ = 2f;		//1.5f;

		// We are looking toward the distance
		final float lookX = 0.0f;
		final float lookY = 0.0f;
		final float lookZ = -5.0f;

		// Set our up vector. This is where our head would be pointing were we holding the camera.
		final float upX = 0.0f;
		final float upY = 1.0f;
		final float upZ = 0.0f;

		// Set the view matrix. This matrix can be said to represent the camera position.
		// NOTE: In OpenGL 1, a ModelView matrix is used, which is a combination of a model and
		// view matrix. In OpenGL 2, we can keep track of these matrices separately if we choose.
		Matrix.setLookAtM(mViewMatrix, 0, eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);
		
		//please note i am making view matrix as identity matrix intentionally here to avoid the
		//effects of view matrix. if you want explore the effect of view matrix you can uncomment this line	     
		//Matrix.setIdentityM(mViewMatrix, 0);

		final String vertexShader =
			"uniform mat4 u_MVPMatrix;      \n"		// A constant representing the combined model/view/projection matrix.
			
		  + "attribute vec4 a_Position;     \n"		// Per-vertex position information we will pass in.
		  + "attribute vec4 a_Color;        \n"		// Per-vertex color information we will pass in.			  
		  + "attribute vec2 a_TexCoordinate;\n"
		  + "varying vec2 v_TexCoordinate;  \n"
		  + "varying vec4 v_Color;          \n"		// This will be passed into the fragment shader.
		  
		  + "void main()                    \n"		// The entry point for our vertex shader.
		  + "{                              \n"
		  + "   v_Color = a_Color;          \n"		// Pass the color through to the fragment shader. 			   
		  +"v_TexCoordinate = a_TexCoordinate;\n"	// It will be interpolated across the triangle.
		  + "   gl_Position = u_MVPMatrix   \n" 	// gl_Position is a special variable used to store the final position.
		  + "               * a_Position;   \n"     // Multiply the vertex by the matrix to get the final point in 			                                            			 
		  + "}                              \n";    // normalized screen coordinates.
		
		final String fragmentShader =
			"precision mediump float;       \n"		// Set the default precision to medium. We don't need as high of a 
													// precision in the fragment shader.				
		  + "varying vec4 v_Color;          \n"		// This is the color from the vertex shader interpolated across the 
		  + "uniform sampler2D u_Texture;   \n"	
		  +"varying vec2 v_TexCoordinate;   \n"		// triangle per fragment.			  
		  + "void main()                    \n"		// The entry point for our fragment shader.
		  + "{                              \n"
		  + " gl_FragColor = (v_Color * texture2D(u_Texture, v_TexCoordinate));     \n"		// Pass the color directly through the pipeline.		  
		  + "}                              \n";												
		
		// Load in the vertex shader.
		int vertexShaderHandle = GLES20.glCreateShader(GLES20.GL_VERTEX_SHADER);

		if (vertexShaderHandle != 0) 
		{
			// Pass in the shader source.
			GLES20.glShaderSource(vertexShaderHandle, vertexShader);

			// Compile the shader.
			GLES20.glCompileShader(vertexShaderHandle);

			// Get the compilation status.
			final int[] compileStatus = new int[1];
			GLES20.glGetShaderiv(vertexShaderHandle, GLES20.GL_COMPILE_STATUS, compileStatus, 0);

			// If the compilation failed, delete the shader.
			if (compileStatus[0] == 0) 
			{				
				GLES20.glDeleteShader(vertexShaderHandle);
				vertexShaderHandle = 0;
			}
		}

		if (vertexShaderHandle == 0)
		{
			throw new RuntimeException("Error creating vertex shader.");
		}
		
		// Load in the fragment shader shader.
		int fragmentShaderHandle = GLES20.glCreateShader(GLES20.GL_FRAGMENT_SHADER);

		if (fragmentShaderHandle != 0) 
		{
			// Pass in the shader source.
			GLES20.glShaderSource(fragmentShaderHandle, fragmentShader);

			// Compile the shader.
			GLES20.glCompileShader(fragmentShaderHandle);

			// Get the compilation status.
			final int[] compileStatus = new int[1];
			GLES20.glGetShaderiv(fragmentShaderHandle, GLES20.GL_COMPILE_STATUS, compileStatus, 0);

			// If the compilation failed, delete the shader.
			if (compileStatus[0] == 0) 
			{				
				GLES20.glDeleteShader(fragmentShaderHandle);
				fragmentShaderHandle = 0;
			}
		}

		if (fragmentShaderHandle == 0)
		{
			throw new RuntimeException("Error creating fragment shader.");
		}
		
		// Create a program object and store the handle to it.
		 mProgramHandle = GLES20.glCreateProgram();
		
		if (mProgramHandle != 0) 
		{
			// Bind the vertex shader to the program.
			GLES20.glAttachShader(mProgramHandle, vertexShaderHandle);			

			// Bind the fragment shader to the program.
			GLES20.glAttachShader(mProgramHandle, fragmentShaderHandle);
			
			// Bind attributes
			GLES20.glBindAttribLocation(mProgramHandle, 0, "a_Position");
			GLES20.glBindAttribLocation(mProgramHandle, 1, "a_Color");
			GLES20.glBindAttribLocation(mProgramHandle, 2, "a_TexCoordinate");

			// Link the two shaders together into a program.
			GLES20.glLinkProgram(mProgramHandle);
			
			mTextureDataHandle0 = loadTexture(mActivityContext, R.drawable.nature1);
			mTextureDataHandle1 = loadTexture(mActivityContext, R.drawable.nature2);
			mTextureDataHandle2 = loadTexture(mActivityContext, R.drawable.nature3);
			mTextureDataHandle3 = loadTexture(mActivityContext, R.drawable.nature4);
			mTextureDataHandle4 = loadTexture(mActivityContext, R.drawable.nature5);
			mTextureDataHandle5 = loadTexture(mActivityContext, R.drawable.nature6);
			 
			// Get the link status.
			final int[] linkStatus = new int[1];
			GLES20.glGetProgramiv(mProgramHandle, GLES20.GL_LINK_STATUS, linkStatus, 0);

			// If the link failed, delete the program.
			if (linkStatus[0] == 0) 
			{				
				GLES20.glDeleteProgram(mProgramHandle);
				mProgramHandle = 0;
			}
		}
		
		if (mProgramHandle == 0)
		{
			throw new RuntimeException("Error creating program.");
		}
        

	}	
	
	@Override
	public void onSurfaceChanged(GL10 glUnused, int width, int height) 
	{
		// Set the OpenGL viewport to the same size as the surface.
		GLES20.glViewport(0, 0, width, height);

		// Create a new perspective projection matrix. The height will stay the same
		// while the width will vary as per aspect ratio.
		final float ratio = (float) width / height;
		final float left = -ratio;
		final float right = ratio;
		final float bottom = -1.0f;
		final float top = 1.0f;
		final float near = 1.0f;
		final float far = 10.0f;
		
		Matrix.frustumM(mProjectionMatrix, 0, left, right, bottom, top, near, far);
		
		//please note i am making projection matrix as identity matrix intentionally here to avoid the
		//effects of projection matrix. if you want you can uncomment this line			
		//Matrix.setIdentityM(mProjectionMatrix, 0);		
	}	

	@Override
	public void onDrawFrame(GL10 glUnused) 
	{
		GLES20.glClear(GLES20.GL_DEPTH_BUFFER_BIT | GLES20.GL_COLOR_BUFFER_BIT);			        
                
		 GLES20.glUseProgram(mProgramHandle);
	        
	        // Set program handles for cube drawing.
	        mMVPMatrixHandle = GLES20.glGetUniformLocation(mProgramHandle, "u_MVPMatrix");
	        mTextureUniformHandle = GLES20.glGetUniformLocation(mProgramHandle, "u_Texture");
	        mPositionHandle = GLES20.glGetAttribLocation(mProgramHandle, "a_Position");
	        mColorHandle = GLES20.glGetAttribLocation(mProgramHandle, "a_Color");
	        mTextureCoordinateHandle = GLES20.glGetAttribLocation(mProgramHandle, "a_TexCoordinate");
	        
	        // Do a complete rotation every 10 seconds.
//	        long time = SystemClock.uptimeMillis() % 10000L;
//	        float angleInDegrees = (360.0f / 10000.0f) * ((int) time);
	        
	        // Draw the triangle facing straight on.
	        Matrix.setIdentityM(mModelMatrix, 0);
//	        Matrix.rotateM(mModelMatrix, 0, xAngle, 0.0f, 1.0f, 0.0f);
//			Matrix.rotateM(mModelMatrix, 0, -yAngle, 1.0f, 0.0f, 0.0f);
	        Matrix.rotateM(mModelMatrix, 0, xAngle, 1.0f, 0.0f, 0.0f);
			Matrix.rotateM(mModelMatrix, 0, yAngle, 0.0f, 1.0f, 0.0f);
			Matrix.rotateM(mModelMatrix, 0, zAngle, 0.0f, 0.0f, 1.0f);
//	        Matrix.rotateM(mModelMatrix, 0, angleInDegrees, 1.0f, 1.0f, 1.0f); 
	        

			// Set the active texture unit to texture unit 0.
			GLES20.glActiveTexture(GLES20.GL_TEXTURE0);

			// Bind the texture to this unit.
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mTextureDataHandle0);

			// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
			GLES20.glUniform1i(mTextureUniformHandle, 0); 

			draw(mcubeVertices, 0);

			// Set the active texture unit to texture unit 0.
			GLES20.glActiveTexture(GLES20.GL_TEXTURE1);

			// Bind the texture to this unit.
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mTextureDataHandle1);

			// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
			GLES20.glUniform1i(mTextureUniformHandle, 1); 

			draw(mcubeVertices, 1);

			// Set the active texture unit to texture unit 0.
			GLES20.glActiveTexture(GLES20.GL_TEXTURE2);

			// Bind the texture to this unit.
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mTextureDataHandle2);

			// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
			GLES20.glUniform1i(mTextureUniformHandle, 2); 

			draw(mcubeVertices, 2);

			// Set the active texture unit to texture unit 0.
			GLES20.glActiveTexture(GLES20.GL_TEXTURE3);

			// Bind the texture to this unit.
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mTextureDataHandle3);

			// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
			GLES20.glUniform1i(mTextureUniformHandle, 3); 

			draw(mcubeVertices,3);

			//Set the active texture unit to texture unit 0.
			GLES20.glActiveTexture(GLES20.GL_TEXTURE4);

			//Bind the texture to this unit.
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mTextureDataHandle4);

			//Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
			GLES20.glUniform1i(mTextureUniformHandle, 4); 

			draw(mcubeVertices, 4);

			//Set the active texture unit to texture unit 0.
			GLES20.glActiveTexture(GLES20.GL_TEXTURE5);

			//Bind the texture to this unit.
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mTextureDataHandle5);

			//Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
			GLES20.glUniform1i(mTextureUniformHandle, 5); 

			draw( mcubeVertices, 5);
	}	
	

	private void draw(final FloatBuffer acubeBuffer, final int i)
	{

		// Pass in the position information. each vertex needs 3 values and each
		// face of the
		// cube needs 4 vertices. so total 3*4 = 12
		acubeBuffer.position(12 * i);
		GLES20.glVertexAttribPointer(mPositionHandle, 3, GLES20.GL_FLOAT, false, 0, acubeBuffer);

		GLES20.glEnableVertexAttribArray(mPositionHandle);

		// Pass in the color information. every vertex colr is defined by 4 values and each cube face has 4 vertices so 4*4 = 16
		mCubeColors.position(16 * i);
		GLES20.glVertexAttribPointer(mColorHandle, 4, GLES20.GL_FLOAT, false, 0, mCubeColors);

		GLES20.glEnableVertexAttribArray(mColorHandle);

		// Pass in the texture coordinate information. every vertex needs 2
		// values to define texture
		// for each face of the cube we need 4 textures . so 4*2=8
		mCubeTextureCoordinates.position(8 * i);
		GLES20.glVertexAttribPointer(mTextureCoordinateHandle, mTextureCoordinateDataSize, GLES20.GL_FLOAT, false, 0, mCubeTextureCoordinates);

		GLES20.glEnableVertexAttribArray(mTextureCoordinateHandle);
		// This multiplies the view matrix by the model matrix, and stores the
		// result in the MVP matrix
		// (which currently contains model * view).
		Matrix.multiplyMM(mMVPMatrix, 0, mViewMatrix, 0, mModelMatrix, 0);

		// This multiplies the modelview matrix by the projection matrix, and
		// stores the result in the MVP matrix
		// (which now contains model * view * projection).
		Matrix.multiplyMM(mMVPMatrix, 0, mProjectionMatrix, 0, mMVPMatrix, 0);

		GLES20.glUniformMatrix4fv(mMVPMatrixHandle, 1, false, mMVPMatrix, 0);
		// *each face of the cube is drawn using 2 triangles. so 2*3=6 lines
		GLES20.glDrawElements(GLES20.GL_TRIANGLES, 6, GLES20.GL_UNSIGNED_SHORT, indexBuffer);

	}

}
