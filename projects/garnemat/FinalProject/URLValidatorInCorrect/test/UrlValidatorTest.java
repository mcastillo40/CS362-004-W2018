
 
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
	   //Test Scheme part of the URL
	   System.out.println("\n\n\t Testing scheme with default constructor");
	      	   				
	   // Test valid default scheme "http, https, ftp"
	   UrlValidator testVal = new UrlValidator();
				       
	   String[] testSchemes = {"http://", "https://", "ftp://", " ", "://", "test//", "://", "http:/"};	
	   
	   // Iterates through different schemes; only default schemes should be true
	   for(int i = 0; i < testSchemes.length; i++){
		   String testString = testSchemes[i] + "www.google.com";
		   System.out.println();
		  switch(i) {
		   	case 0: 
		   		// http://www.google.com
		   		System.out.println((i + 1) + ": " + testString);
				System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
		   		break;
		   	case 1: 
		   		// https://www.google.com
		   		System.out.println((i + 1) + ": " + testString);
				System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
		   		break;
		   	case 2: 
		   		// ftp://www.google.com
		   		System.out.println((i + 1) + ": " + testString);
				System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
		   		break;
		   	case 3:
		   		// www.google.com
		   		System.out.println((i + 1) + ": " + testString);
				System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
				break;
			case 4:
				// ://www.google.com
				System.out.println((i + 1) + ": " + testString);
				System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
				break;
			case 5:
				// test//www.google.com
				System.out.println((i + 1) + ": " + testString);
				System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
				break;
			case 6:
				// ://www.google.com
				System.out.println((i + 1) + ": " + testString);
				System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));	
				break;
			case 7:
				// http:/www.google.com
				System.out.println((i + 1) + ": " + testString);
				System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));	
				break;
		   }
	   }

   }
   
   public void testYourSecondPartition(){
	   //Test Authority part of the URL
	   System.out.println("\n\t Testing Authority with allowing all schemes");
	   
	   // Valid schemes 
	   String[] defaultSchemes = {"http://"};
	   
	   // Test scheme that has been shown to work
	   UrlValidator testVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // Authority that we will test 
	   String[] testAuthority = {"www.google.com", "www.bing.com", "714.com", "0.0.0.0", " ", "abc", "E.T1", ".007"};
	   
	   // Iterates through different authorities; 
	   for(int i = 0; i < testAuthority.length; i++){
		   String testString = defaultSchemes[0] + testAuthority[i];
		   System.out.println();
		   
		   switch(i) {
		   	case 0: 
		   			// Test http://www.google.com
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
					break;
		   	case 1: 
		   			// Test http://www.bing.com
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
					break;
		   	case 2: 
		   			// Test http://714.com
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
					break;
		   	case 3:
		   			// Test http://5.3.4
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
					break;
			case 4:
					// Test http://
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
					break;
			case 5:
					// Test http://abc
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
					break;
			case 6:
					// Test http://E.T1
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
					break;
			case 7:
					// Test http://.007
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
					break;
		   }
		   System.out.println();
	   }

   }
   
   public void testYourThirdPartition() {
	 //Test Port part of the URL
	   System.out.println("\n\t Testing Port with with allowing all schemes");
	   
	   // Valid schemes 
	   String[] defaultSchemes = {"http://"};
	   
	   // Test scheme that has been shown to work
	   UrlValidator testVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // Port that we will test 
	   String[] testPort = {":8000", ":800", ":80", ":0", ": ", ":0.0", ":-8", ":a"};
	   
	   // Iterates through different ports; 
	   for(int i = 0; i < testPort.length; i++){
		   String testString = defaultSchemes[0] + "www.google.com" + testPort[i];
		   System.out.println();
		   
		   switch(i) {
		   	case 0: 
		   			// Test http://www.google.com:8000
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
		   			break;
		   	case 1: 
		   			// Test http://www.google.com:800
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
					break;
		   	case 2: 
		   			// Test http://www.google.com:80
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
					break;
		   	case 3:
		   			// Test http://www.google.com:0
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
					break;
			case 4:
					// Test http://www.google.com:
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
					break;
			case 5:
					// Test http://www.google.com:0.0
		   			System.out.println("Test: " + testString);
					System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
					break;
			case 6:
					// Test http://www.google.com:-8
			   		System.out.println("Test: " + testString);
					System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
					break;
			case 7:
					// Test http://www.google.com:a
	   				System.out.println("Test: " + testString);
	   				System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
	   				break;   
		   }
		   System.out.println();
	   }
}
   
   public void testYourFourthPartition() {
		 //Test Path part of the URL
		   System.out.println("\n\t Testing Path with with allowing all schemes");
		   
		   // Valid schemes 
		   String[] defaultSchemes = {"http://"};
		   
		   // Test scheme that has been shown to work
		   UrlValidator testVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		   
		   // Port that we will test 
		   String[] testPath = {"/path1", "/p8", "/$45", "/path1/path2", " ", "/..", "/dsf//sd", "/../"};
		   
		   
		   // Iterates through different paths; 
		   for(int i = 0; i < testPath.length; i++){
			   String testString = defaultSchemes[0] + "www.google.com" + testPath[i];
			   System.out.println();
			   
			   switch(i) {
			   	case 0: 
			   			// Test http://www.google.com/path1
			   			System.out.println("Test: " + testString);
						System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
						break;
			   	case 1: 
			   			// Test http://www.google.com/p8
			   			System.out.println("Test: " + testString);
						System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
						break;
			   	case 2: 
			   			// Test http://www.google.com/$45
			   			System.out.println("Test: " + testString);
						System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
						break;
			   	case 3:
			   			// Test http://www.google.com/path1/path2
			   			System.out.println("Test: " + testString);
						System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
						break;
				case 4:
						// Test http://www.google.com 
			   			System.out.println("Test: " + testString);
						System.out.print("   Expected: True\n   " + "Result:   " + testVal.isValid(testString));
						break;
				case 5:
						// Test http://www.google.com/..
			   			System.out.println("Test: " + testString);
						System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
						break;
				case 6:
						// Test http://www.google.com/dsf//sd
			   			System.out.println("Test: " + testString);
						System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
						break;
				case 7:
						// Test http://www.google.com/../
			   			System.out.println("Test: " + testString);
						System.out.print("   Expected: False\n   " + "Result:   " + testVal.isValid(testString));
						break;
			   }
			   System.out.println();
		   }
	}
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
