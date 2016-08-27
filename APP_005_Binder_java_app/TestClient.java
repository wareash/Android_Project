
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
			IBinder binder_hello = ServiceManager.getService("hello");
			if(binder_hello == null)
			{
				System.out.println("failed to get hello service !");
				Slog.i(TAG, "failed to get hello service");
				return;
			}

			IHelloService svr = IHelloService.Stub.asInterface(binder_hello);
			
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
		else if(args[0].equals("goodbye"))
		{
			//get service
			IBinder binder_goodbye = ServiceManager.getService("goodbye");
			if(binder_goodbye == null)
			{
				System.out.println("failed to get goodbye service !");
				Slog.i(TAG, "failed to get goodbye service");
				return;
			}

			IGoodbyeService svr = IGoodbyeService.Stub.asInterface(binder_goodbye);
			
			if(args.length == 1)
			{
				try{
					svr.saygoodbye();
					System.out.println("Call saygoodbye !");
					Slog.i(TAG, "Call saygoodbye");
				}catch(Exception e){}
			}else{
				try{
					int cnt = svr.saygoodbye_to(args[1]);
					System.out.println("Call saygoodbye_to !"+args[1]+"cnt= "+cnt);
					Slog.i(TAG, "Call saygoodbye_to");
				}catch(Exception e){}
			}
		}

	}
}
 
