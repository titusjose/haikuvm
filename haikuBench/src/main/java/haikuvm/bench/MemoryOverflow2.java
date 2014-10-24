package haikuvm.bench;

public class MemoryOverflow2 {
	public static void main(String[] args) throws Exception {
	    byte[][] fill=new byte[100][];
	    for (int i = 0; i < fill.length; i++) {
	        System.out.println("fill "+i);
	        fill[i]=new byte[10];            
        }
        System.out.println("ready");
	}
}
