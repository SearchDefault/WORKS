package RenderEngine;

import org.lwjgl.BufferUtils;
import org.lwjgl.glfw.GLFWVidMode;
import org.lwjgl.opengl.GL;
import org.lwjgl.opengl.GL11;
import org.lwjgl.system.MemoryStack;

import java.nio.IntBuffer;

import static org.lwjgl.glfw.GLFW.*;

public class DisplayManager {

    public DisplayManager ( int width, int height, String title ) {
        this.width = width;
        this.height = height;
        this.title = title;
    }

    public void createDisplay() {
        if (!glfwInit()) {
            System.err.println("[ERROR LOG]: GLFW not initialize");
            Runtime.getRuntime().exit( -1 );
        }

        this.winID = glfwCreateWindow( this.width, this.height, this.title, 0, 0 );

        try ( MemoryStack stack = MemoryStack.stackPush() ) {
            this.bufferWidth = BufferUtils.createIntBuffer( 1 );
            this.bufferHeight = BufferUtils.createIntBuffer( 1 );

            glfwGetWindowSize( this.winID, this.bufferWidth, this.bufferWidth );
        }
        catch ( Exception e ) {
            System.err.println( "[Log Error]: Buffered With and Height not created!" );
            e.printStackTrace();
            Runtime.getRuntime().exit( -1 );
        }
        this.videoMode = glfwGetVideoMode( glfwGetPrimaryMonitor() );

        glfwSetWindowTitle( this.winID, this.title );
        glfwSetWindowSize( this.winID, this.width, this.height );
        glfwSetWindowAspectRatio( this.winID, this.width, this.height );

        glfwSetWindowPos(
                this.winID,
                ( this.videoMode.width() - this.bufferWidth.get( 0 ) ) / 2,
                ( this.videoMode.height() - this.bufferHeight.get( 0 ) ) / 2
                );

        glfwSetWindowSizeLimits( this.winID, this.width, this.height, this.videoMode.width(), this.videoMode.height() );
        glfwMakeContextCurrent( this.winID );
        GL.createCapabilities();

        GL11.glViewport( 0, 0, this.bufferWidth.get( 0 ), this.bufferHeight.get( 0 ) );
    }

    public void changeWindowSize ( int width, int height ) {

        this.width = width;
        this.height = height;
        glfwSetWindowSize( this.winID, this.width, this.height );
    }

    public void updateDisplay() {
        glfwPollEvents();
        glfwSwapBuffers( this.winID );
    }

    public void showFPS () {
        this.currentTime = glfwGetTime();
        this.frameCount++;

        if ( this.currentTime - this.previousTime >= 1.0d ) {
            System.out.println( this.frameCount );

            this.frameCount = 0;
            this.previousTime = this.currentTime;
        }
    }

    public void deleteDisplay() {
        glfwDestroyWindow( this.winID );
    }

    public boolean isCloseRequest () {
        return glfwWindowShouldClose( this.winID );
    }

    public int getHeight() {
        return height;
    }

    public int getWidth() {
        return width;
    }

    public GLFWVidMode getVideoMode() {
        return videoMode;
    }

    public IntBuffer getBufferHeight() {
        return bufferHeight;
    }

    public IntBuffer getBufferWidth() {
        return bufferWidth;
    }

    public String getTitle() {
        return title;
    }

    // Window Ver
    private int width = 1280;
    private int height = 720;
    private IntBuffer bufferWidth;
    private IntBuffer bufferHeight;
    private String title =  "Game Window";
    private long winID;
    private GLFWVidMode videoMode;

    //FPS
    private int frameCount = 0;
    private double currentTime;
    private double previousTime = glfwGetTime();
}