package data;

/*
 * Collection interface
 */

interface Collection<E> {
	 Object iterator(); 	
	 void add(E e); 
	 void addAll(Collection<E> c);
	 void clear();
	 boolean  contains(E e);
	 boolean containsAll(Collection<E> c);
	 boolean  isEmpty();
	void remove(E e);
	void removeAll(Collection<E> c);
	int size();
	
	
}

interface Set<E> extends Collection<E>{
	 Object iterator(); 
	 void add(E e);
	 void addAll(Collection<E> c);
	 void clear();
	 boolean  contains(E e);
	 boolean containsAll(Collection<E> c);
	 boolean  isEmpty();
	 void remove(E e);
	 void removeAll(Collection<E> c);
	 int size();
}

 class HashSet<E> implements	Set<E>{
	 private Object[] hashArr =new Object[1];
	 private int size;
	 private int index=0;
	 
	 private class HashIterator<E> implements Iterator<E> {
	        private int position = 0;
	        @Override
	        public boolean hasNext() {
	            if (position < size())
	                return true;
	            else
	                return false;
	        }
	        @Override
	        public E next() {
	        	
	            if (this.hasNext() && position<size())
	                return (E) hashArr[position++];
	            else
	                return null;
	        }

	        @Override
	        public Object remove() {
	        	Object[] tmp=new Object[1];
	        	tmp[0]=hashArr[0];
	        	for(int i=position+1;i<size();i++) {
	        		hashArr[i-1]=hashArr[i];
	        	}
	        	
	        	setSize(size()-1);
	        	return tmp[0];
	        	
	        }
	  }

	public void setSize(int tmpSize) {
		size=tmpSize;
	}	
			
		
	 
	 //private Array<E> hashArr = new Array<E>(1);
	
	    
	@Override
	/**
	 * @param generic_type
	 * @return void
	 *
	 */
	public void add(E e) {
		if(contains(e)==true) {
			return;
		}
		Object[] temp =new Object[size+1];
		if(size!=0) {
			for(int i=0;i<size;i++) {
				temp[i]=hashArr[i];
			}
		}
		size=size+1;
		temp[size-1]=e;
		hashArr=temp;
		
	}
	
	public Object getArr(int i) {
		
		return hashArr[i];
	}
	@Override
	public Iterator<E> iterator() {
        return new HashIterator();
    }

	@Override
	/**
	 * @param generic_type
	 * @return void
	 *
	 */
	public void addAll(Collection<E> c) {
		boolean flag=true;
		for(int i=0; i<c.size();i++) {
			for(int k=0;k<size;k++) {
				if(((HashSet<E>) c).getArr(i)== getArr(k)) {
					flag=false;
				}
				
			}
			if(flag==true) {
				E arr2 = (E) ((HashSet<E>) c).getArr(i);
				add(arr2);
			}
			
		}
		
	}
	/**
	 * @param void
	 * @return void
	 *
	 */
	@Override
	public void clear() {
		for(int i=0;i<size;i++){
			hashArr[i]=null;
		}
		size=0;
		
	}
	/**
	 * @param generic_type
	 * @return bool
	 *
	 */
	@Override
	public boolean contains(E e) {
		for(int i=0;i<size;i++) {
			if(hashArr[i]==e) {
				return true;
			}
		}
		return false;
	}
	/**
	 * @param generic_type
	 * @return bool
	 *
	 */
	@Override
	public boolean containsAll(Collection<E> c) {
		int num=0;
		for(int i=0; i<c.size();i++) {
			for(int k=0;k<size;k++) {
				if(((HashSet<E>) c).getArr(i)== getArr(k)) {
					num++;
				}
				
			}
			if(num==(c.size()-1)) {
				return true;
			}
			
		}
		return false;
	}
	/**
	 * @param void
	 * @return boolean function is empty
	 *
	 */
	@Override
	public boolean isEmpty() {
		if(size==0) {
			return true;
		}
		else {
			return false;
		}
		
	}
	/** remove paremeter element
	 * @param generic_type
	 * @return void 
	 *
	 */
	@Override
	public void remove(E e) {
		Object[] tmp =new Object[size];
		
		int revIndex=0;
		for(int i=0;i<size;i++){
			if(e==getArr(i)) {
				revIndex=i;
				break;
			}
		}
		for(int i=revIndex+1;i<size();i++) {
			hashArr[i-1]=hashArr[i];
		}
		size=size-1;
		
		
	}
	/** remove all element
	 * @param Collection 
	 * @return void
	 *
	 */
	@Override
	public void removeAll(Collection<E> c) {
		for(int i=0;i<c.size();i++) {
			for(int k=0;k<size;k++) {
				if(((HashSet<E>) c).getArr(i)==hashArr[k]) {
					remove((E) hashArr[k]);
				}
			}
		}
		
	}
	/**
	 * @param generic_type
	 * @return int size
	 *
	 */
	@Override
	public int size() {
		// TODO Auto-generated method stub
		return size;
	}
	
}
 
 
 interface List<E> extends Collection<E> {
	 Object iterator(); 
	 void add(E e); 
	 void addAll(Collection<E> c);
	 void clear();
	 boolean  contains(E e);
	 boolean containsAll(Collection<E> c);
	 boolean  isEmpty();
	void remove(E e);
	void removeAll(Collection<E> c);
	int size();
 }
 class ArrayList<E> implements List<E>{
	 private Object[] listArr =new Object[1];
	 private int size;
	 private int index=0;
	 public ArrayList (){
		size=0;
	 }			
	 private class ArrIterator<E> implements Iterator<E> {
	        private int position = 0;
	        @Override
	        public boolean hasNext() {
	            if (position < size())
	                return true;
	            else
	                return false;
	        }
	        @Override
	        public E next() {
	            if (this.hasNext())
	                return (E) listArr[position++];
	            else
	                return null;
	        }

	        @Override
	        public Object remove() {
	        	Object[] tmp=new Object[1];
	        	tmp[0]=listArr[0];
	        	for(int i=position+1;i<size();i++) {
	        		listArr[i-1]=listArr[i];
	        	}
	        	position=position-1;
	        	setSize(size()-1);
	        	return tmp[0];
	        	
	        }
	  }
	 
	 //private Array<E> hashArr = new Array<E>(1);
	
	 public void setSize(int tmpSize) {
		 size=tmpSize;
	 }
	@Override
	public void add(E e) {
		if(contains(e)==true) {
			return;
		}
		Object[] temp =new Object[size+1];
		if(size!=0) {
			for(int i=0;i<size;i++) {
				temp[i]=listArr[i];
			}
		}
		size=size+1;
		temp[size-1]=e;
		listArr=temp;
		
	}
	
	public Object getArr(int i) {
		
		return listArr[i];
	}
	@Override
	public Iterator<E> iterator() {
        return new ArrIterator();
    }
	@Override
	public void addAll(Collection<E> c) {
		boolean flag=true;
		for(int i=0; i<c.size();i++) {
			for(int k=0;k<size;k++) {
				if(((ArrayList<E>) c).getArr(i)== getArr(k)) {
					flag=false;
				}
				
			}
			if(flag==true) {
				E arr2 = (E) ((ArrayList<E>) c).getArr(i);
				add(arr2);
				
			}
			flag=true;
			
			
		}
		
	}
	@Override
	public void clear() {
		for(int i=0;i<size;i++){
			listArr[i]=null;
		}
		size=0;
		
	}
	@Override
	public boolean contains(E e) {
		for(int i=0;i<size;i++) {
			if(listArr[i]==e) {
				return true;
			}
		}
		return false;
	}
	@Override
	public boolean containsAll(Collection<E> c) {
		int num=0;
		for(int i=0; i<c.size();i++) {
			for(int k=0;k<size;k++) {
				if(((ArrayList<E>) c).getArr(i)== getArr(k)) {
					num++;
				}
				
			}
			if(num==(c.size()-1)) {
				return true;
			}
			
		}
		return false;
	}
	@Override
	public boolean isEmpty() {
		if(size==0) {
			return true;
		}
		else {
			return false;
		}
		
	}
	@Override
	public void remove(E e) {
		Object[] tmp =new Object[size];
		
		int revIndex=0;
		for(int i=0;i<size;i++){
			if(e==getArr(i)) {
				revIndex=i;
				break;
			}
		}
		for(int i=revIndex+1;i<size();i++) {
			listArr[i-1]=listArr[i];
		}
		size=size-1;
		
		
	}
	@Override
	public void removeAll(Collection<E> c) {
		for(int i=0;i<c.size();i++) {
			for(int k=0;k<size;k++) {
				if(((ArrayList<E>) c).getArr(i)==listArr[k]) {
					remove((E) listArr[k]);
				}
			}
		}
		
	}
	@Override
	public int size() {
		
		return size;
	}
 }
	
interface Queue<E> extends Collection<E> {
	 
	
	 E element();
	 void offer(E e);
	 E poll();
}

class LinkedList<E> implements Queue<E> , List<E>{
	private Object[] hashArr =new Object[1];
	 private int size;
	 ;
	
	 private class LinkIterator<E> implements Iterator<E> {
	        private int position = 0;
	        @Override
	        public boolean hasNext() {
	            if (position < size())
	                return true;
	            else
	                return false;
	        }
	        @Override
	        public E next() {
	            if (this.hasNext() && position <size)
	                return (E) hashArr[position++];
	            else
	                return null;
	        }

	        @Override
	        public Object remove() {
	        	Object[] tmp=new Object[1];
	        	tmp[0]=hashArr[0];
	        	for(int i=position+1;i<size();i++) {
	        		hashArr[i-1]=hashArr[i];
	        	}
	        	position=position-1;
	        	setSize(size()-1);
	        	return tmp[0];
	        	
	        }
	  }
	
	public void setSize(int tmpSize) {
		size=tmpSize;
	}
	@Override
	public void add(E e) {
		if(contains(e)==true) {
			return;
		}
		Object[] temp =new Object[size+1];
		if(size!=0) {
			for(int i=0;i<size;i++) {
				temp[i]=hashArr[i];
			}
		}
		size=size+1;
		temp[size-1]=e;
		hashArr=temp;
		
	}
	
	public Object getArr(int i) {
		
		return hashArr[i];
	}
	@Override
	public Iterator<E> iterator() {
        return new LinkIterator();
    }
	@Override
	public void addAll(Collection<E> c) {
		boolean flag=true;
		for(int i=0; i<c.size();i++) {
			for(int k=0;k<size;k++) {
				if(((LinkedList<E>) c).getArr(i)== getArr(k)) {
					flag=false;
				}
				
			}
			if(flag==true) {
				E arr2 = (E) ((LinkedList<E>) c).getArr(i);
				add(arr2);
			}
			
		}
		
	}
	@Override
	public void clear() {
		for(int i=0;i<size;i++){
			hashArr[i]=null;
		}
		size=0;
		
	}
	@Override
	public boolean contains(E e) {
		for(int i=0;i<size;i++) {
			if(hashArr[i]==e) {
				return true;
			}
		}
		return false;
	}
	@Override
	public boolean containsAll(Collection<E> c) {
		int num=0;
		for(int i=0; i<c.size();i++) {
			for(int k=0;k<size;k++) {
				if(((LinkedList<E>) c).getArr(i)== getArr(k)) {
					num++;
				}
				
			}
			if(num==(c.size()-1)) {
				return true;
			}
			
		}
		return false;
	}
	@Override
	public boolean isEmpty() {
		if(size==0) {
			return true;
		}
		else {
			return false;
		}
		
	}
	@Override
	public void remove(E e) {
		Object[] tmp =new Object[size];
		
		int revIndex=0;
		for(int i=0;i<size;i++){
			if(e==getArr(i)) {
				revIndex=i;
				break;
			}
		}
		for(int i=revIndex+1;i<size();i++) {
			hashArr[i-1]=hashArr[i];
		}
		size=size-1;
		
		
	}
	@Override
	public void removeAll(Collection<E> c) {
		for(int i=0;i<c.size();i++) {
			for(int k=0;k<size;k++) {
				if(((LinkedList<E>) c).getArr(i)==hashArr[k]) {
					remove((E) hashArr[k]);
				}
			}
		}
		
	}
	@Override
	public int size() {
		// TODO Auto-generated method stub
		return size;
	}

	@Override
	public E element() {
		return (E) hashArr[0];
		
	}

	@Override
	public void offer(E e) {
		Object[] temp =new Object[size+1];
		if(contains(e)==true) {
			return;
		}
		if(size!=0) {
			for(int i=0;i<size;i++) {
				temp[i]=hashArr[i];
			}
		}
		size=size+1;
		temp[size-1]=e;
		hashArr=temp;
		
		
	}

	@Override
	public E poll() {
		Object[] tmp =new Object[1];
		Object[] tmp2=new Object[size-1];
		tmp[0]=hashArr[0];
		
		for(int i=1;i<size();i++) {
			hashArr[i-1]=hashArr[i];
			tmp2[i-1]=hashArr[i-1];
		}
		size =size -1;
		hashArr=tmp2;
		return (E) tmp[0];
		
	}
}
 

