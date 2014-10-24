package haikuvm.pc.tools;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Formatter;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;


public class ClassTable {
	private static class Info {
		private String name;
		
		public Info(String cassName) {
			name=cassName;
		}
	}
	
	private static Map<String, Integer> map=new HashMap<String, Integer>();
	private static Info[] sort; 

	public static void classDeclaration(String cassName) {
		map.put(cassName, 0);
	}

	private static void prepareClasses() {
        sort= new Info[map.size()];
        int i=0;
        for (Entry<String, Integer> info : map.entrySet()) {
            sort[i++]=new Info(info.getKey());
        }
        Arrays.sort(sort, new Comparator<Info>() {
            @Override
            public int compare(Info o1, Info o2) {
                return o1.name.compareTo(o2.name);
            }
        });
	}
	
	/**
    char classDesc000[] PROGMEM ="free block";
	char classDesc002[] PROGMEM ="java.lang.Thread";
	char classDesc001[] PROGMEM ="java.lang.Object";

	const char *    classDesc[] PROGMEM = {
	    classDesc002,
	    classDesc001,
	    classDesc000,
	};

    const jclass    classTable[] PROGMEM = {
        (jclass)&java_lang_Thread__class,
        (jclass)&java_lang_Object__class,
        NULL,
    };
	*/

	public String toString() {
		String str="";
		prepareClasses();
		
        str+="\n";
        str+="\n";
		str+= "#if _DEBUG || NO_MICRO\n";
        str+="\n";
        str+=new Formatter().format("char classDesc%03d[] PROGMEM =\"%s\";\n", 0, "free block");
        for (int i=0; i<sort.length; i++) {
            str+=new Formatter().format("char classDesc%03d[] PROGMEM =\"%s\";\n", i+1, sort[i].name);
        }

        str+="\n";
		str+="const char *	classDesc[] PROGMEM = {\n";
		for (int i=0; i<sort.length; i++) {
			str+=new Formatter().format("\tclassDesc%03d,\n", i+1);
		}
        str+=new Formatter().format("\tclassDesc%03d,\n", 0);
		str+="};\n";
		str+="\n";
		str+="//Needed for Heap and Stack debugging\n";
		str+="const jclass    classTable[] PROGMEM = {\n";
		for (int i=0; i<sort.length; i++) {
			str+=new Formatter().format("\t(jclass)&%s__class,\n", Haikufy.mangle(sort[i].name));
		}
		str+="\tNULL\n";
		str+="};\n";
        str+="#endif\n";
		return str;
	}
}
