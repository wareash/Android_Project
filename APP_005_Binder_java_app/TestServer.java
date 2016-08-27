import android.util.Slog;
import android.os.ServiceManager;

/*
  *1. add service
  *2. while(true) { read data; parse data; call function; reply}
 */
public class TestServer{
	private static final String TAG = "TestServer";
		
	public static void main(String args[])
	{
		Slog.i(TAG, "add Hello Service");
		ServiceManager.addService("hello", new HelloService());
		ServiceManager.addService("goodbye", new GoodbyeService());
		
		while(true)
		{
			try{
				Thread.sleep(100);
			}catch(Exception e){};
		}
	}
}
 
