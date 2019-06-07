public class judgeString{
public native String getSolution(String PATH);
static{
	System.loadLibrary("testjni");
}
public static void main(String args[])
{
	judgeString a = new judgeString();
	String t = a.getSolution("/home/houzena/jni#200#10#");
	System.out.println("java:"+t);
}

}
