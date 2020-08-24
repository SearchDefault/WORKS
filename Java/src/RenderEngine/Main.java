// Main Engine Package //
package RenderEngine;

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

        while ( !mainWindow.isCloseRequest() ) {

            mainWindow.showFPS();
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
