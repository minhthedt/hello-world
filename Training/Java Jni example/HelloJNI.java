public class HelloJNI {  // Save as HelloJNI.java
   static {
      System.loadLibrary("hello"); // Load native library hello.dll (Windows) or libhello.so (Unixes)
                                   //  at runtime
                                   // This library contains a native method called sayHello()
   }
 
   //1. Declare an instance native method sayHello() which receives no parameter and returns void
   private native void sayHello();
   
   //2. Native method that receives a Java String and return a Java String
   private native String sayHelloStr(String msg);
   
   //3. Declare a native method sumAndAverage() that receives an int[] and
   // return a double[2] array with [0] as sum and [1] as average
   private native double[] sumAndAverage(int[] numbers);
 
   // Test Driver
   public static void main(String[] args) {
      HelloJNI test = new HelloJNI();
      //1.
      System.out.println("1. sayHello");
      test.sayHello();  // Create an instance and invoke the native method
      
      //2.
      System.out.println("\n2. sayHelloStr:");
      String result = test.sayHelloStr("Hello from Java");
      System.out.println("In Java, the returned string is: " + result);
      
      //3.
      System.out.println("\n3. sumAndAverage:");
      int[] numbers = {22, 33, 33};
      double[] results =  test.sumAndAverage(numbers);
      System.out.println("In Java, the sum is " + results[0]);
      System.out.println("In Java, the average is " + results[1]);
   }
}