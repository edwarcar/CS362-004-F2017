/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;
import java.util.Random;
import java.io.*;
import java.util.Scanner;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   protected void setUp() {
      for (int index = 0; index < testPartsIndex.length - 1; index++) {
         testPartsIndex[index] = 0;
      }
   }
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   // Read from entries within UrlsToVerify.txt
	   Scanner scanner = new Scanner(getClass().getResourceAsStream("UrlsToVerify.txt"));
	   String s = new String();

	   while(scanner.hasNextLine()){
		   String[] input_details = new String[2];
		   s = scanner.nextLine();
		   input_details = s.split("\t");
		   String result;
		   
		   if (urlVal.isValid(input_details[0])) {
			   result = "valid";
		   } else {
			   result = "invalid";
		   }
		   System.out.println(input_details[0] + " expected: " + input_details[1] + " actual: " + result);		   
	   }
	   
   }
   
   
   public void testYourFirstPartition()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   ResultPair[] schemes  = {new ResultPair("http://", true),
			   					new ResultPair("https://", true),
			   					new ResultPair("sftp://", true),
			   					new ResultPair("ftp://", true),
			   					new ResultPair("//", false),
		   						new ResultPair("rdar:", false),
		   						new ResultPair("h://", false),
		   						new ResultPair("", false)};
	   
	   ResultPair[] hosts = {new ResultPair("www.google.com", true),
			   				 new ResultPair("foo.com", true),
			   				 new ResultPair("userid:password@example.com", true),
			   				 new ResultPair("userid@example.com", true),
			   				 new ResultPair("test", false),
			   				 new ResultPair("-error-.invalid", false),
			   				 new ResultPair("a.b--c.de", false),
			   				 new ResultPair("1.1.1.1", false)};
			   			
	   ResultPair[] ports = {new ResultPair(":0", false),
				 			 new ResultPair(":", false),
				 			 new ResultPair(":636", true),
				 			 new ResultPair(":-2", false),
				 			 new ResultPair(":abc", false),
				 			 new ResultPair(":65535", true),
				 			 new ResultPair(":64z", false),
				 			 new ResultPair(":10000000", false)};	
	   
	   ResultPair[] paths = {new ResultPair("", true),
			   				 new ResultPair("/../", false),
			   				 new ResultPair("/11", true),
			   				 new ResultPair("/foo", true),
			   				 new ResultPair("(something)?after=parens", true),
			   				 new ResultPair("foobar quua", false),
			   				 new ResultPair("?q=Test%20URL-encoded%20stuff", true),
			   				 new ResultPair("/what/?q=query", true)};
	   
	   for(int i = 0; i < schemes.length; i++) {
		   for (int j = 0; j < hosts.length; j++) {
			   for (int k = 0; k < ports.length; k++) {
				   for (int l = 0; l < paths.length; l++) {
					   String url = schemes[i].item + hosts[j].item + ports[k].item + paths[l].item;
					   if (schemes[i].valid && hosts[j].valid && ports[k].valid && paths[l].valid) {
						   System.out.println(url + " expected: true, result: " + urlVal.isValid(url));
					   }
				   }
			   }
		   }
	   }
   }

   public void testIsValid() {
        testIsValid(testUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
        setUp();
        //long options =
        //    UrlValidator.ALLOW_2_SLASHES
        //        + UrlValidator.ALLOW_ALL_SCHEMES
        //        + UrlValidator.NO_FRAGMENTS;

        //testIsValid(testUrlPartsOptions, options);
   }
   
   public void testIsValid2() {
	   
	   testIsValid2(testUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
   }

   public void testIsValidScheme() {
      if (printStatus) {
         System.out.print("\n testIsValidScheme() ");
      }
      String[] schemes = {"http", "gopher"};
      //UrlValidator urlVal = new UrlValidator(schemes,false,false,false);
      UrlValidator urlVal = new UrlValidator(schemes, 0);
      for (int sIndex = 0; sIndex < testScheme.length; sIndex++) {
         ResultPair testPair = testScheme[sIndex];
         boolean result = urlVal.isValidScheme(testPair.item);
         assertEquals(testPair.item, testPair.valid, result);
         if (printStatus) {
            if (result == testPair.valid) {
               System.out.print('.');
            } else {
               System.out.print('X');
            }
         }
      }
      if (printStatus) {
         System.out.println();
      }

   }

   
   public void testIsValid2(Object[] testObjects, long options) {
	   UrlValidator urlVal = new UrlValidator(null, null, options);
	   
	   for(int i=0; i < 20000; i++) {
		   int trueCount = 0; 
		   System.out.println();
		   boolean expected = true; 
		   StringBuffer testBuffer = new StringBuffer();
		   Random rand = new Random();
		   int  n = rand.nextInt(8); //values 0 - 8
		   ResultPair part1 =  testUrlScheme[n]; 
		   testBuffer.append(part1.item);
           expected &= part1.valid;
           String part = part1.item.toString();
           System.out.println(part + ": " + expected);
           System.out.print(expected);
           if(expected == true) {
        	   	trueCount++; 
           }
           n = rand.nextInt(18); //values 0 - 19
           ResultPair part2 = testUrlAuthority[n];
           testBuffer.append(part2.item);
           expected &= part2.valid;
           part = part2.item.toString();
           System.out.println(part + ": " + expected);
           if(expected == true) {
       	   	trueCount++; 
          }
           n = rand.nextInt(6); //values 0 - 6
           ResultPair part3 = testUrlPort[n];
           testBuffer.append(part3.item);
           expected &= part3.valid;
           part = part3.item.toString();
           System.out.println(part + ": " + expected);
           if(expected == true) {
       	   	trueCount++; 
          }
           n = rand.nextInt(9); //values 0 - 8
           ResultPair part4 = testPath[n];
           testBuffer.append(part4.item);
           expected &= part4.valid;
           part = part4.item.toString();
           System.out.println(part + ": " + expected);
           if(expected == true) {
       	   	trueCount++; 
          }
           n = rand.nextInt(2); //values 0 - 6
           ResultPair part5 =  testUrlQuery[n];
           testBuffer.append(part5.item);
           expected &= part5.valid;
           part = part5.item.toString();
           System.out.println(part + ": " + expected);
           if(expected == true) {
       	   	trueCount++; 
          }
       
           String url = testBuffer.toString();
           boolean result = urlVal.isValid(url);
          
          
        	   System.out.println("Iteration" + i);
       
        	   
                System.out.print(url); 
                System.out.println();
                System.out.print("URL valid: " + result); 
                System.out.println();
        	   	
           
           
           System.out.println();
	   }
	   System.out.println("All tests done");
   }
   
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   public void testIsValid(Object[] testObjects, long options) {
      UrlValidator urlVal = new UrlValidator(null, null, options);
      assertTrue(urlVal.isValid("http://www.google.com"));
      assertTrue(urlVal.isValid("http://www.google.com/"));
      int statusPerLine = 60;
      int printed = 0;
      if (printIndex)  {
         statusPerLine = 6;
      }
      do {
         StringBuffer testBuffer = new StringBuffer();
         boolean expected = true;
         for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
            int index = testPartsIndex[testPartsIndexIndex];
            ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
            testBuffer.append(part[index].item);
            expected &= part[index].valid;
         }
         //System.out.println(testPartsIndex[0]);
         String url = testBuffer.toString();
         boolean result = urlVal.isValid(url);
         
         if(result == true)
        	 System.out.println(url);
         assertEquals(url, expected, result);
         
         if (printStatus) {
            if (printIndex) {
               //System.out.print(testPartsIndextoString());
            } else {
               if (result == expected) {
                  System.out.print('.');
               } else {
                  System.out.print('X');
               }
            }
            printed++;
            if (printed == statusPerLine) {
               System.out.println();
               printed = 0;
            }
         }
      } while (incrementTestPartsIndex(testPartsIndex, testObjects));
      if (printStatus) {
         System.out.println();
      }
   }

   public void testValidator202() {
       String[] schemes = {"http","https"};
       UrlValidator urlValidator = new UrlValidator(schemes, UrlValidator.NO_FRAGMENTS);
       //UrlValidator urlValidator = new UrlValidator(schemes, UrlValidator.ALLOW_ALL_SCHEMES);
       assertTrue(urlValidator.isValid("http://www.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.org"));
   }

   public void testValidator204() {
       String[] schemes = {"http","https"};
       UrlValidator urlValidator = new UrlValidator(schemes);
       assertTrue(urlValidator.isValid("http://tech.yahoo.com/rc/desktops/102;_ylt=Ao8yevQHlZ4On0O3ZJGXLEQFLZA5"));
   }

   public void testValidator218() {
       UrlValidator validator = new UrlValidator(UrlValidator.ALLOW_2_SLASHES);
       assertTrue("parentheses should be valid in URLs",
               validator.isValid("http://somewhere.com/pathxyz/file(1).html"));
   }

    public void testValidator248() {
        RegexValidator regex = new RegexValidator(new String[] {"localhost", ".*\\.my-testing"});
        UrlValidator validator = new UrlValidator(regex, 0);

        assertTrue("localhost URL should validate",
                validator.isValid("http://localhost/test/index.html"));
        assertTrue("first.my-testing should validate",
                validator.isValid("http://first.my-testing/test/index.html"));
        assertTrue("sup3r.my-testing should validate",
                validator.isValid("http://sup3r.my-testing/test/index.html"));

        assertFalse("broke.my-test should not validate",
                validator.isValid("http://broke.my-test/test/index.html"));

        assertTrue("www.apache.org should still validate",
                validator.isValid("http://www.apache.org/test/index.html"));

        // Now check using options
        validator = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
        
        assertTrue("localhost URL should validate",
              validator.isValid("http://localhost/test/index.html"));
        
        assertTrue("machinename URL should validate",
              validator.isValid("http://machinename/test/index.html"));
        
        assertTrue("www.apache.org should still validate",
              validator.isValid("http://www.apache.org/test/index.html"));
    }

    public void testValidator288() {
        UrlValidator validator = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);

        assertTrue("hostname should validate",
                validator.isValid("http://hostname"));

        assertTrue("hostname with path should validate",
                validator.isValid("http://hostname/test/index.html"));
        
        assertTrue("localhost URL should validate",
                validator.isValid("http://localhost/test/index.html"));
        
        assertFalse("first.my-testing should not validate",
                validator.isValid("http://first.my-testing/test/index.html"));


        assertTrue("www.apache.org should still validate",
                validator.isValid("http://www.apache.org/test/index.html"));

        // Turn it off, and check
        validator = new UrlValidator(0);

        assertFalse("hostname should no longer validate",
                validator.isValid("http://hostname"));

        assertFalse("localhost URL should no longer validate",
                validator.isValid("http://localhost/test/index.html"));
        
        assertTrue("www.apache.org should still validate",
                validator.isValid("http://www.apache.org/test/index.html"));
    }
    
    public void testValidator276() {
        // file:// isn't allowed by default
        UrlValidator validator = new UrlValidator();
        
        assertTrue("http://apache.org/ should be allowed by default",
                 validator.isValid("http://www.apache.org/test/index.html"));
       
        assertFalse("file:///c:/ shouldn't be allowed by default",
                 validator.isValid("file:///C:/some.file"));
        
        assertFalse("file:///c:\\ shouldn't be allowed by default",
              validator.isValid("file:///C:\\some.file"));
        
        assertFalse("file:///etc/ shouldn't be allowed by default",
              validator.isValid("file:///etc/hosts"));
        
        assertFalse("file://localhost/etc/ shouldn't be allowed by default",
              validator.isValid("file://localhost/etc/hosts"));
        
        assertFalse("file://localhost/c:/ shouldn't be allowed by default",
              validator.isValid("file://localhost/c:/some.file"));
        
        // Turn it on, and check
        // Note - we need to enable local urls when working with file:
        validator = new UrlValidator(new String[] {"http","file"}, UrlValidator.ALLOW_LOCAL_URLS);
        
        assertTrue("http://apache.org/ should be allowed by default",
                 validator.isValid("http://www.apache.org/test/index.html"));
       
        assertTrue("file:///c:/ should now be allowed",
                 validator.isValid("file:///C:/some.file"));
        
        // Currently, we don't support the c:\ form
        assertFalse("file:///c:\\ shouldn't be allowed",
              validator.isValid("file:///C:\\some.file"));
        
        assertTrue("file:///etc/ should now be allowed",
              validator.isValid("file:///etc/hosts"));
        
        assertTrue("file://localhost/etc/ should now be allowed",
              validator.isValid("file://localhost/etc/hosts"));
        
        assertTrue("file://localhost/c:/ should now be allowed",
              validator.isValid("file://localhost/c:/some.file"));
        
        // These are never valid
        assertFalse("file://c:/ shouldn't ever be allowed, needs file:///c:/",
              validator.isValid("file://C:/some.file"));
     
        assertFalse("file://c:\\ shouldn't ever be allowed, needs file:///c:/",
              validator.isValid("file://C:\\some.file"));
    }

    
   static boolean incrementTestPartsIndex(int[] testPartsIndex, Object[] testParts) {
      boolean carry = true;  //add 1 to lowest order part.
      boolean maxIndex = true;
      for (int testPartsIndexIndex = testPartsIndex.length - 1; testPartsIndexIndex >= 0; --testPartsIndexIndex) {
         int index = testPartsIndex[testPartsIndexIndex];
         ResultPair[] part = (ResultPair[]) testParts[testPartsIndexIndex];
         if (carry) {
            if (index < part.length - 1) {
               index++;
               testPartsIndex[testPartsIndexIndex] = index;
               carry = false;
            } else {
               testPartsIndex[testPartsIndexIndex] = 0;
               carry = true;
            }
         }
         maxIndex &= (index == (part.length - 1));
      }


      return (!maxIndex);
   }

   private String testPartsIndextoString() {
      StringBuffer carryMsg = new StringBuffer("{");
      for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
         carryMsg.append(testPartsIndex[testPartsIndexIndex]);
         if (testPartsIndexIndex < testPartsIndex.length - 1) {
            carryMsg.append(',');
         } else {
            carryMsg.append('}');
         }
      }
      return carryMsg.toString();

   }

   public void testValidateUrl() {
      assertTrue(true);
   }
   
   public void testBug1(){
	  //http://www.google.com:80/test1?action=view true
	   UrlValidator validator = new UrlValidator();
	   validator.isValid("http://www.google.com:80/test1?action=view true");
	   
   }
   
   public void testBug2(){
	   UrlValidator validator = new UrlValidator();
	   validator.isValid("http://0.0.0.0:80/test1?action=view true");
   }

   /**
    * Only used to debug the unit tests.
    * @param argv
    */
   public static void main(String[] argv) {

      //UrlValidatorTest fct = new UrlValidatorTest("url test");
      //fct.setUp();
      //fct.testIsValid();
      //fct.testIsValidScheme();
	  
	  for(int i=0; i < 10000; i++) {
		  UrlValidatorTest test = new UrlValidatorTest("url test2");
		  test.testIsValid2();
	  }
   }
   //-------------------- Test data for creating a composite URL
   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
                               new ResultPair("ftp://", true),
                               new ResultPair("h3t://", true),
                               new ResultPair("3ht://", false),
                               new ResultPair("http:/", false),
                               new ResultPair("http:", false),
                               new ResultPair("http/", false),
                               new ResultPair("://", false),
                               new ResultPair("", true)};

   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
                                  new ResultPair("go.com", true),
                                  new ResultPair("go.au", true),
                                  new ResultPair("0.0.0.0", true),
                                  new ResultPair("255.255.255.255", true),
                                  new ResultPair("256.256.256.256", false),
                                  new ResultPair("255.com", true),
                                  new ResultPair("1.2.3.4.5", false),
                                  new ResultPair("1.2.3.4.", false),
                                  new ResultPair("1.2.3", false),
                                  new ResultPair(".1.2.3.4", false),
                                  new ResultPair("go.a", false),
                                  new ResultPair("go.a1a", false),
                                  new ResultPair("go.cc", true),
                                  new ResultPair("go.1aa", false),
                                  new ResultPair("aaa.", false),
                                  new ResultPair(".aaa", false),
                                  new ResultPair("aaa", false),
                                  new ResultPair("", false)
   };
   ResultPair[] testUrlPort = {new ResultPair(":80", true),
                             new ResultPair(":65535", true),
                             new ResultPair(":0", true),
                             new ResultPair("", true),
                             new ResultPair(":-1", false),
                             new ResultPair(":65636", true),
                             new ResultPair(":65a", false)
   };
   ResultPair[] testPath = {new ResultPair("/test1", true),
                          new ResultPair("/t123", true),
                          new ResultPair("/$23", true),
                          new ResultPair("/..", false),
                          new ResultPair("/../", false),
                          new ResultPair("/test1/", true),
                          new ResultPair("", true),
                          new ResultPair("/test1/file", true),
                          new ResultPair("/..//file", false),
                          new ResultPair("/test1//file", false)
   };
   //Test allow2slash, noFragment
   ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
                                    new ResultPair("/t123", true),
                                    new ResultPair("/$23", true),
                                    new ResultPair("/..", false),
                                    new ResultPair("/../", false),
                                    new ResultPair("/test1/", true),
                                    new ResultPair("/#", false),
                                    new ResultPair("", true),
                                    new ResultPair("/test1/file", true),
                                    new ResultPair("/t123/file", true),
                                    new ResultPair("/$23/file", true),
                                    new ResultPair("/../file", false),
                                    new ResultPair("/..//file", false),
                                    new ResultPair("/test1//file", true),
                                    new ResultPair("/#/file", false)
   };

   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
                              new ResultPair("?action=edit&mode=up", true),
                              new ResultPair("", true)
   };

   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
   Object[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};
   int[] testPartsIndex = {0, 0, 0, 0, 0};

   //---------------- Test data for individual url parts ----------------
   ResultPair[] testScheme = {new ResultPair("http", true),
                            new ResultPair("ftp", false),
                            new ResultPair("httpd", false),
                            new ResultPair("telnet", false)};


}