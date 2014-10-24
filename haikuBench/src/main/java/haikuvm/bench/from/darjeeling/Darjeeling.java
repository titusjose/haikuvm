package haikuvm.bench.from.darjeeling;

public class Darjeeling {

    public static void assertTrue(int i, boolean b) {
        if (b) {
            System.out.println("Darjeeling.assertTrue("+i/1000+", "+i%1000+") passed");
        } else {
            System.out.println("Darjeeling.assertTrue("+i/1000+", "+i%1000+") failed !!");
            //throw new RuntimeException("failed");
        }
    }

}
