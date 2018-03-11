
 
import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!







public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
	   //String[] schemes = {"http", "https", "ftp"};
	   
	  
	   
	   // Using default constructor
	   UrlValidator testVal1 = new UrlValidator();
	   
	   System.out.println("Testing isValid with default constructor");
	   
	   
	   
	   System.out.println("http://www.google.com: " + testVal1.isValid("http://www.google.com"));
	   System.out.println("https://www.google.com: " + testVal1.isValid("https://www.google.com"));
	   System.out.println("ftp://www.google.com: " + testVal1.isValid("ftp://www.google.com"));
	   System.out.println("test://www.google.com: " + testVal1.isValid("test://www.google.com"));
	   System.out.println("www.google.com: " + testVal1.isValid("www.google.com"));
	   System.out.println("http://255.255.255.255: " + testVal1.isValid("http://255.255.255.255"));
	   System.out.println("http://256.256.256.256: " + testVal1.isValid("http://256.256.256.256"));
	   System.out.println("http://www.google.com/hello?key=value: " + testVal1.isValid("http://www.google.com/hello?key=value"));
	   System.out.println("http://www.google.com:20/hello?key=value: " + testVal1.isValid("http://www.google.com:20/hello?key=value"));
	   System.out.println("http://www.google.com:20:" + testVal1.isValid("http://www.google.com:20"));
	   
	   
	   // Using UrlValidator(String[] schemes, RegexValidator authorityValidator, long options) constructor
	   UrlValidator testVal2 = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("\nTesting isValid with allow all schemes on");	   
	   
	   System.out.println("http://www.google.com: " + testVal2.isValid("http://www.google.com"));
	   //System.out.println("https://www.google.com: " + testVal2.isValid("https://www.google.com"));
	   //System.out.println("ftp://www.google.com: " + testVal2.isValid("ftp://www.google.com"));
	   //System.out.println("test://www.google.com: " + testVal2.isValid("test://www.google.com"));
	   System.out.println("www.google.com: " + testVal2.isValid("www.google.com"));
	   System.out.println("http://255.255.255.255: " + testVal2.isValid("http://255.255.255.255"));
	   //System.out.println("https://255.255.255.255: " + testVal2.isValid("https://255.255.255.255"));
	   System.out.println("http://256.256.256.256: " + testVal2.isValid("http://256.256.256.256"));
	   //System.out.println("https://256.256.256.256: " + testVal2.isValid("https://256.256.256.256"));
	   System.out.println("http://www.google.com/hello?key=value: " + testVal2.isValid("http://www.google.com/hello?key=value"));
	   System.out.println("http://www.google.com:20/hello?key=value: " + testVal2.isValid("http://www.google.com:20/hello?key=value"));
	   System.out.println("http://www.google.com:20: " + testVal2.isValid("http://www.google.com:20"));	   
	   
	  

   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
