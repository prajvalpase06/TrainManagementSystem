// import java.io.*;
class Err extends Exception { }
class outcome621 {
    public static void main( String[] args )
    {
        try {
        f(0);
        } catch( Err e ) {
        System.out.println( "Exception caught" );
        }
    }
        static void f(int j) throws Err {
        System.out.println( j );
        if (j == 3) throw new Err();
        f( ++j );
    }
}