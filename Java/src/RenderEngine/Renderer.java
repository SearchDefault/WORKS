package RenderEngine;

import static org.lwjgl.opengl.GL46C.*;

public class Renderer {

    public void prepare () {
        glClearColor( 0, 1, 1, 1 );
        glClear( GL_COLOR_BUFFER_BIT );
    }

    public void render ( RawModel model ) {
        glBindVertexArray( model.getVaoID() );
        glEnableVertexAttribArray( 0 );
        glDrawElements( GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glBindVertexArray( 0 );
    }
}
