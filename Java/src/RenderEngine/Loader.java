package RenderEngine;

import org.lwjgl.BufferUtils;

import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.List;

import static org.lwjgl.opengl.GL46C.*;

public class Loader {

    private final List<Integer> vaos = new ArrayList<>();
    private final List<Integer> vbos = new ArrayList<>();

    public  RawModel loadToVAO ( float[] positions, int[] indices ) {
        int vaoID = this.createVAO();
        bindIndicesBuffer ( indices );
        storeDataInAttributeList( 0, positions );
        unbindVAO( vaoID );

        return new RawModel( vaoID, indices.length );
    }

    public void cleanUP () {
        for ( int vao : this.vaos ) {
            glDeleteVertexArrays( vao );
        }

        for ( int vbo : this.vbos ) {
            glDeleteBuffers( vbo );
        }
    }

    private int createVAO () {
        int vaoID = glCreateVertexArrays();
        this.vaos.add( vaoID );
        glBindVertexArray( vaoID );

        return vaoID;
    }

    private void storeDataInAttributeList ( int attribNumber, float[] data ) {
        int vboID = glCreateBuffers();
        this.vbos.add( vboID );
        glBindBuffer( GL_ARRAY_BUFFER, vboID );
        FloatBuffer buffer = storeDataInFloatBuffer( data );
        glBufferData( GL_ARRAY_BUFFER, buffer, GL_STATIC_DRAW );
        glVertexAttribPointer( attribNumber, 3, GL_FLOAT, false, 0, 0 );
        glBindBuffer( GL_ARRAY_BUFFER, vboID );
    }

    private void unbindVAO ( int vaoID ) {
        glBindVertexArray( vaoID );
    }

    private void bindIndicesBuffer ( int[] indices ) {
        int vboID = glCreateBuffers();
        vbos.add( vboID );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboID );
        IntBuffer buffer = storeDataInIntBuffer( indices );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, buffer, GL_STATIC_DRAW );
    }

    private IntBuffer storeDataInIntBuffer (int[] data ) {
        IntBuffer buffer = BufferUtils.createIntBuffer( data.length );
        buffer.put( data );
        buffer.flip();

        return buffer;
    }

    private FloatBuffer storeDataInFloatBuffer ( float[] data ) {
        FloatBuffer buffer = BufferUtils.createFloatBuffer( data.length );
        buffer.put( data );
        buffer.flip();

        return buffer;
    }
}
