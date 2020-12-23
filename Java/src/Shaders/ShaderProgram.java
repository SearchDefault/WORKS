package Shaders;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import static org.lwjgl.opengl.GL46C.*;

public abstract class ShaderProgram {

    private int programID;
    private int vertexShaderID;
    private int fragmentShaderID;

    public ShaderProgram ( String vertexFile, String fragmentFile ) {
        this.vertexShaderID = loadShader( vertexFile, GL_VERTEX_SHADER );
        this.fragmentShaderID = loadShader( fragmentFile, GL_FRAGMENT_SHADER );

        this.programID = glCreateProgram();
        glAttachShader( this.programID, this.vertexShaderID );
        glAttachShader( this.programID, this.fragmentShaderID );

        glLinkProgram( this.programID );
        glValidateProgram( this.programID );

        bindAttributes();
    }

    public void start () {
        glUseProgram( this.programID );
    }

    public void stop () {
        glUseProgram( 0 );
    }

    public  void cleanUP () {
        stop();
        glDetachShader( this.programID, this.vertexShaderID );
        glDetachShader( this.programID, this.fragmentShaderID );
        glDeleteShader( this.vertexShaderID );
        glDeleteShader( this.fragmentShaderID );
        glDeleteProgram( this.programID );
    }

    protected abstract void bindAttributes ();

    protected void bindAttribute ( int attribute, String variableName ) {
        glBindAttribLocation( this.programID, attribute, variableName );
    }

    private static int loadShader ( String file, int type ) {
        StringBuilder shaderSource = new StringBuilder();

        try {
            BufferedReader reader = new BufferedReader( new FileReader( file ));
            String line;

            while ( ( line = reader.readLine() ) != null ) {
                shaderSource.append( line ).append( "\n" );
            }
            reader.close();

        } catch ( IOException e ) {
            System.err.println( "[LOG]: Could not read file! " );
            e.printStackTrace();
            System.exit( -1 );
        }

        int shaderID = glCreateShader( type );
        glShaderSource( shaderID, shaderSource );
        glCompileShader( shaderID );

        if ( glGetShaderi( shaderID, GL_COMPILE_STATUS ) == GL_FALSE ) {
            System.out.println( glGetShaderInfoLog( shaderID, 500 ) );
            System.err.println( "[LOG]: Could not compile shader" );
            System.exit( -1 );
        }

        return shaderID;
    }
}