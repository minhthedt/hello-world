public class HelloJNI {  // Save as HelloJNI.java
    static {
      System.loadLibrary("program"); // Load native library hello.dll (Windows) or libhello.so (Unixes)
                                   //  at runtime
                                   // This library contains a native method called sayHello()
    }
 
    //1. Declare an instance native method sayHello() which receives no parameter and returns void
    private native void sayHello();

    //1.1.2 Passing Primitives
    private native double testJNIPrimitive(boolean a, byte b, char c, short d, int e,long f, float g,double h);
    //1.2.1 Passing Array of Primitives
    private native double[] testJNIArrayPrimitive(int[] numbers);
    //1.3 Passing Strings
    private native String testJNIString(String msg);
    //2.1.1 Accessing Object's Variables 
    private int number = 88;
    private String message = "Hello from Java";
    private native void testModifyInstanceVariable();
    //2.1.4 Accessing Class' Static Variables
    private static double s_number = 55.66;
    //2.2.1 Callback Instance Methods
    private double callbackAverage(int n1, int n2){
     return ((double)n1 + n2) / 2.0;
    }
    private native void testCallbackMethod();
    
    //2.2.2 Callback Static Methods
    private static String callbackStatic(){
        return "From static Java method";
    }   
    //2.1 Creating Objects
    private native Integer testCreateObject(int number);
    
    //2.1 Creating Object Arrays
    private native Double[] testCreateArrayObject();
    
    //4.1 Local References
    private native Integer testLocalReference(); 
    private void runTestLocalReference1() {
         Integer i = testLocalReference();
    }  
    private void runTestLocalReference2()   {
         Integer i = testLocalReference();
    }

    
   // Test Driver
   public static void main(String[] args) {
      HelloJNI test = new HelloJNI();
      //1.
      //System.out.println("1. sayHello");
      //test.sayHello();  // Create an instance and invoke the native method
      //1.1.2
      //test.runTestJNIPrimitive();
      //test.runTestJNIArrayPrimitive();
      //test.runTestJNIString();
      //test.runTestModifyInstanceVariable();
      //test.testCallbackMethod();
      //test.runTestCreateObject();
      //test.runTestCreateArrayObject();
      test.runTestLocalReference1();
      System.out.println("In Java, runTestLocalReference2");
      test.runTestLocalReference2();

   }
   
   private void runTestCreateArrayObject()   {
       Double[] numbers = testCreateArrayObject();
       for(int i =0; i < numbers.length; i++) 
           System.out.println("In Java, numbers[" + i + "] = " + numbers[i]);
   }
   
   private void runTestCreateObject()   {
       int number = 1;
       Integer ret =  testCreateObject(1);
       System.out.println("In Java, ret : " + ret );
   }

   private void runTestCallbackMethod(){
       testCallbackMethod();
   }
   
    private void runTestModifyInstanceVariable(){
       testModifyInstanceVariable();
       System.out.println("In Java, number : " + number + " message: " + message);
       System.out.println("In Java, static s_number : " + s_number );
   }
   
    private void runTestJNIString(){
       String ret = testJNIString("hello");
       System.out.println("In Java,runTestJNIString : " + ret);
   }
   
   private void runTestJNIArrayPrimitive(){
       int[] numbers = {1,2};
       double[] ret = testJNIArrayPrimitive(numbers);
       for(int i =0; i < ret.length; i++) 
           System.out.println("In Java, ret[" + i + "] = " + ret[i]);
   }
   
   private void runTestJNIPrimitive(){
       boolean a = true;byte b = 1; 
       char c = 'A'; short d = 1;
       int e = 2;long f = 3;
       float g = 3.4f; double h = 3.4f;
       double ret = testJNIPrimitive(a,b,c,d,e,f,g,h);
       System.out.println("In Java, runTestJNIPrimitive ret = " + ret);
   }
   
   

}