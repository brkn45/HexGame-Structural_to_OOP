package data;
/**	
*@author Berkan_Akin
*/

public class Main {
	/*
	 * testing all functions 
	 */

	public static void main(String[] args) {
		data.HashSet<Integer> berkan = new data.HashSet<Integer>();
		berkan.add(10);
		berkan.add(20);
		berkan.add(30);
		berkan.add(40);
		
		data.HashSet<Integer> akin = new data.HashSet<Integer>();
		akin.add(50);
		akin.add(60);
		akin.add(40);
		
		berkan.addAll(akin);
	
		for(int i=0;i<berkan.size();i++) {
			System.out.println("HashSet AddAll Test"+berkan.getArr(i));
		}
		System.out.println("HashSet containall()(contain() function) function Test "+berkan.containsAll(akin));
		berkan.removeAll(akin);
		System.out.println("HashSet containall()(contain() function) function Test "+berkan.containsAll(akin));
		 Iterator<Integer> iter= berkan.iterator();
		 
		 while (iter.hasNext()) {
	             
	            System.out.println("HashSet removeAll(remove function) function and Iterator test: " +  iter.next());
	        }
		 
		 iter= berkan.iterator();
		 iter.remove(); // remove first element
		 while (iter.hasNext()) {
			 System.out.println("Test Ýter remove and hasNext(), next() function: " +  iter.next());
         }
		 
		 // **********               ArrayList Test                                                       *********//
		 
		 data.ArrayList<Integer> chain =new data.ArrayList<Integer>();
		 
		 chain.add(10);
		 chain.add(20);
		 chain.add(30);
		 chain.add(40);
		 Iterator<Integer> arrIter= chain.iterator();
		 data.ArrayList<Integer> engine =new data.ArrayList<Integer>();
		 engine.add(30);
		 engine.add(40);
		 engine.add(50);
		 engine.add(60);
		 while (arrIter.hasNext()) {
             
	            System.out.println("HashSet removeAll(remove function) function and Iterator test: " +  arrIter.next());
	        }
		 chain.addAll(engine);
		 arrIter=chain.iterator();
		 
		while (arrIter.hasNext()) {
        
			System.out.println("ArrayList addAll(add function) function and Iterator test: " +  arrIter.next());
		}
		System.out.println("ArrayList containall()(contain() function) function Test "+chain.containsAll(engine));
		chain.removeAll(engine);
		System.out.println("ArrayList containall()(contain() function) function Test "+chain.containsAll(engine));
		
		arrIter=chain.iterator();
		while (arrIter.hasNext()) {
            
            System.out.println("HashSet removeAll(remove function) function and Iterator test: " +  arrIter.next());
        }
		
		
		//*************************            LinkedList Test                        ********************************//
		
		data.LinkedList<String> word =new data.LinkedList<String>();
		data.LinkedList<String> promise =new data.LinkedList<String>();
		
		word.offer("blue");
		word.offer("black");
		word.offer("red");
		word.offer("yellow");
		
		Iterator<String> iterWord= word.iterator();
		
		while (iterWord.hasNext()) {
			 System.out.println("Test Ýter : " +  iterWord.next());
        }
		
		promise.add("white");
		promise.add("black");
		promise.add("green");
		
		word.addAll(promise);
		iterWord= word.iterator();
		
		while (iterWord.hasNext()) {
			 System.out.println("Test Ýter : " +  iterWord.next());
       }
		
		System.out.println("LinkedList containall()(contain() function) function Test "+word.containsAll(promise));
		word.removeAll(promise); // remove() and removeall() test function
		System.out.println("LinkedList containall()(contain() function) function Test "+word.containsAll(promise));
		
		iterWord= word.iterator();
		
		while (iterWord.hasNext()) {
			 System.out.println("Test Ýter : " +  iterWord.next());
       }
		
		System.out.println("pull() function test "+word.poll());
	
	iterWord= word.iterator();
	
	while (iterWord.hasNext()) {
		 System.out.println("Test Ýter : " +  iterWord.next());
   }
	System.out.println("Test element() function : " +  word.element());
	
	}
}
