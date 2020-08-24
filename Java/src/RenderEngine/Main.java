// Main Engine Package //
package RenderEngine;

import org.lwjgl.glfw.GLFW; //finaly

/**
 * ## This Render Engine produced ##
 * ## By Search Default ##
 */

// Main Class //
public class Main {

    // Run Engine Method //
    public void run () {

        DisplayManager mainWindow = new DisplayManager( 800, 600, "MyEngine" );
        mainWindow.createDisplay();

        //FPS
        double previousTime = GLFW.glfwGetTime();
        int frameCount = 0;

        while ( !mainWindow.isCloseRequest() ) {
            double currentTime = GLFW.glfwGetTime();
            frameCount++;

            if ( currentTime - previousTime >= 1.0d ) {
                System.out.println( frameCount );

                frameCount = 0;
                previousTime = currentTime;
            }

            mainWindow.updateDisplay();
        }

        mainWindow.deleteDisplay();
    }

    // Main Method //
    public static void main(String[] args) {

        /**
         * ## Start run method ##
         */
        new Main().run();
    }
}
