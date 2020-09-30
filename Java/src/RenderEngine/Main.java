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

        Loader loader = new Loader();
        Renderer renderer = new Renderer();

        //Positions
        float[] vertices = {
                -0.5f, 0.5f, 0,
                -0.5f, -0.5f, 0,
                0.5f, -0.5f, 0,
                0.5f, 0.5f, 0
        };

        int[] indices = {
                0, 1, 3,
                3, 1, 2
        };

        RawModel model = loader.loadToVAO( vertices, indices );

        while ( !mainWindow.isCloseRequest() ) {
            renderer.prepare();

            renderer.render( model );

            mainWindow.showFPS();
            mainWindow.updateDisplay();
        }

        loader.cleanUP();
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
