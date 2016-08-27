
/*
  *1. get service
  *2. while(true) { read data; parse data; call function; reply}
 */

 /*test_client <hello|goodbye> [name]*/
import android.util.Slog;
import android.os.ServiceManager;
import android.os.IBinder;

public class TestClient{
	private static final String TAG = "TestClient";
		
	public static void main(String args[])
	{
		if (args.length ==0 )
		{
			System.out.println("Usage : need paramenter: <hello|goodbye>");
			return;
		}

		if(args[0].equals("hello"))
		{
			//get service
			IBinder binder = ServiceManager.getService("hello");
			if(binder == null)
			{
				System.out.println("failed to get hello service !");
				Slog.i(TAG, "failed to get hello service");
				return;
			}

			IHelloService svr = IHelloService.Stub.asInterface(binder);
			
			if(args.length == 1)
			{
				try{
					svr.sayhello();
					System.out.println("Call sayhello !");
					Slog.i(TAG, "Call sayhello");
				}catch(Exception e){}
			}else{
				try{
					int cnt = svr.sayhello_to(args[1]);
					System.out.println("Call sayhello_to !"+args[1]+"cnt= "+cnt);
					Slog.i(TAG, "Call sayhello_to");
				}catch(Exception e){}
			}
		}
					
	}
}
 
